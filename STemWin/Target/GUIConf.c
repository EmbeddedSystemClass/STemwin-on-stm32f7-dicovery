  /**
  ******************************************************************************
  * @file    GUIConf.c
  * @author  MCD Application Team
  * @brief   Display controller initialization 
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

#include "GUI.h"

//#define WIDGET_USE_FLEX_SKIN	1

/*********************************************************************
*
*       Defines, configurable
*
**********************************************************************
*/

//
// Define the available number of bytes available for the GUI
//
// Jack
// https://forum.segger.com/index.php/Thread/4675-Alpha-blending-not-work/
// https://forum.segger.com/index.php/Thread/3399-stemwin-without-sdram/
#define GUI_NUMBYTES  (1024) * 220   // x KByte

//#define GUI_BLOCKSIZE 0x80
//#define GUI_BUFFER_IN_EXT_RAM 0
//#define GUI_BUFFER_ADDRESS  0xC0000000 // 0xD0600000, 0xC0200000 , 0xC0000000, 0x20001000
//#define OS_SUPPORT 0

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
/* 32 bit aligned memory area */
static U32 extMem[GUI_NUMBYTES / 4];
//#if (GUI_BUFFER_IN_EXT_RAM)
////  static U32 aMemory[GUI_NUMBYTES / 4]__attribute__((at(GUI_BUFFER_ADDRESS)));
//  static U32 aMemory[GUI_NUMBYTES / 4] __attribute__((at(GUI_BUFFER_ADDRESS)));
////  static U32 extMem[GUI_NUMBYTES / 4] __attribute__((section('.ExtRAMData')));
//#else
////  static U32 aMemory[GUI_NUMBYTES / 4];
//  static U32 aMemory[GUI_NUMBYTES / 4];
//#endif

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_X_Config
*
* Purpose:
*   Called during the initialization process in order to set up the
*   available memory for the GUI.
*/
void GUI_X_Config(void)
{
  //	 Jack
  // 32 bit aligned memory area  //
  // Assign memory to emWin  //
  GUI_ALLOC_AssignMemory(extMem, GUI_NUMBYTES);
//  GUI_ALLOC_AssignMemory(aMemory, GUI_NUMBYTES);
//  GUI_ALLOC_SetAvBlockSize(GUI_BLOCKSIZE);

  // Set default font
//  GUI_SetDefaultFont(GUI_FONT_6X8);
}

/*************************** End of file ****************************/
