  /**
  ******************************************************************************
  * @file    GUI_App.c
  * @author  MCD Application Team
  * @brief   Simple demo drawing "Hello world"  
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright © 2018 STMicroelectronics International N.V. 
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#include <dmc_prng.h>
#include <math.h>
#include <touch.h>
#include <WM.h>
#include "GUI_App.h"
#include "GUI.h"

#include "stm32746g_discovery.h"
#include "stm32746g_discovery_ts.h"

//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 100)

int i=0;
int xPos, yPos;

const GUI_POINT aPoints[] = {
  { 40, 20},
  {  0, 20},
  { 20,  0}
};


GUI_PID_STATE PollTouchScreen(void)
{
  GUI_PID_STATE TS_State;               /* Structure that reports the touch state to STemWin */
  static TS_StateTypeDef prev_state;    /* Previous touch state from the touch sensor used from BSP package */
  TS_StateTypeDef ts;                   /* Actual touch state from the touch sensor used from BSP package */
  BSP_TS_GetState(&ts);                 /* Read the touch state from touch sensor (BSP API) */
  TS_State.Pressed = ts.touchDetected;  /* Store pressed state to STemWin structure */

  if (prev_state.touchDetected != ts.touchDetected)
  {
//    dmc_putc('.');
    prev_state.touchDetected != ts.touchDetected;
    /* Check touch variations */
    if((ts.touchX[0] != 0) &&  (ts.touchY[0] != 0))
    {
      prev_state.touchX[0] = ts.touchX[0];
      prev_state.touchY[0] = ts.touchY[0];
    }
    TS_State.Layer = 0;
    TS_State.x = prev_state.touchX[0];
    TS_State.y = prev_state.touchY[0];

//    dmc_putint((uint16_t)TS_State.x);
//    dmc_putc(' ');
//    dmc_putint((uint16_t)TS_State.y);
//    dmc_putcr();

    /* Send touch state to STemWin */
    GUI_TOUCH_StoreStateEx(&TS_State);

  }
  return TS_State;
}

void InitNew(void)
{
  GUI_Init();

  GUI_SetBkColor(GUI_BLACK);
  GUI_Clear();
  GUI_EnableAlpha(0);
  GUI_SetTextMode(GUI_TM_NORMAL);
  GUI_SetColor(GUI_WHITE);
  GUI_SetFont(GUI_FONT_32_1);
  GUI_AA_SetFactor(6);
  //  GUI_AA_EnableHiRes();
  GUI_AA_DisableHiRes();
}

void loop(void)
{
  uint16_t delay = 2000;



  //***** "Shapes" *********************************
  InitNew();

  //***** "Graph" ****************************************

//  GUI_SelectLayer(0);
  GUI_SetBkColor(GUI_BLACK);
  GUI_Clear();
  GUI_SetColor(GUI_WHITE);
  I16 aY[460];
  int i;
  double step = 360.0/460.0;
  double angle = 0.0;
  for (i = 0; i < GUI_COUNTOF(aY); i++) {
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
  HAL_Delay(delay*4);

  //***** "Graph" ****************************************

//  GUI_SetBkColor(GUI_DARKGREEN);
//  GUI_Clear();
//  GUI_SetColor(GUI_WHITE);
//
//  I16 aY[200];
//  int i;
//
//
//  int px[20];
//  int py[20];
//
//  for (i = 0; i < GUI_COUNTOF(px); i++) {
//    px[i] = i * 20;
//    py[i] = rnd() % 150;
//  }
//  GUI_HMEM hSpline = GUI_SPLINE_Create(px, py, GUI_COUNTOF(px));
//  UI_SPLINE_Draw(hSpline, 45, 45);
//
////  GUI_DrawGraph(aY, GUI_COUNTOF(aY), 50, 50);
////  GUI_DrawHLine(205, 45, 250);
////  GUI_DrawVLine(45, 45, 200);
//  GUI_DispStringHCenterAt("Graph",250,210);
//  HAL_Delay(5000);

  //***** "Pie" ****************************************

  InitNew();

//  GUI_SelectLayer(1);
  GUI_SetBkColor(GUI_GRAY);
  GUI_Clear();
  GUI_SetPenSize(1);

  int a0, a1;
  const unsigned aValues[]  = { 100, 135, 190, 240, 340, 360};
  const GUI_COLOR aColors[] = { GUI_BLUE, GUI_GREEN,   GUI_RED,
      GUI_CYAN, GUI_MAGENTA, GUI_YELLOW };
  for (i = 0; i < GUI_COUNTOF(aValues); i++) {
    a0 = (i == 0) ? 0 : aValues[i - 1];
    a1 = aValues[i];
    GUI_SetColor(aColors[i]);
    GUI_DrawPie(150, 136, 120, a0, a1, 0);
  }
  GUI_SetColor(GUI_WHITE);
  GUI_DispStringHCenterAt("Pie", 320, 150);
  HAL_Delay(delay);

  //***** "Miscellaneous" *********************************

  InitNew();

//  GUI_SelectLayer(0);
  GUI_SetBkColor(GUI_GREEN);
  GUI_Clear();
  GUI_SetColor(GUI_RED);
  for (i = 10; i <= 470; i += 10) {
    GUI_DrawLine(i, 30, i, 60);
//    HAL_Delay(20);
  };
  for (i = 10; i < 50; i += 3) {
    GUI_DrawCircle(80, 160, i);
//    HAL_Delay(20);
  };
  GUI_SetColor(0x00FFFF00);
  for (i = 0; i < 4; i += 1) {
    GUI_SetColor(0x000FFFF0 << i*0x6);
    GUI_FillCircle(200+(i*15),150+(i*15),30);
//    HAL_Delay(20);
  };
  GUI_POINT aEnlargedPoints[GUI_COUNTOF(aPoints)];

  GUI_SetDrawMode(GUI_DM_XOR);
  GUI_FillPolygon(aPoints, GUI_COUNTOF(aPoints), 140, 110);
  for (i = 1; i < 10; i++) {
    GUI_EnlargePolygon(aEnlargedPoints, aPoints, GUI_COUNTOF(aPoints), i * 5);
    GUI_FillPolygon(aEnlargedPoints, GUI_COUNTOF(aPoints), 140, 110);
  };
  HAL_Delay(delay);

  GUI_SetBkColor(GUI_DARKBLUE);
  GUI_Clear();
  GUI_SetColor(GUI_YELLOW);
  GUI_SetFont(&GUI_FontD80);
  GUI_DispStringAt("1234.456", 10, 100);
  HAL_Delay(delay);

//  InitNew();
//
//  // Lines
//  int16_t x[361];
//  int16_t y[361];
//  for (uint16_t i = 0; i <= 360; i++)
//  {
//    x[i] = sin(i*M_PI/-180) * 125;
//    y[i] = cos(i*M_PI/-180) * 125;
//  }
//  GUI_SetBkColor(GUI_DARKBLUE);
//  GUI_Clear();
//  GUI_SetPenSize(2);
//  GUI_SetColor(GUI_LIGHTGREEN);
//  uint8_t layer = 0;
//  for (uint16_t i = 0; i <= 360; i++)
//  {
////    GUI_SelectLayer(layer);
////    layer ^= 1;
//
//    GUI_DrawLine(240, 136, 240+x[i], 136+y[i]);
////    HAL_Delay(10);
//  }
//  HAL_Delay(delay);
}

//extern WM_HWIN CreateWindow(void);


void GRAPHICS_MainTask(void)
{
  /* USER CODE BEGIN GRAPHICS_MainTask */

//  static GUI_PID_STATE pid_state;
//  TP_STATE *touch_state;
//  uint8_t last_state = 0;
//
//  GUI_UC_SetEncodeUTF8();
//  GUI_CURSOR_Show();
//  CreateFramewin();
//  /* User can implement his graphic application here */
//  /* Hello Word example */
//  GUI_Clear();
//  GUI_SetColor(GUI_BLUE);
//  GUI_SetFont(&GUI_Font32_1);
//  GUI_DispStringHCenterAt("Hello World", LCD_GetXSize() / 2, LCD_GetYSize() / 2 + 100);
//  if (Touch_Config() == HAL_OK)
//  {
//  }
//  /* USER CODE END GRAPHICS_MainTask */
//  while (1)
//  {
//    PollTouchScreen();
//    GUI_Delay(20);
//    touch_state = IOE_TP_GetState();
//    if(touch_state->TouchDetected)
//    {
//      pid_state.x = touch_state->X;
//      pid_state.y = touch_state->Y;
//      pid_state.Pressed = 1;
//      GUI_PID_StoreState(&pid_state);
////      GUI_AA_DrawLine(0, 0, pid_state.x, pid_state.y);
//
//      last_state = 1;
//    }
//    else
//    {
//      if(last_state)
//      {
//        last_state = 0;
//        pid_state.x = touch_state->X;
//        pid_state.y = touch_state->Y;
//        pid_state.Pressed = 0;
//        GUI_PID_StoreState(&pid_state);
//      }
//    }
//  }







//  WM_MULTIBUF_Enable(1);
//  WM_SetSize();

  GUI_Init();

  // Check if recommended memory for the sample is available
  //
//  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
//    GUI_ErrorOut("Not enough memory available.");
//    return;
//  }
//  while (1) {
//    _DemoAntialiasing();
//  }

//  _DemoBarGraph();
//  while (1) {
//    GUI_Delay(100);
//  }

//  HAL_Delay(10000);

  //
  // Check if recommended memory for the sample is available
  //
//  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
//    GUI_ErrorOut("Not enough memory available.");
//    return;
//  }
//  GUI_EnableAlpha(1);
//  while (1) {
//    GUI_Delay(100);
//  }

//  GUI_CURSOR_Show();


//  GUI_MULTIBUF_Config(2);

  //
  // Create edit widget
  //
//  WM_HWIN hWin;
//  int MaxSize = 20;
//  uint8_t pPath[] = "Hello        ";
//
//  hWin = EDIT_Create(10, 120, 300, 20, 0, MaxSize, WM_CF_SHOW);
//
//  EDIT_SetText(hWin, pPath);
//  WM_SetFocus(hWin);
//  //
//  // Wait until GUI_KEY_ENTER has been pressed
//  //
////  while (GUI_GetKey() != GUI_KEY_ENTER) {
////    GUI_Delay(100);
////  }
//  //
//  // Get filename from EDIT widget
//  //
//  EDIT_GetText(hWin, pPath, MaxSize);
//  dmc_putscr(pPath);
//  //
//  // Create edit widget
//  //
//  WM_DeleteWindow(hWin);
//
//  GUI_ClearRect(0, 40, 319, 239);



//  int ySize;
//  int FontHeight;
//
//  GUI_Init();
//  //
//  // Check if recommended memory for the sample is available
//  //
//  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
//    GUI_ErrorOut("Not enough memory available.");
//    return;
//  }
//  //
//  // Draw message
//  //
//  ySize = LCD_GetYSize();
//  GUI_SetFont(&GUI_Font20_ASCII);
//  FontHeight = GUI_GetFontSizeY();
//  GUI_DispStringHCenterAt(_acMessageTop, 160, 5);
//  GUI_DispStringHCenterAt(_acMessageBottom, 160, ySize - FontHeight * 2 - 5);
//  //
//  // Draw stripes on layer 0
//  //
//  GUI_SelectLayer(0);
//  _DrawStripes(50);
//  //
//  // Fill layer 1 with transparency and draw alpha image
//  //
////  GUI_SelectLayer(1);
//  GUI_SetBkColor(GUI_TRANSPARENT);
////  GUI_Clear();
//  _DrawImage();
////  while (1) {
////    GUI_Delay(100);
////  }
//



//  HAL_Delay(10000);

//
//
////  GUI_SetOrientation(GUI_SWAP_XY);
//
//  printf("Hi\n");
//
////  GUI_MULTIBUF_Begin();
//
//
////  WM_HWIN hWin;
//
////  hWin = CreateWindow();
////   WM_ShowWindow(hWin);
//
////   while(1);
//
///* USER CODE BEGIN GRAPHICS_MainTask */
// /* User can implement his graphic application here */
//  /* Hello Word example */
//  GUI_SetBkColor(GUI_BLACK);
//  GUI_Clear();
//
//  GUI_AA_EnableGammaAA4(GUI_AA_TRANS);
//  GUI_AA_EnableHiRes();
//  GUI_AA_DisableHiRes();
//
//  GUI_EnableAlpha(0);
////  GUI_SetAlpha(0xe0);
////  GUI_SetUserAlpha();
//
//  int aa = 1;
//  //  GUI_AA_EnableHiRes();
//  //  GUI_AA_DisableHiRes();
//  GUI_AA_SetFactor(6);
//
//  GUI_AA_EnableHiRes();
//  GUI_AA_SetDrawMode(GUI_AA_NOTRANS);
//
//  GUI_SetColor(GUI_RED);
//  GUI_SetFont(&GUI_Font16_1);
//  GUI_DispStringAt("Hello world!", (LCD_GetXSize()-150)/2, (LCD_GetYSize()-80)/2);
//
//  GUI_SetColor(GUI_GREEN);
//  GUI_SetFont(&GUI_Font24_1);
//  GUI_DispStringAt("Hello world!", (LCD_GetXSize()-150)/2, (LCD_GetYSize()-20)/2);
//
//  GUI_SetColor(GUI_BLUE);
//  GUI_SetFont(&GUI_FontD80);
//  GUI_DispStringAt("0123456789", (LCD_GetXSize()-200)/2, (LCD_GetYSize()+60)/2);
//
////  GUI_Delay(100);
//  GUI_SetColor(GUI_WHITE);
//  GUI_SetFont(&GUI_Font16_1);
//  for (uint16_t y = 0; y < LCD_GetYSize(); y+=20)
//  {
////    GUI_Delay(100);
//    GUI_DispStringAt("Hello world!", 10, y+10);
//  }
//
//
//  GUI_AA_SetGammaAA4(0x40);
//
//  GUI_SetPenSize(3);
//
//  GUI_SetColor(GUI_LIGHTRED);
//  GUI_AA_DrawLine(40, 40, LCD_GetXSize()*aa - 40, LCD_GetYSize()*aa - 40);
//  GUI_AA_DrawLine(40, LCD_GetYSize()*aa - 40, LCD_GetXSize()*aa - 40, 40);
////  GUI_DrawLine(10, LCD_GetYSize() - 10, LCD_GetXSize() - 10, 10);
//
//  GUI_SetColor(GUI_LIGHTGREEN);
////  GUI_DrawCircle(LCD_GetXSize()/2, LCD_GetYSize()/2, 80);
////  GUI_AA_DrawCircle(LCD_GetXSize()/2*aa, LCD_GetYSize()/2*aa, 80*aa);
//  GUI_AA_DrawArc(LCD_GetXSize()/2*aa, LCD_GetYSize()/2*aa, 80*aa, 80*aa, 0, 270);
//
//
//  GUI_SetColor(GUI_LIGHTBLUE);
//  GUI_AA_FillCircle(LCD_GetXSize()/4*aa, LCD_GetYSize()/2*aa, 35*aa);
//
////  GUI_SetColor(GUI_LIGHTMAGENTA);
//  GUI_SetColor(0xFFFF80FF);
//
////  GUI_AA_FillRoundedRect(200*aa, 100*aa, 280*aa, 156*aa, 10*aa);
//  GUI_AA_DrawRoundedRect(200*aa, 100*aa, 280*aa, 156*aa, 10*aa);

//  GUI_DrawPixel(240, 20);

//  GUI_MULTIBUF_End();

/* USER CODE END GRAPHICS_MainTask */
//  GUI_MULTIBUF_Begin();
//  GUI_SetBkColor(GUI_BLACK);
//  GUI_SetColor(GUI_WHITE);
////  GUI_SetBkColor(GUI_WHITE);
//  GUI_Clear();
//  GUI_SetColor(GUI_YELLOW);
//
//
//  int xPos = LCD_GetXSize() / 2;
//  int yPos = LCD_GetYSize() / 2;
//  GUI_SetTextMode(GUI_TM_TRANS);
//  GUI_SetFont(GUI_FONT_32_1);
//  GUI_DispStringHCenterAt("Vincent", xPos, yPos - 10);

  int delay = 2000;

//  J01_TextVersionString1();
//  HAL_Delay(delay);
//  J01_TextVersionString2();
//  HAL_Delay(delay);
//  J01_TextModes();
//  HAL_Delay(delay);
//  J01_TextInBox();
//  HAL_Delay(delay);
//  J01_TextRotated();
//  HAL_Delay(delay);
//  J01_PixelIndex();
//  HAL_Delay(delay);
//  J01_DrawAlpha1();
//  HAL_Delay(delay);
//  J01_DrawAlpha2();
//  HAL_Delay(delay);
//  J01_DrawAlpha3();
//  HAL_Delay(delay);

//  _DemoBarGraph();
//  HAL_Delay(2000);

  InitNew();
  Shapes();
  HAL_Delay(delay*10);

  loop();

//  GUI_RECT rClient;
//  rClient.x0 = 10;
//  rClient.y0 = 10;
//  rClient.x1 = 170;
//  rClient.y1 = 135;
//
//  //  GUI_AA_EnableHiRes();
//  //  GUI_AA_DisableHiRes();
//  GUI_AA_SetFactor(6);
//
////  GUI_GetClientRect(&rClient);
////  GUI_DispStringInRect("The quick brown fox jumps over the lazy dog", &rClient, GUI_TA_HCENTER | GUI_TA_VCENTER);
//
//  const char mystring[] = "The quick brown fox jumps over the lazy dog, is het niet g?";
//
//  int lines = GUI_WrapGetNumLines(mystring, rClient.x1 - rClient.x0, GUI_WRAPMODE_WORD);
//  dmc_puts("lines: ");
//  dmc_putintcr(lines);
//
//  int fsize = GUI_GetFontSizeY();
//  dmc_puts("fsize: ");
//  dmc_putintcr(fsize);
//
//  rClient.y1 = rClient.x0 + lines * fsize;
//
//  GUI_AA_DrawRoundedRect(rClient.x0 - 10, rClient.y0 - 10, rClient.x1 + 10, rClient.y1 + 10, 10*aa);
//
//  GUI_DispStringInRectWrap(mystring, &rClient, GUI_TA_VCENTER, GUI_WRAPMODE_WORD);

//#define PIXEL_SIZE 4
////static const char sText [] = "www.embitek.co.jp/product/iot-solutions.html";
//static const char sText [] = "http://www.blogtextbook.com/";
//
//GUI_HMEM hQR;
//hQR = GUI_QR_Create (sText, PIXEL_SIZE, GUI_QR_ECLEVEL_H, 0 );
//GUI_QR_Draw (hQR, 50, 50);
//GUI_QR_Delete (hQR);

  // Erase the screen
  GUI_SetBkColor(GUI_BLACK);
  GUI_Clear();

  GUI_SetPenSize(11);

  uint32_t x1 = 0;
  uint32_t x2 = 0;
  uint32_t y1 = 0;
  uint32_t y2 = 0;
  uint8_t started = 0;
  uint8_t pressed = 0;
  uint8_t erasing = 0;

  while(1)
  {
//    loop();
    GUI_PID_STATE TS_State = PollTouchScreen();
      if (TS_State.Pressed)
      {
        x2 = TS_State.x;
        y2 = TS_State.y;
//        if ((x2 < 40) && (y2 < 40))
//        {
//          if (pressed == 0)
//          {
//            GUI_SetBkColor(GUI_BLACK);
//            GUI_Clear();
//            started = 0;
//            erasing = 1;
//          }
//        }
        if ((started) && (!erasing))
        {
          uint8_t r = rnd() % 255;
          uint8_t g = rnd() % 255;
          uint8_t b = rnd() % 255;
          uint32_t color = 0xff000000 | (r << 16) | (g << 8) | b;
          GUI_SetColor(color);
          GUI_AA_DrawLine(x1, y1, x2, y2);
        }
        x1 = x2;
        y1 = y2;
        started = 1;
        pressed = 1;
      }
      else
      {
        started = 0;
        pressed = 0;
        erasing = 0;
      }
    GUI_MULTIBUF_End();
    GUI_Delay(5);
  }
}

/*************************** End of file ****************************/
