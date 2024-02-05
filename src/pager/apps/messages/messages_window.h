#pragma once
#include "pager/window.h"

namespace pager
{

class MessagesWindow : public Window
{
   public:
    explicit MessagesWindow() {}

    void repaint(U8G2& u8g2);

    void onEvent(int event);

    void onStart();

    void onStop();

   private:
};

}  // namespace pager