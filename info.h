#ifndef _INFO_H
#define _INFO_H

#define INFO_NUM_MAX 20
#include "lpc_types.h"


typedef enum _INFO_CHANNEL INFO_CHNL;
enum _INFO_CHANNEL{INT = 1,LOC1, LOC2, CHS};

typedef enum _INFO_TYPE INFO_TYPE;
enum _INFO_TYPE{INFO_Type_None = 0, INFO_Type_VIP, INFO_Type_Rscue};

typedef enum _INFO_STATE INFO_STT;
enum _INFO_STATE{INFO_STT_None = 0, INFO_STT_Choosen, INFO_STT_CSTOFF ,INFO_STT_New};

typedef struct _INFO INFO;
struct _INFO
{
	int			 ID;
	char       codeFormat[5];
	long       date;
	long       time;
	INFO_CHNL  chnl;
	INFO_TYPE  type;
	INFO_STT   state;
	char       isLocked;
	char *     pContent;
	
	INFO *     pPrev;
	INFO *     pNext;
};

extern INFO * pInfoHeader;
extern INFO * pInfoTail;
extern char strt[8][1000];
Bool INFO_add(INFO * pInfo);
INFO * INFO_LIST_Reset(void);
INFO * INFO_LIST_hasPrev(void);
void INFO_Dump(void);
void lock(int);


#endif