#include "GUI.h"

void J01_TextVersionString1(void)
{
  // Erase the screen
  InitNew();

  // Set the font
  GUI_SetFont(GUI_FONT_32_1);
  // Get the current font height
//  int textWidth = GUI_GetStringDistX(GUI_GetVersionString());
  int fsize = GUI_GetFontSizeY();
  int xPos = LCD_GetXSize() / 2;
  int yPos = (LCD_GetYSize() - yPos) / 2;
  GUI_SetColor(GUI_WHITE);
  GUI_DispStringHCenterAt(GUI_GetVersionString(), xPos, yPos - 10);
}

void J01_TextVersionString2(void)
{
  GUI_SetBkColor(GUI_BLUE);
  GUI_Clear();
  GUI_SetDrawMode(GUI_DM_NORMAL);
  GUI_SetColor(GUI_WHITE);
  GUI_DrawGradientV(20, 20, LCD_GetXSize() - 20, LCD_GetYSize() - 20, GUI_RED, GUI_YELLOW);
  int xPos = LCD_GetXSize() / 2;
  int yPos = LCD_GetYSize() / 2;
  GUI_SetTextMode(GUI_TM_TRANS);
  GUI_SetFont(GUI_FONT_COMIC24B_ASCII);
  GUI_DispStringHCenterAt("Hello Jack!", xPos, yPos - 30);
  GUI_DispStringHCenterAt("STemWin", xPos, yPos + 15);
  GUI_DispString(" ");
  GUI_DispString(GUI_GetVersionString());

  GUI_SetFont(&GUI_Font10S_ASCII);
  GUI_DispStringHCenterAt("Compiled " __DATE__ " "__TIME__, xPos, yPos + 60);

  GUI_SetTextMode(GUI_TM_NORMAL);
}

void J01_TextModes(void)
{
  InitNew();

//  GUI_SelectLayer(1);
  GUI_SetFont(&GUI_Font8x18);
  GUI_SetBkColor(GUI_BLUE);
  GUI_Clear();
  GUI_SetPenSize(10);
  GUI_SetColor(GUI_RED);
  GUI_DrawLine(100, 65, 380, 205);
  GUI_DrawLine(100, 205, 380, 65);
  GUI_SetBkColor(GUI_BLACK);
  GUI_SetColor(GUI_WHITE);
  GUI_SetTextMode(GUI_TM_NORMAL);
  GUI_DispStringHCenterAt("Text mode GUI_TM_NORMAL"            , 240, 70);
  GUI_SetTextMode(GUI_TM_REV);
  GUI_DispStringHCenterAt("Text mode GUI_TM_REV"               , 240, 100);
  GUI_SetTextMode(GUI_TM_TRANS);
  GUI_DispStringHCenterAt("Text mode GUI_TM_TRANS"             , 240, 130);
  GUI_SetTextMode(GUI_TM_XOR);
  GUI_DispStringHCenterAt("Text mode GUI_TM_XOR"               , 240, 160);
  GUI_SetTextMode(GUI_TM_TRANS | GUI_TM_REV);
  GUI_DispStringHCenterAt("Text mode GUI_TM_TRANS | GUI_TM_REV", 240, 190);
}

void DispFloat(void)
{
  //***** "floating point values" *********************************

//  GUI_SelectLayer(0);
  float f = 123.45678;
  GUI_Clear();
  GUI_SetBkColor(GUI_BLACK);
  GUI_SetColor(GUI_WHITE);
  GUI_SetTextMode(GUI_TM_NORMAL);
  GUI_SetFont(&GUI_Font8x16);
  GUI_DispStringAt("GUI_DispFloat:\n", 0, 20);
  GUI_DispFloat(f, 9);
  GUI_GotoX(100);
  GUI_DispFloat(-f, 9);
  GUI_DispStringAt("GUI_DispFloatFix:\n", 0, 60);
  GUI_DispFloatFix(f, 9, 2);
  GUI_GotoX(100);
  GUI_DispFloatFix(-f, 9, 2);
  GUI_DispStringAt("GUI_DispSFloatFix:\n", 0, 100);
  GUI_DispSFloatFix(f, 9, 2);
  GUI_GotoX(100);
  GUI_DispSFloatFix(-f, 9, 2);
  GUI_DispStringAt("GUI_DispFloatMin:\n", 0, 140);
  GUI_DispFloatMin(f, 3);
  GUI_GotoX(100);
  GUI_DispFloatMin(-f, 3);
  GUI_DispStringAt("GUI_DispSFloatMin:\n", 0, 180);
  GUI_DispSFloatMin(f, 3);
  GUI_GotoX(100);
  GUI_DispSFloatMin(-f, 3);

}

void J01_TextInBox(void)
{
  const char Text[] = "This text is wrapped in an rectangle.";
  GUI_RECT Rect = {0, 0, 160, 100};   // x0, y0, x1, y1
  // The height will be adjusted

  // Set the font
  GUI_SetFont(GUI_FONT_32_1);

  // Get the required number of lines using the available width
  int lines = GUI_WrapGetNumLines(Text, Rect.x1 - Rect.x0, GUI_WRAPMODE_WORD);

  // Get the current font height
  int fsize = GUI_GetFontSizeY();

  // Adjust vertical rectangle size
  Rect.y1 = Rect.y0 + lines * fsize;

  // Move the rectangle to the center of the display
  int shiftX = (LCD_GetXSize() - Rect.x1) / 2;
  int shiftY = (LCD_GetYSize() - Rect.y1) / 2;
  Rect.x0 += shiftX;
  Rect.y0 += shiftY;
  Rect.x1 += shiftX;
  Rect.y1 += shiftY;

  // Erase the screen
  GUI_SetBkColor(GUI_BLACK);
  GUI_Clear();

  // Draw a rounded rectangle, slightly bigger
  GUI_AA_SetFactor(6);
  GUI_SetPenSize(3);
  GUI_SetColor(GUI_BLUE);
  GUI_FillRoundedRect(Rect.x0 - 10, Rect.y0 - 10, Rect.x1 + 10, Rect.y1 + 10, 12);
  GUI_SetColor(GUI_WHITE);
  GUI_AA_DrawRoundedRect(Rect.x0 - 10, Rect.y0 - 10, Rect.x1 + 10, Rect.y1 + 10, 12);

  // Display the text inside the rectangle
  GUI_SetTextMode(GUI_TM_TRANS);
  GUI_SetTextStyle(GUI_TS_NORMAL);
  GUI_DispStringInRectWrap(Text, &Rect, GUI_TA_VCENTER, GUI_WRAPMODE_WORD);
}

void J01_TextRotated(void)
{
  const char Text[] = "Rotated\ntext";
  GUI_RECT Rect = {0, 0, 100, 100};   // x0, y0, x1, y1

  // Set the font
  GUI_SetFont(GUI_FONT_32_1);

  // Get the current font height
  int fsize = GUI_GetFontSizeY();

  int textWidth = GUI_GetStringDistX("Rotated");

  // Adjust vertical rectangle size
  int noOfLines = 2;
  Rect.x1 = Rect.x0 + noOfLines * fsize;
  Rect.y1 = Rect.y0 + textWidth;

  // Move the rectangle to the center of the display
  int shiftX = (LCD_GetXSize() - Rect.x1) / 2;
  int shiftY = (LCD_GetYSize() - Rect.y1) / 2;
  Rect.x0 += shiftX;
  Rect.y0 += shiftY;
  Rect.x1 += shiftX;
  Rect.y1 += shiftY;

  // Erase the screen
  GUI_SetBkColor(GUI_BLACK);
  GUI_Clear();

  GUI_AA_SetFactor(6);
  GUI_SetPenSize(3);
  GUI_SetColor(GUI_BLUE);
  GUI_FillRoundedRect(Rect.x0 - 10, Rect.y0 - 10, Rect.x1 + 10, Rect.y1 + 10, 12);
  GUI_SetColor(GUI_WHITE);
  GUI_AA_DrawRoundedRect(Rect.x0 - 10, Rect.y0 - 10, Rect.x1 + 10, Rect.y1 + 10, 12);

//  GUI_SetTextAlign(GUI_TA_TOP | GUI_TA_HCENTER);

  GUI_SetTextMode(GUI_TM_TRANS);
  GUI_SetTextStyle(GUI_TS_NORMAL);
  GUI_DispStringInRectEx(Text, &Rect, GUI_TA_HCENTER | GUI_TA_VCENTER, strlen(Text), GUI_ROTATE_CCW);

  J01_GUI_GetClientRect(&Rect);
  dmc_putintcr(Rect.x0);
  dmc_putintcr(Rect.x1);  // 16382
  dmc_putintcr(Rect.y0);
  dmc_putintcr(Rect.y1);  // 16382
}

void J01_GUI_GetClientRect(GUI_RECT *Rect)
{
  GUI_GetClientRect(Rect);
  if (Rect->x1 >= LCD_GetXSize())
  {
    Rect->x1 = LCD_GetXSize() - 1;
  }
  if (Rect->y1 >= LCD_GetYSize())
  {
    Rect->y1 = LCD_GetYSize() - 1;
  }
}
