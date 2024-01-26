#include "display_manager.h"

#include <U8g2lib.h>

#include <functional>

#include "DebugConfiguration.h"

namespace pager
{

constexpr BaseType_t kCpuCore = 0;
constexpr UBaseType_t kThreadPriority = 1;

void startThread(void *param)
{
    auto fn = *static_cast<std::function<void()> *>(param);
    fn();
    vTaskDelete(NULL);
}

void DisplayManager::initScreen()
{
    u8g2.begin();
    u8g2.clearBuffer();
    u8g2.sendBuffer();

    LOG_INFO("PAGER InitDisplay\n");
    xTaskCreatePinnedToCore(&startThread, "display_loop", 30000, &threadFn,
                            kThreadPriority, &threadHandle, kCpuCore);
}

void DisplayManager::thread()
{
    for (;;) {
        // TODO: Draw current top window
        // Send input events
        // Garbage collect closed windows
        u8g2.clearBuffer();
        for (auto &window : windows) {
            window->repaint(u8g2);
        }
        u8g2.sendBuffer();
    }
}

void DisplayManager::addWindow(int id, std::unique_ptr<Window> window)
{
    windows.push_back(std::move(window));
}

}  // namespace pager