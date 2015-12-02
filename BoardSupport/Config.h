#ifndef _CONFIG_H
#define _CONFIG_H

#define MOTHERShIP_LA    1927265
#define MOTHERShIP_LG    7128663

/********************************************************************
*
*               MENU  ID
*/

#define ID_MENU     					(GUI_ID_USER + 0x50)
#define ID_PrintMenu     (GUI_ID_USER + 0x51)
#define ID_TEXT_0    (GUI_ID_USER + 0x52)
#define ID_TEXT_1    (GUI_ID_USER + 0x53)
//一级
#define ID_SITESEL 					 (GUI_ID_USER + 0x01)//站点选择
#define ID_INFOSEL	 					(GUI_ID_USER + 0x02)//信息选择
#define ID_PORTSET 					 (GUI_ID_USER + 0x03)//端口设置
#define ID_SYSSET   					(GUI_ID_USER + 0x04)//系统设置

//二级
#define ID_FOURCAN  					(GUI_ID_USER + 0x05)//四频道同步
#define ID_INTERCEL 					(GUI_ID_USER + 0x06)//国际频道
#define ID_LOCAL1   					(GUI_ID_USER + 0x07) //本地频道1
#define ID_LOCAL2   					(GUI_ID_USER + 0x08)//本地频道2
#define ID_CHS      					(GUI_ID_USER + 0x09)//中文频道

#define ID_PORT_SITESEL	 (GUI_ID_USER + 0x0a)//端口设置-站点选择
#define ID_PORT_INFOSEL	 (GUI_ID_USER + 0x0b)//端口设置-信息选择

//系统设置
#define ID_SYSSET_DISP	      (GUI_ID_USER + 0x10)//显示设置
#define ID_SYSSET_ALAR	      (GUI_ID_USER + 0x11)//报警音设置
#define ID_SYSSET_KEYSOUND	  (GUI_ID_USER + 0x12)//按键音设置
#define ID_SYSSET_TIME					  (GUI_ID_USER + 0x13)//时间设定
#define ID_SYSSET_LANGUAGE	  (GUI_ID_USER + 0x14)//语言设置
#define ID_SYSSET_ANTEN				  (GUI_ID_USER + 0x15)//天线设置
#define ID_SYSSET_SOFTUPDATE	(GUI_ID_USER + 0x16)//软件更新
#define ID_SYSSET_RESET  				(GUI_ID_USER + 0x17)//恢复出厂
#define ID_SYSSET_CHECK 					(GUI_ID_USER + 0x18)//开启自检

//三级
#define ID_FOUR_RECEIVE_0 (GUI_ID_USER + 0x21)
#define ID_FOUR_RECEIVE_1 (GUI_ID_USER + 0x22)
#define ID_FOUR_RECEIVE_2 (GUI_ID_USER + 0x23)
#define ID_FOUR_RECEIVE_3 (GUI_ID_USER + 0x24)
#define ID_FOUR_RECEIVE_4 (GUI_ID_USER + 0x25)

#define ID_INT_RECEIVE_0 (GUI_ID_USER + 0x26)
#define ID_INT_RECEIVE_1 (GUI_ID_USER + 0x27)
#define ID_INT_RECEIVE_2 (GUI_ID_USER + 0x28)
#define ID_INT_RECEIVE_3 (GUI_ID_USER + 0x29)
#define ID_INT_RECEIVE_4 (GUI_ID_USER + 0x2a)

#define ID_LOC1_RECEIVE_0 (GUI_ID_USER + 0x2b)
#define ID_LOC1_RECEIVE_1 (GUI_ID_USER + 0x2c)
#define ID_LOC1_RECEIVE_2 (GUI_ID_USER + 0x2d)
#define ID_LOC1_RECEIVE_3 (GUI_ID_USER + 0x2e)
#define ID_LOC1_RECEIVE_4 (GUI_ID_USER + 0x2f)

#define ID_LOC2_RECEIVE_0 (GUI_ID_USER + 0x30)
#define ID_LOC2_RECEIVE_1 (GUI_ID_USER + 0x31)
#define ID_LOC2_RECEIVE_2 (GUI_ID_USER + 0x32)
#define ID_LOC2_RECEIVE_3 (GUI_ID_USER + 0x33)
#define ID_LOC2_RECEIVE_4 (GUI_ID_USER + 0x34)

#define ID_CHS_RECEIVE_0 (GUI_ID_USER + 0x35)
#define ID_CHS_RECEIVE_1 (GUI_ID_USER + 0x36)
#define ID_CHS_RECEIVE_2 (GUI_ID_USER + 0x37)
#define ID_CHS_RECEIVE_3 (GUI_ID_USER + 0x38)
#define ID_CHS_RECEIVE_4 (GUI_ID_USER + 0x39)

#define ID_SITE_OUTPUT_0  (GUI_ID_USER + 0x70)//输出
#define ID_SITE_OUTPUT_1  (GUI_ID_USER + 0x71)//输出
#define ID_SITE_OUTPUT_2  (GUI_ID_USER + 0x72)//输出
#define ID_SITE_OUTPUT_3  (GUI_ID_USER + 0x73)//输出
#define ID_SITE_OUTPUT_4  (GUI_ID_USER + 0x74)//输出

#define ID_INFO_OUTPUT_0  (GUI_ID_USER + 0x75)//输出
#define ID_INFO_OUTPUT_1  (GUI_ID_USER + 0x76)//输出
#define ID_INFO_OUTPUT_2  (GUI_ID_USER + 0x77)//输出
#define ID_INFO_OUTPUT_3  (GUI_ID_USER + 0x78)//输出
#define ID_INFO_OUTPUT_4  (GUI_ID_USER + 0x79)//输出

#define ID_INVERSE        (GUI_ID_USER + 0x3a)//反色
#define ID_SLEEPSET       (GUI_ID_USER + 0x3b)//睡眠设置
#define ID_SLEEPSET_0     (GUI_ID_USER + 0x3d)//睡眠设置

#define ID_ALAR_INFOTYPE_0  (GUI_ID_USER + 0x46)//报警音-信息类型
#define ID_ALAR_INFOTYPE_1  (GUI_ID_USER + 0x47)//报警音-信息类型
#define ID_ALAR_INFOTYPE_2  (GUI_ID_USER + 0x48)//报警音-信息类型
#define ID_ALAR_INFOTYPE_3  (GUI_ID_USER + 0x49)//报警音-信息类型

#define ID_KEYSOUND       (GUI_ID_USER + 0x3f)//按键音
#define ID_TIME           (GUI_ID_USER + 0x40)//时间
#define ID_LANGUAGE       (GUI_ID_USER + 0x41)//语言
#define ID_ANTEN          (GUI_ID_USER + 0x42)//天线
#define ID_SOFT           (GUI_ID_USER + 0x43)//软件更新
#define ID_RESET          (GUI_ID_USER + 0x44)//恢复出厂
#define ID_CHECK          (GUI_ID_USER + 0x45)//自检

/********************************************************************
 *
 *               boat drawing config
 */
#define DSP_BOAT_COLOR   GUI_BLACK

#define BGL_BOAT_COLOR   GUI_RED
#define BGL_CIRCLE_R     15

#define DRG_BOAT_COLOR   GUI_GREEN
#define DRG_CIRCLE_R     20
#define DRG_PENSIZE      4

#define MM_BOAT_COLOR    GUI_BLUE
#define MM_BOAT_PENSIZE   2





/********************************************************************
 *
 *               timer counter config
 */
#define TIMESTAMP           60

#define MAP_REFRESH_SLOT    500
#define AUTO_ADAPTER_CNT    20  



/********************************************************************
 *
 *              array size config
 */
#define MSG_QUEUE_TABNUM    20
#define BOAT_NUM_MAX        500
#define MNT_NUM_MAX         20
#define INVD_NUM_MAX        10


/********************************************************************
 *
 *              EEPROM address config
 */
#define SYSCONF_ADDR     0                        

#define MNT_PAGE_ID_HEADER  (uint8_t)1
#define MNT_PAGE_ID         (uint8_t)2       


/********************************************************************
 *
 *              code switch config
 */
#define CODE_CHECK 

/********************************************************************
 *
 *               printf config.
 */
#define __INFO_ENABLE 

#ifndef __INFO_ENABLE

#define INFO(format,...) 

#else

#define INFO(format,...)  printf("FILE:%s,LINE:%d,"format"\r\n",__FILE__,__LINE__,##__VA_ARGS__)

#endif


/********************************************************************
 *
 *               cursor config.
 */
#define CURSOR_SPEED   5


#endif
