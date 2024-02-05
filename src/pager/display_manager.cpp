#include <FunctionalInterrupt.h>
#include <U8g2lib.h>

#include <array>
#include <functional>

#include "DebugConfiguration.h"
#include "display_manager.h"

namespace pager
{

constexpr BaseType_t kCpuCore = 0;
constexpr UBaseType_t kThreadPriority = 0;

namespace
{
/*
 * Bridge from raw function pointer to std::function for xTaskCreate.
 */
void startThread(void *param)
{
    auto fn = *static_cast<std::function<void()> *>(param);
    fn();
    vTaskDelete(NULL);
}
}  // namespace

void DisplayManager::init()
{
    LOG_INFO("[Pager DisplayManager] Start init.\n");
    initInputs();
    initScreen();
    xTaskCreatePinnedToCore(&startThread, "display_loop", 30000, &thread_fn,
                            kThreadPriority, &threadHandle, kCpuCore);

    LOG_INFO("[Pager DisplayManager] End init.\n");
}

void DisplayManager::initInputs()
{
    auto setupButton = [&](int pin, int id) {
        pinMode(pin, INPUT_PULLUP);
        interrupts[id] = std::bind(&DisplayManager::onDown, this, id);
        attachInterrupt(pin, interrupts[id], FALLING);
    };

    enum ButtonPin {
        RED = 33,
        GREEN = 34,
        UP = 26,
        DOWN = 48,
        LEFT = 47,
        RIGHT = 20
    };
    setupButton(ButtonPin::GREEN, Button::GREEN);
    setupButton(ButtonPin::RED, Button::RED);
    setupButton(ButtonPin::UP, Button::UP);
    setupButton(ButtonPin::DOWN, Button::DOWN);
    setupButton(ButtonPin::LEFT, Button::LEFT);
    setupButton(ButtonPin::RIGHT, Button::RIGHT);
}

/*
 * Caution! Interrupt handler. Must return quickly.
 */
void DisplayManager::onDown(int button)
{
    const int debounceMillis = 100;
    unsigned long now = millis();
    unsigned long last = button_debounce[button];
    if ((now - last) < debounceMillis) {
        return;
    }
    button_debounce[button] = now;
    button_state[button] = true;
    queued_input = button;
}

void DisplayManager::onUp(int button)
{
    // TODO: Bounce?
    button_state[button] = false;
}

void DisplayManager::initScreen()
{
    u8g2.begin();
    u8g2.clearBuffer();
    u8g2.sendBuffer();
}

void DisplayManager::thread()
{
    for (;;) {
        if (windows.empty()) {
            LOG_WARN("[Pager DisplayManager] No windows\n");
            continue;
        }
        auto &window = windows.top();
        // Send input events
        if (queued_input != Button::NONE) {
            window->onEvent(queued_input);
            queued_input = Button::NONE;
        }

        // Draw current top window
        u8g2.clearBuffer();
        window->repaint(u8g2);
        u8g2.sendBuffer();

        // Garbage collect closed windows.
        // TODO
    }
}

void DisplayManager::addWindow(int id, std::unique_ptr<Window> window)
{
    windows.push(std::move(window));
}

}  // namespace pager