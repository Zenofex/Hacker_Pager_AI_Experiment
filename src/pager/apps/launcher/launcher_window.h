#pragma once
#include <array>
#include <string>

#include "app_lora.xbm"
#include "app_lora_s.xbm"
#include "app_msg.xbm"
#include "app_msg_s.xbm"
#include "pager/window.h"

namespace pager
{

class LauncherWindow : public Window
{
   public:
    explicit LauncherWindow()
    {
        items[0] = {.width = app_msg_s_width,
                    .height = app_msg_height,
                    .icon = app_msg_bits,
                    .icon_selected = app_msg_s_bits};
        items[1] = {.width = app_lora_s_width,
                    .height = app_lora_height,
                    .icon = app_lora_bits,
                    .icon_selected = app_lora_s_bits};
    }

    void repaint(U8G2 &u8g2) override;

    void onEvent(int event) override;

    void onStart() override;

    void onStop() override;

   private:
    struct Item {
        int width;
        int height;
        unsigned char *icon;
        unsigned char *icon_selected;
    };

    int selected = 0;
    std::array<Item, 2> items;
};

}  // namespace pager