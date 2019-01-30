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
CFLAGS += -DFASTLED_SDL $(shell sdl2-config --cflags)
CFLAGS += -std=c++11

CXXFLAGS += $(CFLAGS)
CXXFLAGS += -Wno-class-memaccess # FastLED does some naughty things

LDFLAGS += $(shell sdl2-config --libs)
LDFLAGS += -Wl,--gc-sections

DEPDIR := $(BUILD_ROOT)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@

define add_lib
SRC_C    += $(shell find $1 -name '*.c')
SRC_CXX  += $(shell find $1 -name '*.cpp')

INCLUDES += -I$1
endef

INCLUDES += -I$(NATIVE_ROOT)/src/cores/arduino -I$(NATIVE_ROOT)/src/system
$(eval $(call add_lib,$(NATIVE_ROOT)/src))

$(foreach lib, $(ARDUINO_LIBS), $(eval $(call add_lib,$(NATIVE_ROOT)/libraries/$(lib))))

OBJECTS += $(SRC_C:%.c=$(BUILD_ROOT)/%.o)
OBJECTS += $(SRC_CXX:%.cpp=$(BUILD_ROOT)/%.o)

INCLUDES += $(foreach d, $(INC_DIR), -I$d)

SRCS += $(SRC_C)
SRCS += $(SRC_CXX)

$(TARGET): $(OBJECTS)
	$(Q)$(CXX) $(OBJECTS) $(LDFLAGS) -o $@
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
