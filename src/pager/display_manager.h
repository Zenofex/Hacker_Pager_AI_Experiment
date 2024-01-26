#pragma once
#include <U8g2lib.h>

#include <functional>
#include <memory>
#include <vector>

#include "graphics.h"
#include "window.h"

namespace pager
{

class DisplayManager
{
   public:
    explicit DisplayManager()
        : u8g2(
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
          threadFn(std::bind(&DisplayManager::thread, this))
    {
    }

    void initScreen();
    void addWindow(int id, std::unique_ptr<Window> window);

   private:
    U8G2Type u8g2;
    std::function<void()> threadFn;
    TaskHandle_t threadHandle;
    std::vector<std::unique_ptr<pager::Window>> windows;
    void thread();
};

}  // namespace pager