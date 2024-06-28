IN-DEVELOPMENT

# M5 Doom

Relive the Classic Doom Experience on Your M5Cardputer!

Welcome to the Doom port for M5 Stack devices, specifically for M5Cardputer! This project aims to bring the classic Doom experience to the M5 Stack platform, allowing you to relive the iconic game on modern hardware.

---

The purpose of doomgeneric is to make porting Doom easier.
Of course Doom is already portable but with doomgeneric it is possible with just a few functions.

To try it you will need a WAD file (game data). If you don't own the game, shareware version is freely available (doom1.wad).

- https://doomwiki.org/wiki/DOOM1.WAD
- https://freedoom.github.io/index.html
- Miniwad

---

## Compiling 

```bash

# Windows with SDL
make -j4 -f Makefile.sdl
```

---

## Running

```bash

# Windows with SDL
./doomgeneric.exe -iwad doom1.wad
./doomgeneric.exe -iwad miniwad.wad

```

---

## Porting to M5Stack CardPuter

To bring the classic Doom experience to your M5Stack CardPuter, follow these setup instructions:

### Hardware Requirements

- M5Stack CardPuter
- SD card with at least 16MB of free space
- USB-C cable for programming and power supply

### Compiling and Uploading

1. Install [PlatformIO](https://platformio.org/) and the necessary ESP32 platform support.
2. Clone this repository to your local machine.
3. Place your WAD file (e.g., `doom1.wad`) in the root of the SD card and insert it into the M5Stack CardPuter.
4. Navigate to the project directory and open the `platformio.ini` file. Ensure the correct environment is selected for your M5Stack CardPuter model.
5. Compile the project by running `pio run` in the terminal.
6. Upload the game to your M5Stack CardPuter using `pio run --target upload`.
7. Once uploaded, reset the M5Stack CardPuter to start playing Doom!

Enjoy Doom on your M5Stack CardPuter and relive the classic gaming experience!

---

## porting
Create a file named doomgeneric_yourplatform.c and just implement these functions to suit your platform.
* DG_Init
* DG_DrawFrame
* DG_SleepMs
* DG_GetTicksMs
* DG_GetKey

|Functions            |Description|
|---------------------|-----------|
|DG_Init              |Initialize your platfrom (create window, framebuffer, etc...).
|DG_DrawFrame         |Frame is ready in DG_ScreenBuffer. Copy it to your platform's screen.
|DG_SleepMs           |Sleep in milliseconds.
|DG_GetTicksMs        |The ticks passed since launch in milliseconds.
|DG_GetKey            |Provide keyboard events.
|DG_SetWindowTitle    |Not required. This is for setting the window title as Doom sets this from WAD file.

### main loop
At start, call doomgeneric_Create().

In a loop, call doomgeneric_Tick().

In simplest form:
```
int main(int argc, char **argv)
{
    doomgeneric_Create(argc, argv);

    while (1)
    {
        doomgeneric_Tick();
    }
    
    return 0;
}
```

## sound
Sound is much harder to implement! If you need sound, take a look at SDL port. It fully supports sound and music! Where to start? Define FEATURE_SOUND, assign DG_sound_module and DG_music_module.

## platforms
Ported platforms include Windows, X11, SDL, emscripten. Just look at (doomgeneric_win.c, doomgeneric_xlib.c, doomgeneric_sdl.c).
Makefiles provided for each platform.

### emscripten
You can try it directly here:
https://ozkl.github.io/doomgeneric/

emscripten port is based on SDL port, so it supports sound and music! For music, timidity backend is used.

### Windows
![Windows](screenshots/windows.png)

### X11 - Ubuntu
![Ubuntu](screenshots/ubuntu.png)

### X11 - FreeBSD
![FreeBSD](screenshots/freebsd.png)

### SDL
![SDL](screenshots/sdl.png)
