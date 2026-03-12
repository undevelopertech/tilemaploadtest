#include <stdint.h>
#include <stdbool.h>
// include SMSlib (DevkitSMS) - see https://github.com/sverx/devkitSMS for docs
#include "SMSlib.h"
#ifdef USEPSGLIB // Set USEPSGLIB := true in Makefile to build with PSGlib for music and sounds
// include PSGlib (DevkitSMS) - see https://github.com/sverx/devkitSMS/tree/master/PSGlib for docs
#include "PSGlib.h"
#endif
#include "rom.h"
#include "assets.h"

static void expand_sms_palette_to_gg(uint8_t *sms_palette, uint8_t *gg_palette, uint8_t num_colors)
{
    // !WB: not sure how efficient this actually turns out to be, but hey...
    for (uint8_t i = 0; i < num_colors; i++)
    {
        register uint8_t byte0 = *(sms_palette++);    // xxbbggrr
        register uint8_t byte1 = (byte0 >> 4) & 0x03; // 000000bb
        byte0 = (byte0 & 0x03) | (byte0 << 2);        // bbggrrrr
        byte0 = (byte0 & 0x3f) | (byte0 << 2);        // ggggrrrr
        *(gg_palette++) = byte0;
        byte1 = byte1 | (byte1 << 2); // 0000bbbb
        *(gg_palette++) = byte1;
    }
}

void main(void)
{

    SMS_init();
    SMS_waitForVBlank();

    SMS_mapROMBank(map0_pal_bin_bank);

    // !WB: convert SMS palette to GG palette
    uint8_t gg_palette[map0_pal_bin_size * 2];
    expand_sms_palette_to_gg((uint8_t *)&map0_pal_bin, (uint8_t *)&gg_palette, map0_pal_bin_size);
    // !WB: now load the expaneded GG palette to the VDP
    GG_loadBGPalette(gg_palette);

    SMS_mapROMBank(map0_tileset_bin_bank);
    // SMS_loadTiles(map0_tileset_bin, 8, map0_tileset_bin_size);
    SMS_loadTiles(map0_tileset_bin, 0, map0_tileset_bin_size);

    SMS_mapROMBank(map0_tilemap_bin_bank);

    // !WB: copy the tilemap to just the GG visible portion of the screen
    // SMS_loadTileMap(0, 0, map0_tilemap_bin, map0_tilemap_bin_size);
    SMS_loadTileMapArea(6, 3, map0_tilemap_bin, 20, 18);

    SMS_displayOn();

    while (1)
    {
        SMS_waitForVBlank();
    }
}
