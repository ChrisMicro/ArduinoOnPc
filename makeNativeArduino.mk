penultimateword = $(wordlist $(words $1),$(words $1), x $1)

SKETCH_ROOT := $(shell dirname $(abspath $(call penultimateword, $(MAKEFILE_LIST))))
NATIVE_ROOT := $(shell dirname $(abspath $(lastword $(MAKEFILE_LIST))))

Q ?= @

BUILD_ROOT ?= build
SKETCH ?= $(shell find $(SKETCH_ROOT) -maxdepth 1 -name "*.ino")

TARGET := $(shell basename -s .ino $(SKETCH))

$(shell mkdir -p $(BUILD_ROOT))

CFLAGS += -Wall -Wextra -Wno-unused-parameter
CFLAGS += -DARDUINO=101 -DSKETCH_FILE=\"$(SKETCH)\"
CFLAGS += -std=gnu11
CFLAGS += -lm
#CFLAGS += -DFASTLED_SDL $(shell sdl2-config --cflags)

CXXFLAGS += -Wall -Wextra -Wno-unused-parameter
CXXFLAGS += -DARDUINO=101 -DSKETCH_FILE=\"$(SKETCH)\"
CXXFLAGS += -Wno-class-memaccess # FastLED does some naughty things
CXXFLAGS += -std=gnu++11
#CXXFLAGS += -DFASTLED_SDL $(shell sdl2-config --cflags)

LDFLAGS += -Wl,--gc-sections
LDFLAGS += -L/usr/X11R6/lib -lX11
#LDFLAGS += $(shell sdl2-config --libs)

DEPDIR := $(BUILD_ROOT)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@

define add_lib
SRC_C    += $(shell find $1 -name '*.c')
SRC_CXX  += $(shell find $1 -name '*.cpp')
SRC_USER_C = $(shell find $(SKETCH_ROOT) -name "*.c")
SRC_USER_CXX = $(shell find $(SKETCH_ROOT) -name "*.cpp")

INCLUDES += -I$1
endef

INCLUDES += -I$(SKETCH_ROOT)
INCLUDES += -I$(NATIVE_ROOT)/src/cores/arduino -I$(NATIVE_ROOT)/src/system
$(eval $(call add_lib,$(NATIVE_ROOT)/src))

$(foreach lib, $(ARDUINO_LIBS), $(eval $(call add_lib,$(NATIVE_ROOT)/libraries/$(lib))))

USER_FOLDERS = $(shell find $(SKETCH_ROOT) -path $(SKETCH_ROOT)/build -prune -o -type d -print)
INC_USER_FOLDERS = $(foreach folder, $(USER_FOLDERS), -I$(folder))


OBJECTS += $(SRC_C:%.c=$(BUILD_ROOT)/%.o)
OBJECTS += $(SRC_CXX:%.cpp=$(BUILD_ROOT)/%.o)
OBJECTS += $(SRC_USER_C:%.c=$(BUILD_ROOT)/%.o)
OBJECTS += $(SRC_USER_CXX:%.cpp=$(BUILD_ROOT)/%.o)

SRCS += $(SRC_C)
SRCS += $(SRC_CXX)
SRCS += $(SRC_USER_C)
SRCS += $(SRC_USER_CXX)

$(TARGET): $(OBJECTS)
	$(Q)$(CXX) $(INC_USER_FOLDERS) $(INCLUDES) $(OBJECTS) $(LDFLAGS) -o $@
	@size $@

clean:
	rm -r $(BUILD_ROOT)
	rm $(TARGET)

print:
	@echo "BUILD_ROOT:\t $(BUILD_ROOT)"
	@echo "INCLUDES:\t $(INCLUDES)"
	@echo "OBJECTS:\t $(OBJECTS)"
	@echo "SRCS:\t $(SRCS)"
	@echo "SKETCH:\t $(SKETCH)"
	@echo "ROOT:\t $(NATIVE_ROOT)"
	@echo "SRC_C   :\t $(SRC_C)"
	@echo "SRC_CXX :\t $(SRC_CXX)"
	@echo "SRC_USER:\t $(SRC_USER)"
	@echo ":\t $(INC_USER_FOLDERS)"




$(BUILD_ROOT)/%.o : %.c $(DEPDIR)/%.d
	@mkdir -p `dirname $@`
	$(Q)$(CC) $(DEPFLAGS) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(POSTCOMPILE)

$(BUILD_ROOT)/%.o : %.cpp $(DEPDIR)/%.d
	@mkdir -p `dirname $@`
	$(Q)$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(INCLUDES) -c $< -o $@
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

include $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS))))
