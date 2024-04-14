#pragma once
#include <U8g2lib.h>

#include <functional>
#include <memory>
#include <stack>

#include "graphics.h"
#include "window.h"

typedef U8G2_KS0108_SMR19264B_F U8G2Type;

namespace pager
{
const int SCREEN_WIDTH = 192;

/*
// Original screen: U8G2_ST7920_128X64_F_8080
u8g2(
          // rotation
          U8G2_R0,
          // d0, d1, d2, d3, d4, d5, d6, d7
          4, 3, 2, 38, 39, 40, 41, 42,
          // enable/E
          5,
          // CS
          U8X8_PIN_NONE,
          // dc/RS
          7),

// New screen: U8G2_KS0108_SMR19264B_F

Heltec devkit:
// d0, d1, d2, d3, d4, d5, d6, d7
4, 3, 2, 38, 39, 40, 41, 42,
// enable/E
5,
// DC/RS
7,
// CS0, CS1
45, 46,
// Reset
37

*/

class DisplayManager
{
   public:
    explicit DisplayManager()
        : u8g2(
              // rotation
              U8G2_R0,
              // d0, d1, d2, d3, d4, d5, d6, d7
              4, 5, 6, 7, 15, 16, 17, 18,
              // enable/E
              3,
              // DC/RS
              42,
              // CS0, CS1
              46, 45,
              // Reset
              U8X8_PIN_NONE),
          thread_fn(std::bind(&DisplayManager::thread, this))
    {
    }

    enum Button { NONE, RED, GREEN, UP, DOWN, LEFT, RIGHT, BUTTON_LENGTH };

    void init();

    void addWindow(int id, std::unique_ptr<Window> window);

   private:
    U8G2Type u8g2;
    std::function<void()> thread_fn;
    TaskHandle_t threadHandle;
    std::stack<std::unique_ptr<pager::Window>> windows;
    std::array<bool, Button::BUTTON_LENGTH> button_state = {};
    std::array<unsigned long, Button::BUTTON_LENGTH> button_debounce = {};
    int queued_input = Button::NONE;

    unsigned long start_time = 0;

    std::array<std::function<void()>, Button::BUTTON_LENGTH> interrupts;

    void thread();

    void initScreen();
    void initInputs();
    void onDown(int button);
    void onUp(int button);
};

}  // namespace pager