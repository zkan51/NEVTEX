#include "info.h"
#include "string.h"
#include "Config.h"


static INFO * pCursor  = NULL;
static int INFO_Cnt  = 0;
static INFO InfoTable[INFO_NUM_MAX] = {0};

INFO * pInfoHeader  = NULL;
INFO * pInfoTail    = NULL;

static INFO * INFO_alloc()
{
	int i  = 0;
	
	if(INFO_Cnt<INFO_NUM_MAX)
	{
		for(i=0; i<INFO_NUM_MAX; i++)
		{
			if(InfoTable[i].time == 0)
			{
				INFO_Cnt++;
				return &InfoTable[i];
			}
		}
  }
	else
	{
		/// 
		INFO * pIterator  = pInfoHeader;
		INFO * pBC        = NULL;
		
		/// Clean header as new alloced memory.
		if(   pInfoHeader->state != INFO_STT_Choosen
			 && pInfoHeader->isLocked == 0)
		{
			pInfoHeader->pNext->pPrev  = NULL;
			pInfoHeader  = pInfoHeader->pNext;
			
			memset((void*)pIterator, 0, sizeof(INFO));
			return pIterator;
		}
		else
		{
			pBC  = pInfoHeader;
			pIterator  = pBC->pNext;
			
			while(pIterator)
			{
				if(   pIterator->state != INFO_STT_Choosen
					 && pIterator->isLocked == 0)
				{
					if(pIterator != pInfoTail)
					{
						pBC->pNext  = pIterator->pNext;
						pIterator->pNext->pPrev  = pBC;						
					}
          else 
					{
						pBC->pNext  = NULL;
						pInfoTail  = pBC;
					}
					
					memset((void*)pIterator, 0, sizeof(INFO));
					return pIterator;
				}
				else
				{
					pBC  = pIterator;
					pIterator  = pBC->pNext;
				}
			}
			return NULL;
		}
	}
	 
	return NULL;
}



Bool INFO_add(INFO * pInfo)
{
	   INFO * pBuf  = NULL;
     
     pBuf  = INFO_alloc();
		 
		 if(pBuf)
		 {
				pBuf->ID = pInfo->ID;
			 pBuf->pContent = pInfo->pContent;
			 pBuf->chnl  = pInfo->chnl;
			 pBuf->date  = pInfo->date;
			 pBuf->time  = pInfo->time;
			 pBuf->type  = pInfo->type;
			 pBuf->state = pInfo->state;
			 pBuf->isLocked  = pInfo->isLocked;			 
				pBuf->codeFormat[0]  = pInfo->codeFormat[0];
				pBuf->codeFormat[1]  = pInfo->codeFormat[1];
				pBuf->codeFormat[2]  = pInfo->codeFormat[2];
				pBuf->codeFormat[3]  = pInfo->codeFormat[3];		
			 
			 /// Add node for the first time.
       if(pInfoHeader == NULL)			 
			 {
				 pInfoHeader  = pBuf;
				 pInfoTail    = pBuf;
				 return TRUE;
			 }
			 
			 /// Add node at tail.
			 pInfoTail->pNext  = pBuf;
			 pBuf->pPrev  = pInfoTail;
			 
			 pInfoTail  = pBuf;
			 return TRUE;
		 }
		 else
		 {
INFO("alloc info failed!");			 
			 return FALSE;
		 }
}


INFO * INFO_LIST_Reset()
{
	if(pInfoTail)
	{
		pCursor  = pInfoTail;
		return pCursor;
	}
	else
	{
		return NULL;
	}
}


INFO * INFO_LIST_hasPrev()
{
	if(pCursor == NULL)
	{
		return FALSE;
	}
	
	pCursor  = pCursor->pPrev;
	return pCursor;
	
// 	if(pCursor != pInfoHeader)
// 	{
// 		*pInfo  = pCursor;
// 		pCursor  = pCursor->pPrev;
// printf("--->%p\n\r",pCursor);		
// 		return TRUE;
// 	}
// 	else
// 	{
// 		*pInfo  = pCursor;
// 		return FALSE;
// 	}
}

void lock(int SelRow)
{
	int cnt = 0;
	INFO * pTemp = pInfoTail;
	while (pTemp)
	{
		if (cnt == SelRow)
		{		
			if(pTemp->isLocked == 0)
				pTemp->isLocked = 1;
			else pTemp->isLocked = 0;
		}
		cnt++;
		
		pTemp = pTemp->pPrev;
	}
}
// 	int index = 0;
// 	for (pCursor = pInfoTail; pCursor->pPrev != NULL ;pCursor =  pCursor->pPrev)
// 	{
// 		index++;
// 			
// 				pCursor->isLocked = 1;
// 	}



void INFO_Dump()
{
	INFO * pIterator  = pInfoHeader;
	
	while(pIterator)
	{
		printf("%p  \n\r",pIterator);
		printf("Date:%ld Time:%ld  \n\r", pIterator->date, pIterator->time);
		
		pIterator  = pIterator->pNext;
	}
}
//
//testdata
//
char strt[8][1000] = 
{
	"ZCZC EA31\n\
WZ 1268\n\
SELF CANCELLING. CANCEL WZ 1115 (EA96). ANM 5389/15 REFERS.\n\
NNNN\n",
	
"ZCZC LA56\n\
041718 UTC NOV 15\n\
NORWEGIAN NAV. WARNING 691/2015\n\
CHART 26\n\
AREA FLOROE\n\
LANGHOLMEN LOWER LEADING LIGHT 61-36.3N 005-02.4E IS UNLIT.\n\
NNNN\n",
	
"ZCZC LA46\n\
010045 UTC JAN 15\n\
LIMNOS RADIO NAVWARN 2/15\n\
CENTRAL AIGAIO SEA\n\
1)FIRING EXERCISES\n\
'NISOS ANDROS FIRING AREA\n\
01 JAN TO 31 DEC 15\n\
DAILY FROM SUNRISE TO SUNSET\n\
IN AREA BOUNDED BY:\n\
38-02N 024*TWE\n\
38-16N 025-21E\n\
37-48N 025-49E\n\
37-34N 025-23E\n\
37-42N 025-01E\n\
38-00N 024-52E\n\
2)CANCEL THIS MSG 311615 UTC DEC 15\n\
NNNN\n",

"ZCZC ME75\n\
102300 UTC NOV 15\n\
NORWEGIAN WEATHER BULLETIN\n\
GALE OR STORM IS NOT EXPECTED IN AREAS COVERED BY THIS BULLETIN.\n\
SYNOPTIC SITUATION TUESDAY 10 NOVEMBER AT 18 UTC\n\
LOW 973 HPA 71 N 01 E MOV N 10 KT.\n\
LOW 974 HPA 60 N 28 W MOV NE 10 KT AND FLN SOME.\n\
HIGH 1029 HPA 46 N 01 E ALMOST STATIONARY.\n\
FORECAST VALID THE NEXT 24 HOURS:\n\
SKAGERRAK\n\
SW 5 AND OCNL 6. MAINLY DRY WED EVENING SLIGHT RAIN FM S. MOD IN PRECIPITATION.\n\
GERMAN BIGHT AND \n\
SW 6 AT TIMES 7 WED FORENOON TEMPO 5 IN N PART. MAINLY DRY FM WED FORENOON\n\
RAIN IN N PART. MOD IN PRECIPITATION.\n\
FISHER AND FORTIES\n\
W 6. BECMG MAINLY DRY AND GOOD. WED MORNING DECR SW 5 IN THE EVENING SW\n\
7. RAIN FM S WITH MOD.\n\
NNNN\n",

"ZCZC DA50\n\
271242 UTC OCT 15\n\
NORWEGIAN NAV. WARNING 669/2015\n\
CHART 4\n\
AREA NORDRE OSLOFJORD\n\
HOEVIKODDEN LOWER LIGHT 59-53.3N 010-33.1E IS UNLIT.\n\
NNNN\n",

"ZCZC DA29\n\
NAVAREA I 317\n\
**COTLA*N*  NORTH COAST.\n\
*APE*WRA*H NORTHWACDS AND NORTN-EA**STWARDS.\n\
NUN BANK AND*SKERRY B*OK.\n\
.*C*ARTS*BL 2720 (INT1602) AND 1954 (IN* 16*WLM *\n\
NEW VIRTUAL AIS AIDS TO NAVIGATIO* ESTABLIAHED AS*FOLLOWS:\n\
*\n\
(*A) NUN ROCK 58-52.65N 004-58.30W ISOLALED DANGER MARK MMSI 992356016.\n\
(B) SULE STACK 59-01.45N 004-30.40W ISOLATED DANGER MARK MMSI 992356017.\n\
NNNN\n",

"ZCZC DA96\n\
11 NOV 2015 02.31 UTC\n\
RCC-HAIFA\n\
NAVAREA III 000329\n\
N.T.M 53/2015 10.11. 2015\n\
SUBJECT:\n\
PORT OF HADERA PYROTECHNIC PRACTICING.\n\
THIS IS TO ADVISE ALL MARINERS THAT ON\n\
11TH NOVEMBER 2015 BETWEEN 0700\n\
AND 1000 UTC THE PORT WILL PRACTICE\n\
PYROTECHNIC DEVISES USING HAND FLARES\n\
SMOKE BUOYS AND PARACHUTE ROCKETS.\n\
ISR AUTH\n\
NNNN\n",

"ZCZC QE57\n\
101840 UTC NOV\n\
SPLITRADIO/9AS SHIPPING FORECAST FOR ADRIATIC AT 1800 UTC\n\
WNG: FOG IN PLACES MOSTLY ON N-ERN ADRIATIC.\n\
SYNOPSIS: FIELD OF HIGH STATIONARY OVER ADRIATIC.\n\
OUTLOK 24 HRS: N-ERN/CENTRAL/S-ERN ADRIATIC: CALM OR NW  4-10 ON S-ERN/PARTLY\n\
S-ERN ADRIATIC UP TO 15 KTS. SEA 1-2 ON S-ERN/PARTLY CENTRAL ADRIATIC 3.\n\
VSBY 10-20 KMS OVERNIGHT AND TOMORROW MORNING LOCALLY LESS THEN 1 KM BY\n\
FOG MOSTLY ON N-ERN ADRIATIC. LIGHT-MOD CLOUDY.\n\
NNNN\n"
};