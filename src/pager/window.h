#pragma once
#include <U8g2lib.h>

#include "graphics.h"
namespace pager
{

class Window
{
   public:
    explicit Window() {}

    void repaint(U8G2Type& u8g2);

    void onEvent(int event);

    void onStart();

    void onStop();

   private:
};

}  // namespace pager