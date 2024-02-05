#include <U8g2lib.h>

#include "DebugConfiguration.h"
#include "messages.xbm.h"
#include "messages_window.h"
#include "pager/display_manager.h"

namespace pager
{

void MessagesWindow::repaint(U8G2 &u8g2)
{
    u8g2.drawXBM(0, 0, messages_xbm_width, messages_xbm_height,
                 messages_xbm_bits);
}

void MessagesWindow::onStart() {}

void MessagesWindow::onStop() {}

void MessagesWindow::onEvent(int event) {}

}  // namespace pager