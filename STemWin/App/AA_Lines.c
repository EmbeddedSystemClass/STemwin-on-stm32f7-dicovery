/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2015  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************
** emWin V5.32 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only  be used  in accordance  with  a license  and should  not be  re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : AA_Lines.c
Purpose     : Shows lines with different antialiasing qualities
Requirements: WindowManager - ( )
              MemoryDevices - ( )
              AntiAliasing  - (x)
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/

#include "GUI.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 5)

/*******************************************************************
*
*       Static code
*
********************************************************************
*/
/*******************************************************************
*
*       _DemoAntialiasing
*
* Function description
*   Draws lines with different antialiasing factors
*   https://www.segger.com/products/user-interface/emwin/add-ons/antialiasing/
*   The quality of antialiasing can be set with a factor between 1 and 6,
*   where 1 means no antialiasing and 6 the highest quality. For most applications
*   factor 4 is sufficient and is a good compromise between quality and performance.
*
*/
void _DemoAntialiasing(void) {
  const GUI_FONT * font_old;
  int              i;
  int              x1;
  int              x2;
  int              y1;
  int              y2;

  //
  // Set drawing attributes 
  //
  GUI_SetColor(GUI_WHITE);
  GUI_SetBkColor(GUI_BLACK);
  GUI_SetPenShape(GUI_PS_FLAT);
//  GUI_SetPenShape(GUI_PS_ROUND);
//  GUI_SetPenShape(GUI_PS_SQUARE);
  GUI_Clear();
  //
  // Draw headline
  //
  font_old = GUI_SetFont(&GUI_Font24_ASCII);
  GUI_SetTextAlign(GUI_TA_HCENTER);
  GUI_DispStringAt("AA_Lines - Sample", 160, 5);
  //
  // Draw lines without antialiased
  //
  GUI_SetFont(&GUI_Font8x16);
  GUI_SetTextAlign(GUI_TA_LEFT);

  GUI_DispStringAtCEOL("Draw normal lines using", 5, 40);
  GUI_DispStringAtCEOL("GUI_DrawLine", 5, 55);
  //
  // Draw lines with antialiasing quality factor 2
  //
//  GUI_DispStringAtCEOL("", 5, 40);
//  GUI_DispStringAtCEOL("", 5, 55);
  GUI_DispStringAtCEOL("Draw antialiased lines using", 5, 70);
  GUI_DispStringAtCEOL("GUI_AA_DrawLine", 5, 85);

  y1 = 95;
  y2 = 5;

  //
  // Draw lines with antialiasing quality factor 1
  //
  x1 = 20;
  x2 = 100;
  GUI_SetFont(font_old);
  GUI_DispStringHCenterAt("Normal", (x1 + x2) / 2, 30 + y1);
  for (i = 1; i < 8; i++) {
    GUI_SetPenSize(i);
    GUI_DrawLine(x1, 40 + i * 15 + y1, x2, 40 + i * 15 + y1 + y2);
  }

  //
  // Draw lines with antialiasing quality factor 3
  //
  x1 = 120;
  x2 = 200;
  GUI_AA_SetFactor(2);
  GUI_SetFont(font_old);
  GUI_DispStringHCenterAt("Antialiased\nusing factor 2", (x1 + x2) / 2, 30 + y1);
  for (i = 1; i < 8; i++) {
    GUI_SetPenSize(i);
    GUI_AA_DrawLine(x1, 40 + i * 15 + y1, x2, 40 + i * 15 + y1 + y2);
  }
  //
  // Draw lines with antialiasing quality factor 6
  //
  x1 = 220;
  x2 = 300;
  GUI_AA_SetFactor(4);
  GUI_SetFont(font_old);
  GUI_DispStringHCenterAt("Antialiased\nusing factor 4", (x1 + x2) / 2, 30 + y1);
  for (i = 1; i < 8; i++) {
    GUI_SetPenSize(i);
    GUI_AA_DrawLine(x1, 40 + i * 15 + y1, x2, 40 + i * 15 + y1 + y2);
  }
  //
  // Draw lines with antialiasing quality factor 6
  //
  x1 = 320;
  x2 = 400;
  GUI_AA_SetFactor(6);
  GUI_SetFont(font_old);
  GUI_DispStringHCenterAt("Antialiased\nusing factor 6", (x1 + x2) / 2, 30 + y1);
  for (i = 1; i < 8; i++) {
    GUI_SetPenSize(i);
    GUI_AA_DrawLine(x1, 40 + i * 15 + y1, x2, 40 + i * 15 + y1 + y2);
  }
  GUI_Delay(7500);
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       MainTask
*/
//void MainTask(void) {
//  GUI_Init();
//  //
//  // Check if recommended memory for the sample is available
//  //
//  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
//    GUI_ErrorOut("Not enough memory available.");
//    return;
//  }
//  while (1) {
//    _DemoAntialiasing();
//  }
//}

/*************************** End of file ****************************/
