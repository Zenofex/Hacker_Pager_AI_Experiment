#include "pager_main.h"

#include <U8g2lib.h>

#include <memory>

#include "display_manager.h"
#include "graphics.h"

std::unique_ptr<pager::DisplayManager> displayManager;

// U8G2Type u8g2(
//     // rotation
//     U8G2_R0,
//     // d0, d1, d2, d3, d4, d5, d6, d7
//     4, 3, 2, 38, 39, 40, 41, 42,
//     // enable/E
//     5,
//     // CS
//     U8X8_PIN_NONE,
//     // dc/RS
//     7);

void pager_setup()
{
    // Set up the LCD and UI thread.
    displayManager =
        std::unique_ptr<pager::DisplayManager>(new pager::DisplayManager());
    displayManager->initScreen();

    std::unique_ptr<pager::Window> root(new pager::Window());
    displayManager->addWindow(0, std::move(root));

    //     u8g2.begin();
    //     u8g2.setFont(u8g2_font_6x12_tf);
    //     u8g2.clearBuffer();
    //     u8g2.sendBuffer();
    //     u8g2.drawStr(25, 20, "DisplayManager Test");
    //     u8g2.drawStr(0, 40, "HACK THE PLANET");
    //     u8g2.sendBuffer();
}
