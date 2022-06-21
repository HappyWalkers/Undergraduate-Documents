#include "2440addr.h"
#include "def.h"

int Test_IrDa() 
{ 

  unsigned int m,n,j=0; 
  
  rGPBCON&= ~((0x11<<18)|0x11); //GPB9:IRDA  GPB1:BELL
  rGPBCON|=0x01; 
 
  Uart_Printf("\n====irda test====\n");
  Uart_Printf("press ESC to exit\n"); 
    while(1)
    {  
       m=n=rGPBDAT;
       if (!(m&=0x200))    //检测PD2是否为低电平
       {  
             j++;
             if(j==3)//累计接收10次蜂鸣器动作
		     {
               
             	if(n&0x01) rGPBDAT&=~0x1;
             	else rGPBDAT|=0x01;
             	j=0; 
                 
             }  
             
                    
        }
        Delay(10);
       if ( Uart_GetKey() == ESC_KEY ) break;	
	}
  
 
  return(0); 
}

