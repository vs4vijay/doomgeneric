#include "doomgeneric.h"
#include <M5Cardputer.h>
#include <M5Unified.h>
#include <M5GFX.h>

#define KEYQUEUE_SIZE 16

static unsigned short s_KeyQueue[KEYQUEUE_SIZE];
static unsigned int s_KeyQueueWriteIndex = 0;
static unsigned int s_KeyQueueReadIndex = 0;

#ifdef __cplusplus
extern "C"
{
#endif

  void doomgeneric_Create(int argc, char **argv);
  void doomgeneric_Tick();

#ifdef __cplusplus
}
#endif

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

void setup()
{
  doomgeneric_Create(0, nullptr);
}

void loop()
{
  doomgeneric_Tick();
}

// int main(int argc, char **argv)
// {
//   doomgeneric_Create(argc, argv);

//   while (1)
//   {
//     doomgeneric_Tick();
//   }

//   return 0;
// }
