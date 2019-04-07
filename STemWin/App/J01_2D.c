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

void Shapes(void)
{
  //  GUI_SelectLayer(1);
    GUI_SetBkColor(GUI_DARKBLUE);
    GUI_Clear();
    GUI_SetColor(GUI_YELLOW);
    GUI_AA_SetFactor(6);
    GUI_SetPenSize(30);
//    GUI_DrawPoint(15, 15);                            // OK
//    GUI_AA_DrawPoint(15, 15);                            // Does not exist!
//    GUI_DrawLine(120, 15, 420, 40);                   // OK
//    GUI_AA_DrawLine(120, 30, 420, 55);                // OK
    GUI_DrawRect(30, 38, 60, 63);                   // BUG PenSize wrong

//    GUI_FillRect(20, 38, 100, 63);

    GUI_DrawRoundedRect(150, 75, 225, 125, 15);     // BUG PenSize wrong
//    GUI_AA_DrawRoundedRect(150, 75, 225, 125, 15);    // OK

//    GUI_FillRoundedRect(375, 75, 450, 125, 15);
//    GUI_AA_FillRoundedRect(375, 75, 450, 125, 15);

    GUI_DrawCircle(45, 150, 30);                   // BUG PenSize wrong
    GUI_AA_DrawCircle(240, 136, 100);                   // BUG Outside Edges Clipped Off

//    GUI_FillCircle(270, 150, 30);
//    GUI_AA_FillCircle(270, 150, 30);

//    GUI_DrawEllipse(120, 225, 75, 34);                // OK
//    GUI_AA_DrawEllipse(120, 225, 75, 34);                // Does not exist!

//    GUI_FillEllipse(360, 225, 75, 34);
//    GUI_AA_FillEllipse(360, 225, 75, 34);

//    GUI_DispStringHCenterAt("Shapes", 195, 225);
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

// https://forum.segger.com/index.php/Thread/5022-SSD1963-GUI-GetPixelIndex/
//U16 LCD_DEVFUNC_READPIXEL_CUSTOM(int LayerIndex)
//{
//  PortAPI.pfWrite16_A0(0x2e);
//  return PortAPI.pfRead16_A1();
//}
//
//void LCD_X_Config(void)
//
//{
//.
//.
//.
//.
//LCD_SetDevFunc(0, LCD_DEVFUNC_READPIXEL, LCD_DEVFUNC_READPIXEL_CUSTOM);
//
//}

