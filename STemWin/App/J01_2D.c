#include <math.h>
#include "GUI.h"
#include <stdint.h>

uint32_t J01_GetPixel(int x, int y);

void J01_DrawAlpha1(void)
{
  GUI_SetColor(GUI_BLACK);
  GUI_Clear();

  GUI_SetFont(&GUI_Font32B_1);
//  GUI_SetFont(GUI_FONT_16_1);

  GUI_SetColor(GUI_WHITE);
  GUI_DispStringAt("Hello world!", (LCD_GetXSize()-100)/2, (LCD_GetYSize()-20)/2);
  HAL_Delay(1000);

  GUI_EnableAlpha(1);
  GUI_SetColor(0xa0400000); // Blue
  GUI_FillRect(0, 0, LCD_GetXSize() - 1, LCD_GetYSize() - 1);
  GUI_EnableAlpha(0);
  HAL_Delay(1000);

  GUI_SetTextMode(GUI_TM_TRANS);
  GUI_SetColor(GUI_WHITE);
  GUI_DispStringAt("Hello world!", (LCD_GetXSize()-100)/2, (LCD_GetYSize()-20)/2 + 30);
}

void J01_DrawAlpha2(void)
{
  GUI_EnableAlpha(0);
  GUI_SetBkColor(GUI_BLACK);
  GUI_Clear();

  GUI_SetColor(GUI_WHITE);
  GUI_SetFont(&GUI_Font32B_1);
  GUI_DispStringHCenterAt("This is alphablending", LCD_GetXSize()/2, LCD_GetYSize()/2);

  GUI_EnableAlpha(1);
  GUI_SetColor(GUI_MAKE_COLOR((0xC0uL << 24) | 0x0000FF));
//  GUI_SetAlpha(0xc0);
  GUI_FillRect(LCD_GetXSize()/2 - 100, LCD_GetYSize()/2 - 100, LCD_GetXSize()/2 + 20, LCD_GetYSize()/2 + 20);
  GUI_SetColor(GUI_MAKE_COLOR((0x80uL << 24) | 0x00FF00));
//  GUI_SetAlpha(0x80);
  GUI_FillRect(LCD_GetXSize()/2 - 60, LCD_GetYSize()/2 - 60, LCD_GetXSize()/2 + 60, LCD_GetYSize()/2 + 60);
  GUI_SetColor(GUI_MAKE_COLOR((0x40uL << 24) | 0xFF0000));
//  GUI_SetAlpha(0x40);
  GUI_FillRect(LCD_GetXSize()/2 - 20, LCD_GetYSize()/2 - 20, LCD_GetXSize()/2 + 100, LCD_GetYSize()/2 + 100);
  GUI_EnableAlpha(0);
}

void J01_DrawAlpha3(void)
{
  GUI_ALPHA_STATE AlphaState;

  GUI_EnableAlpha(0);
  GUI_SetBkColor(GUI_BLACK);
  GUI_Clear();

  GUI_SetColor(GUI_WHITE);
  GUI_SetFont(&GUI_Font32B_1);
  GUI_DispStringHCenterAt("This is alphablending", LCD_GetXSize()/2, LCD_GetYSize()/2);

  GUI_EnableAlpha(1);
//  GUI_SetUserAlpha(&AlphaState, 0xC0);
  GUI_SetColor(GUI_RED | 0x80000000);
  GUI_FillRect(LCD_GetXSize()/2 - 100, LCD_GetYSize()/2 - 100, LCD_GetXSize()/2 + 20, LCD_GetYSize()/2 + 20);
  GUI_SetColor(GUI_GREEN | 0x80000000);
  GUI_FillRect(LCD_GetXSize()/2 - 60, LCD_GetYSize()/2 - 60, LCD_GetXSize()/2 + 60, LCD_GetYSize()/2 + 60);
  GUI_SetColor(GUI_BLUE | 0x80000000);
  GUI_FillRect(LCD_GetXSize()/2 - 20, LCD_GetYSize()/2 - 20, LCD_GetXSize()/2 + 100, LCD_GetYSize()/2 + 100);
//  GUI_RestoreUserAlpha(&AlphaState);
  GUI_EnableAlpha(0);
}

void J01_Shapes(void)
{
  //  GUI_SelectLayer(1);
    GUI_SetBkColor(GUI_DARKBLUE);
    GUI_Clear();
    GUI_SetColor(GUI_YELLOW);
    GUI_AA_SetFactor(6);
    GUI_SetPenSize(6);
    GUI_DrawPoint(15, 15);                            // OK
//    GUI_AA_DrawPoint(15, 15);                            // Does not exist!
    GUI_DrawLine(120, 15, 420, 40);                   // OK
    GUI_AA_DrawLine(120, 30, 420, 55);                // OK
    GUI_DrawRect(30, 38, 60, 63);                   // BUG PenSize wrong

    GUI_FillRect(20, 38, 100, 63);

    GUI_DrawRoundedRect(150, 75, 225, 125, 15);     // BUG PenSize wrong
    GUI_AA_DrawRoundedRect(150, 75, 225, 125, 15);    // OK

    GUI_FillRoundedRect(375, 75, 450, 125, 15);
    GUI_AA_FillRoundedRect(375, 75, 450, 125, 15);

    GUI_DrawCircle(45, 150, 30);                   // BUG PenSize wrong
    GUI_AA_DrawCircle(240, 136, 100);                   // BUG Outside Edges Clipped Off

    GUI_FillCircle(270, 150, 30);
    GUI_AA_FillCircle(270, 150, 30);

    GUI_DrawEllipse(120, 225, 75, 34);                // OK
//    GUI_AA_DrawEllipse(120, 225, 75, 34);                // Does not exist!

    GUI_FillEllipse(360, 225, 75, 34);
    GUI_AA_FillEllipse(360, 225, 75, 34);

    GUI_DispStringHCenterAt("Shapes", 195, 225);
}

void J01_Sine(void)
{
  GUI_SetBkColor(GUI_BLACK);
  GUI_Clear();
  GUI_SetColor(GUI_WHITE);
  I16 aY[460];
  double step = 360.0/460.0;
  double angle = 0.0;
  for (int i = 0; i < GUI_COUNTOF(aY); i++) {
    aY[i] = sin(angle*2*M_PI/180) * -68 + 68;
    angle += step;
  }
  GUI_SetColor(0xff306890);
  GUI_SetPenSize(2);
  for (uint16_t y = 4; y < 272; y += 44)
  {
    GUI_DrawHLine(y, 10, 470);
  }
  for (uint16_t x = 10; x < 480; x += 46)
  {
    GUI_DrawVLine(x, 4, 268);
  }
  GUI_SetPenSize(6);
  GUI_SetColor(0xff00ff40);
  GUI_DrawGraph(aY, GUI_COUNTOF(aY), 10, 69);
  GUI_DrawGraph(aY, GUI_COUNTOF(aY), 10, 68);
  GUI_DrawGraph(aY, GUI_COUNTOF(aY), 10, 67);
  GUI_DrawGraph(aY, GUI_COUNTOF(aY), 10, 66);
}

void J01_BigDigits(void)
{
  GUI_SetBkColor(GUI_DARKBLUE);
  GUI_Clear();
  GUI_SetColor(GUI_YELLOW);
  GUI_SetFont(&GUI_FontD80);
  GUI_DispStringAt("1234.456", 10, 100);
}

void J01_PieChart(void)
{
  //  GUI_SelectLayer(1);
    GUI_SetBkColor(GUI_GRAY);
    GUI_Clear();
    GUI_SetPenSize(1);

    int a0, a1;
    const unsigned aValues[]  = { 100, 135, 190, 240, 340, 360};
    const GUI_COLOR aColors[] = { GUI_BLUE, GUI_GREEN,   GUI_RED,
        GUI_CYAN, GUI_MAGENTA, GUI_YELLOW };
    for (int i = 0; i < GUI_COUNTOF(aValues); i++) {
      a0 = (i == 0) ? 0 : aValues[i - 1];
      a1 = aValues[i];
      GUI_SetColor(aColors[i]);
      GUI_DrawPie(150, 136, 120, a0, a1, 0);
    }
    GUI_SetFont(&GUI_Font32_1);
    GUI_SetColor(GUI_WHITE);
    GUI_DispStringHCenterAt("Pie", 320, 150);
}

void J01_DrawModes(void)
{
  const GUI_POINT aPoints[] = {
    { 40, 20},
    {  0, 20},
    { 20,  0}
  };

  GUI_SetBkColor(GUI_GREEN);
  GUI_Clear();
  GUI_SetColor(GUI_RED);
  for (int i = 10; i <= 470; i += 10) {
    GUI_DrawLine(i, 30, i, 60);
//    HAL_Delay(20);
  };
  for (int i = 10; i < 50; i += 3) {
    GUI_DrawCircle(80, 160, i);
//    HAL_Delay(20);
  };
  GUI_SetColor(0x00FFFF00);
  for (int i = 0; i < 4; i += 1) {
    GUI_SetColor(0x000FFFF0 << i*0x6);
    GUI_FillCircle(200+(i*15),150+(i*15),30);
//    HAL_Delay(20);
  };
  for (int i = 0; i < 4; i += 1) {
    GUI_SetColor(0x000FFFF0 << i*0x6);
    GUI_AA_FillCircle(400+(i*15),150+(i*15),30);
//    HAL_Delay(20);
  };
  GUI_POINT aEnlargedPoints[GUI_COUNTOF(aPoints)];

  GUI_SetDrawMode(GUI_DM_XOR);
  GUI_FillPolygon(aPoints, GUI_COUNTOF(aPoints), 140, 110);
  for (int i = 1; i < 10; i++) {
    GUI_EnlargePolygon(aEnlargedPoints, aPoints, GUI_COUNTOF(aPoints), i * 5);
    GUI_FillPolygon(aEnlargedPoints, GUI_COUNTOF(aPoints), 140, 110);
  };
  GUI_SetDrawMode(GUI_DRAWMODE_NORMAL);
}

void J01_PixelIndex(void)
{
  uint32_t index;
  uint32_t color;
  // Erase the screen
  color = 0x00000000;
  dmc_puts("color 0: ");
  dmc_puthex8cr(color);
  GUI_SetBkColor(color);
  GUI_Clear();

  color = J01_GetPixel(60, 60);
  dmc_puts("color 0: ");
  dmc_puthex8cr(color);

  color = 0x000000FF;
  dmc_puts("color 1: ");
  dmc_puthex8cr(color);
  GUI_SetColor(color);
  GUI_FillRect(10, 10, 100, 100);

  color = J01_GetPixel(60, 60);
  dmc_puts("color 1: ");
  dmc_puthex8cr(color);

  color = 0x00FF0000;
  dmc_puts("color 2: ");
  dmc_puthex8cr(color);

  GUI_SetColor(color);
  GUI_DrawPixel(60, 60);

  color = J01_GetPixel(60, 60);
  dmc_puts("color 2: ");
  dmc_puthex8cr(color);

}

uint32_t J01_GetPixel(int x, int y)
{
  // GUIConf.h: #define GUI_USE_ARGB 1
  return GUI_Index2Color(GUI_GetPixelIndex(x, y)) & 0x00ffffff;
}

void J01_SetPixel(int x, int y, uint32_t color)
{
  GUI_SetColor(color);
  GUI_DrawPixel(60, 60);
}
