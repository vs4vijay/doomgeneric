#include "doomkeys.h"
#include "m_argv.h"
#include "doomgeneric.h"

#include <M5Unified.h>
#include <M5Cardputer.h>
#include <M5GFX.h>

#define KEYQUEUE_SIZE 16

static unsigned short s_KeyQueue[KEYQUEUE_SIZE];
static unsigned int s_KeyQueueWriteIndex = 0;
static unsigned int s_KeyQueueReadIndex = 0;

static unsigned char convertToDoomKey(unsigned int key)
{
  switch (key)
  {
  case M5Cardputer::Key::Enter:
    return KEY_ENTER;
  case M5Cardputer::Key::Escape:
    return KEY_ESCAPE;
  case M5Cardputer::Key::Left:
    return KEY_LEFTARROW;
  case M5Cardputer::Key::Right:
    return KEY_RIGHTARROW;
  case M5Cardputer::Key::Up:
    return KEY_UPARROW;
  case M5Cardputer::Key::Down:
    return KEY_DOWNARROW;
  case M5Cardputer::Key::Ctrl:
    return KEY_FIRE;
  case M5Cardputer::Key::Space:
    return KEY_USE;
  case M5Cardputer::Key::Shift:
    return KEY_RSHIFT;
  default:
    return tolower(key);
  }
}

static void addKeyToQueue(int pressed, unsigned int keyCode)
{
  unsigned char key = convertToDoomKey(keyCode);
  unsigned short keyData = (pressed << 8) | key;

  s_KeyQueue[s_KeyQueueWriteIndex] = keyData;
  s_KeyQueueWriteIndex++;
  s_KeyQueueWriteIndex %= KEYQUEUE_SIZE;
}

static void handleKeyInput()
{
  M5Cardputer::KeyEvent e;
  while (M5Cardputer::pollEvent(e))
  {
    if (e.type == M5Cardputer::KeyEvent::KeyDown)
    {
      addKeyToQueue(1, e.key);
    }
    else if (e.type == M5Cardputer::KeyEvent::KeyUp)
    {
      addKeyToQueue(0, e.key);
    }
  }
}

void DG_Init()
{
  M5.begin();
  M5Cardputer::begin();
  M5GFX::begin();
}

void DG_DrawFrame()
{
  M5GFX::drawBitmap(0, 0, DOOMGENERIC_RESX, DOOMGENERIC_RESY, DG_ScreenBuffer);
  handleKeyInput();
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
}

void DG_SetWindowTitle(const char *title)
{
  // No window title to set for M5Stack Cardputer
}

int main(int argc, char **argv)
{
  doomgeneric_Create(argc, argv);

  for (;;)
  {
    doomgeneric_Tick();
  }

  return 0;
}
