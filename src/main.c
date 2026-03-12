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

void main(void)
{

    SMS_init();
    SMS_waitForVBlank();

    SMS_mapROMBank(map0_pal_bin_bank);
    SMS_loadBGPalette(map0_pal_bin);

    SMS_mapROMBank(map0_tileset_bin_bank);
    SMS_loadTiles(map0_tileset_bin, 8, map0_tileset_bin_size);

    SMS_mapROMBank(map0_tilemap_bin_bank);
    SMS_loadTileMap(0, 0, map0_tilemap_bin, map0_tilemap_bin_size);

    SMS_displayOn();

    while (1)
    {
        SMS_waitForVBlank();
    }
}
