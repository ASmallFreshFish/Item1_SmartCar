#ifndef __REMOTECONTROL_H
#define __REMOTECONTROL_H	 

#include "head_include.h"
/**************************************************************
MOTOR:

***************************************************************/
#define REMOECONTROL_5V 	
#define REMOECONTROL_GND 
#define REMOECONTROL_D0 PFin(11)	//B
#define REMOECONTROL_D1 PFin(12)	//D
#define REMOECONTROL_D2 PFin(13)	//A	
#define REMOECONTROL_D3 PFin(14)	//C


#define REMOECONTROL_FRONT REMOECONTROL_D2 	
#define REMOECONTROL_LEFT REMOECONTROL_D3 	
#define REMOECONTROL_RIGHT REMOECONTROL_D0
#define REMOECONTROL_STOP REMOECONTROL_D1 

void REMOTECONTROL_init(void);//≥ı ºªØ
void remoteC_handle(void);
smartCar_status_t remoteC_get_status();

		 				    
#endif

