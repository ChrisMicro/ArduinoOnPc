/*
 * SerialConsole.cpp
 *
 *  Created on: 08.07.2017
 *      Author: christoph
 */

#include <unistd.h>
#include <stdio.h>
#include <sys/select.h>
#include "SerialConsole.h"
#include <queue>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>

std::queue < char > avaliableInput;
std::mutex inputMutex;
std::thread t1;
std::atomic<bool> active(true);

SerialConsole::SerialConsole()
{

}

void loadData() {
    while(active){
        char c = getchar();
        // Avoid race conditions
        std::lock_guard<std::mutex> guard(inputMutex);
        avaliableInput.push(c);
    }
}

void SerialConsole:: begin(const uint32_t baud)
{
    // Worker that reads from stdin.
    // This is needed so as not to block the main thread.
    active=true;
    t1 = std::thread(loadData);
    t1.detach();
}

void SerialConsole::end(void)
{
    /*Stop reading input. It will read 1 extra character but
     * thats inevitable*/
    active = false;
}

int SerialConsole::available(void)
{
    std::lock_guard<std::mutex> guard(inputMutex);
    return !avaliableInput.empty();
}

int SerialConsole::peek(void)
{
    if(available()) {
        std::lock_guard<std::mutex> guard(inputMutex);
        return avaliableInput.front();
    }
    return -1;
}

int SerialConsole::read(void)
{
    if(available()) {
        std::lock_guard<std::mutex> guard(inputMutex);
        char c = avaliableInput.front();
        avaliableInput.pop();
        return c;
    }
    return -1;
}

void SerialConsole::flush(void)
{
    fflush(stdin);
}

size_t SerialConsole::write(const uint8_t c)
{
    putchar(c);
    return 1;
}

SerialConsole Serial;

