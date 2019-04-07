/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.32                          *
*        Compiled Oct  8 2015, 11:59:02                              *
*        (c) 2015 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include "DIALOG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0     (GUI_ID_USER + 0x00)
#define ID_BUTTON_0       (GUI_ID_USER + 0x01)
#define ID_BUTTON_1       (GUI_ID_USER + 0x02)
#define ID_TEXT_0         (GUI_ID_USER + 0x03)
#define ID_TEXT_1         (GUI_ID_USER + 0x04)
#define ID_TEXT_2         (GUI_ID_USER + 0x05)
#define ID_TEXT_3         (GUI_ID_USER + 0x06)
#define ID_PROGBAR_0      (GUI_ID_USER + 0x07)
#define ID_PROGBAR_1      (GUI_ID_USER + 0x08)
#define ID_PROGBAR_2      (GUI_ID_USER + 0x09)
#define ID_PROGBAR_3      (GUI_ID_USER + 0x0A)
#define ID_RADIO_0        (GUI_ID_USER + 0x0B)


// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 10, 10, 240, 180, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Down", ID_BUTTON_0, 2, 135, 80, 20, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Up", ID_BUTTON_1, 147, 135, 80, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Speed", ID_TEXT_0, 8, 12, 39, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Tac", ID_TEXT_1, 8, 42, 44, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Water", ID_TEXT_2, 8, 72, 43, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Oil", ID_TEXT_3, 8, 102, 34, 20, 0, 0x0, 0 },
  { PROGBAR_CreateIndirect, "Progbar", ID_PROGBAR_0, 50, 10, 120, 20, 0, 0x0, 0 },
  { PROGBAR_CreateIndirect, "Progbar", ID_PROGBAR_1, 50, 40, 120, 20, 0, 0x0, 0 },
  { PROGBAR_CreateIndirect, "Progbar", ID_PROGBAR_2, 50, 70, 120, 20, 0, 0x0, 0 },
  { PROGBAR_CreateIndirect, "Progbar", ID_PROGBAR_3, 50, 100, 120, 20, 0, 0x0, 0 },
  { RADIO_CreateIndirect, "Radio", ID_RADIO_0, 181, 12, 32, 108, 0, 0x1e04, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
//extern GUI_CONST_STORAGE GUI_FONT GUI_Fontsong16;
void InitDialog(WM_MESSAGE *pMsg)
{
	WM_HWIN hWin = pMsg->hWin;

//	BUTTON_SetFont(WM_GetDialogItem(hWin, ID_BUTTON_0), &GUI_Font13_1);
//	BUTTON_SetFont(WM_GetDialogItem(hWin, ID_BUTTON_1), &GUI_Font13_1);
}
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  int NCode;
  int Id;
  WM_HWIN hItem;

  // USER START (Optionally insert additional variables)
  static int prog0 = 20;
  static int prog1 = 40;
  static int prog2 = 60;
  static int prog3 = 80;
  // USER END
  hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_0);
  PROGBAR_SetValue(hItem, prog0);
  hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_1);
  PROGBAR_SetValue(hItem, prog1);
  hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_2);
  PROGBAR_SetValue(hItem, prog2);
  hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_3);
  PROGBAR_SetValue(hItem, prog3);

  switch (pMsg->MsgId)
  {
  case WM_INIT_DIALOG:
    InitDialog(pMsg);
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id)
    {
    case ID_BUTTON_0: // Notifications sent by 'Back'
      switch(NCode)
      {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
      {
        hItem = WM_GetDialogItem(pMsg->hWin, ID_RADIO_0);
        int rval = RADIO_GetValue(hItem);
        switch(rval)
        {
        case 0:
          if(prog0 > 0)
          {
            prog0--;
          }
          hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_0);
          PROGBAR_SetValue(hItem, prog0);
          break;
        case 1:
          if(prog1 > 0)
          {
            prog1--;
          }
          hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_1);
          PROGBAR_SetValue(hItem, prog1);
          break;
        case 2:
          if(prog2 > 0)
          {
            prog2--;
          }
          hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_2);
          PROGBAR_SetValue(hItem, prog2);
          break;
        case 3:
          if(prog3 > 0)
          {
            prog3--;
          }
          hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_3);
          PROGBAR_SetValue(hItem, prog3);
          break;
        }
      }
      // USER END
      break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
        // USER START (Optionally insert additional code for further notification handling)
        // USER END
      }
      break;
      case ID_BUTTON_1: // Notifications sent by 'OK'
        switch(NCode)
        {
        case WM_NOTIFICATION_CLICKED:
          // USER START (Optionally insert code for reacting on notification message)
        {
          hItem = WM_GetDialogItem(pMsg->hWin, ID_RADIO_0);
          int rval = RADIO_GetValue(hItem);
          switch(rval)
          {
          case 0:
            if(prog0 < 100)
            {
              prog0++;
            }
            hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_0);
            PROGBAR_SetValue(hItem, prog0);
            break;
          case 1:
            if(prog1 < 100)
            {
              prog1++;
            }
            hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_1);
            PROGBAR_SetValue(hItem, prog1);
            break;
          case 2:
            if(prog2 < 100)
            {
              prog2++;
            }
            hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_2);
            PROGBAR_SetValue(hItem, prog2);
            break;
          case 3:
            if(prog3 < 100)
            {
              prog3++;
            }
            hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_3);
            PROGBAR_SetValue(hItem, prog3);
            break;
          }
        }
        // USER END
        break;
        case WM_NOTIFICATION_RELEASED:
          // USER START (Optionally insert code for reacting on notification message)
          // USER END
          break;
          // USER START (Optionally insert additional code for further notification handling)
          // USER END
        }
        break;
        case ID_RADIO_0: // Notifications sent by 'Radio'
          switch(NCode)
          {
          case WM_NOTIFICATION_CLICKED:
            // USER START (Optionally insert code for reacting on notification message)
            // USER END
            break;
          case WM_NOTIFICATION_RELEASED:
            // USER START (Optionally insert code for reacting on notification message)
            // USER END
            break;
          case WM_NOTIFICATION_VALUE_CHANGED:
            // USER START (Optionally insert code for reacting on notification message)
            // USER END
            break;
            // USER START (Optionally insert additional code for further notification handling)
            // USER END
          }
          break;
          // USER START (Optionally insert additional code for further Ids)
          // USER END
    }
    break;
    // USER START (Optionally insert additional message handling)
    // USER END
    default:
      WM_DefaultProc(pMsg);
      break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateFramewin
*/
//WM_HWIN CreateFramewin(void);
WM_HWIN CreateFramewin(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/