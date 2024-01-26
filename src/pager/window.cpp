#include "window.h"

#include <U8g2lib.h>

#include "DebugConfiguration.h"
#include "display_manager.h"

namespace pager
{

uint32_t pos = 0;
void Window::repaint(U8G2Type &u8g2)
{
    u8g2.setFont(u8g2_font_6x12_tf);
    u8g2.drawStr(25, 20, "GRAND CENTRAL");
    u8g2.drawStr(pos, 40, "HACK THE PLANET");
    pos = (pos + 1) & 0x7F;
}

void Window::onStart() {}

void Window::onStop() {}

void Window::onEvent(int event) {}

}  // namespace pager