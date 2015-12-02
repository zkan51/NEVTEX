#ifndef MAINTASK_H
#define MAINTASK_H

#include "WM.h"
#define USER_MSG           (WM_USER + 0x00)
#define USER_MSG_CHOOSE    (WM_USER + 0x01)
#define USER_MSG_REPLY     (WM_USER + 0x02)
#define USER_MSG_SKIN      (WM_USER + 0x03)
#define USER_MSG_SHAPE     (WM_USER + 0x04)
#define USER_MSG_UNIT      (WM_USER + 0x05)
#define USER_MSG_BRING     (WM_USER + 0x06)
#define USER_MSG_DFULT_CNT (WM_USER + 0x07)

#define USER_MSG_SOFTUPDATE (WM_USER + 0x08) //软件更新
#define USER_MSG_PRINTEND   (WM_USER + 0x09) //打印
#define USER_MSG_LANGUAGE   (WM_USER + 0x0a) //语言选择

#define STORE_SETTING   1
#define CANCEL_MONITED  2
#define REPLY_OK        3
#define REPLY_CANCEL    4
#define ADD_MONITED     5
#define SYS_SETTING     6
#define SOFT_UPDATE_0   7
#define SOFT_UPDATE_1   8
#define SOFT_UPDATE_2   9

#define GUI_KEY_INT					 4
#define GUI_KEY_LOC1				 5
#define GUI_KEY_CHS						6
#define GUI_KEY_LOC2					7
#define GUI_KEY_PRINT				11
#define GUI_KEY_LOCK					12
#define GUI_KEY_DIM1					14
#define GUI_KEY_DIM2					15
#define GUI_KEY_ALOFF				20
#define GUI_KEY_MENU					21

// #define GUI_KEY_RELEASE           4
// #define GUI_KEY_MENU              5
// #define GUI_KEY_LARGE             6
// #define GUI_KEY_REDUCE            7
// #define GUI_KEY_MONITORING        11
// #define GUI_KEY_CANCEL            12
// #define GUI_KEY_CENTER            14

// #define GUI_KEY_MNT_ENABLE        15
// #define GUI_KEY_MNT_DISABLE       20

// #define GUI_KEY_PWM_INC           21
// #define GUI_KEY_PWM_DEC           22

// #define GUI_KEY_TRACE_ENABLE      28
// #define GUI_KEY_TRACE_DISABLE     31

#endif
