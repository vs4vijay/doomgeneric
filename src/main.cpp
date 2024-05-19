// #include "doomgeneric.h"
#include "../doomgeneric/doomgeneric.h"
#include <M5Cardputer.h>
#include <M5Unified.h>
#include <M5GFX.h>

#define KEYQUEUE_SIZE 16

static unsigned short s_KeyQueue[KEYQUEUE_SIZE];
static unsigned int s_KeyQueueWriteIndex = 0;
static unsigned int s_KeyQueueReadIndex = 0;

void DG_Init()
{
  M5.begin();
  // Initialize M5Stack Cardputer
}

void DG_DrawFrame()
{
  M5.Lcd.drawBitmap(0, 0, DOOMGENERIC_RESX, DOOMGENERIC_RESY, (uint16_t *)DG_ScreenBuffer);
}

void DG_SleepMs(uint32_t ms)
{
  delay(ms);
}

uint32_t DG_GetTicksMs()
{
  return millis();
}

// int DG_GetKey(int* pressed, unsigned char* key) {
//   *pressed = 0;
//   *key = 0;

//   if(M5.BtnA.wasPressed()) {
//     *pressed = 1;
//     *key = KEY_ENTER;
//     return 1;
//   }
//   else if(M5.BtnB.wasPressed()) {
//     *pressed = 1;
//     *key = KEY_FIRE;
//     return 1;
//   }
//   else if(M5.BtnC.wasPressed()) {
//     *pressed = 1;
//     *key = KEY_USE;
//     return 1;
//   }

//   return 0;
// }

int DG_GetKey(int *pressed, unsigned char *doomKey)
{
  if (s_KeyQueueReadIndex == s_KeyQueueWriteIndex)
  {
    // key queue is empty
    return 0;
  }
  else
  {
    unsigned short keyData = s_KeyQueue[s_KeyQueueReadIndex];
    s_KeyQueueReadIndex++;
    s_KeyQueueReadIndex %= KEYQUEUE_SIZE;

    *pressed = keyData >> 8;
    *doomKey = keyData & 0xFF;

    return 1;
  }

  return 0;
}

// void setup() {
//   // Initialization code here
// }

// void loop() {
//   // You can leave this empty if not needed
// }

int main(int argc, char **argv)
{
  doomgeneric_Create(argc, argv);

  while (1)
  {
    doomgeneric_Tick();
  }

  return 0;
}