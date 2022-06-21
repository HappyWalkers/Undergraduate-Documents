#include "def.h"
#define GPGCON (*(volatile unsigned *)0x56000060)     //18b20寄存器设置
#define GPGDAT (*(volatile unsigned *)0x56000064) 
#define GPGUP (*(volatile unsigned *)0x56000068) 
 
#define UFCON0     (*(volatile unsigned *)0x50000008)   //串口寄存器设置
#define UMCON0     (*(volatile unsigned *)0x5000000c)
#define ULCON0     (*(volatile unsigned *)0x50000000)	
#define UCON0      (*(volatile unsigned *)0x50000004)
#define UBRDIV0    (*(volatile unsigned *)0x50000028)
#define UTRSTAT0   (*(volatile unsigned *)0x50000010)
#define UTXH0 		(*(volatile unsigned*)0x50000020)
#define URXH0 		(*(volatile unsigned*)0x50000024)
   

unsigned char wd[4];  
 unsigned int sdata;//测量到的温度的整数部分
float xiaoshu1;//小数第一位
unsigned char xiaoshu2;//小数第二位
 unsigned int xiaoshu;//两位小数

void zh(unsigned char wdata);
void Delay(unsigned int x) ;
void uart(void);
void DS18B20PRO(void);
void dmsec (unsigned int t);
void tmreset (void);
unsigned char tmrbit (void);
unsigned char tmrbyte (void) ;
void tmwbyte (unsigned char dat);
void tmstart (void) ;
void tmrtemp (void) ;

int Temperature(void)                       //不停循环检测温度值，并转换为asc||码，通过串口传出来
{  
	int n=1;
  //  GPGUP&= 0xfffffffe; 
	Uart_Printf("\nTest temperature sensor!\n");
	Uart_Printf("Press 'ESC' key to exit!\n");     
    while(1)
    {  
          DS18B20PRO();         
      //    zh(sdata);
          if(n){
          	n=0;
          	continue;
          }
          
          Uart_Printf(" %d.%.2d\n",sdata,xiaoshu);
          //uart();
		  Delay(800);
          if ( Uart_GetKey() == ESC_KEY ) break;                    
	}
   
  return(0); 
} 

void dmsec (unsigned int t)       //精确延时函数  
 {   
	unsigned int i;
    unsigned int j;
    j=1*t;
    for(i = 0; i < j; i++);
 } 
         
void tmreset (void)       //18b20初始化
{   unsigned int i;                            
    
	GPGCON&=0xfffffffc;    //设置寄存器对18b20进行写操作
	GPGCON|=0x01;
	
	GPGDAT|=0x01;
    dmsec(100);

	GPGDAT&=0xfffe;     
	dmsec(600);
  
       	 
	GPGDAT|=0x01;
	
	dmsec(100);
	GPGCON&=0xfffffffc;     //设置寄存器对18b20进行读操作
	i=GPGDAT;
	//if(i&0x01)   
}             



unsigned char tmrbyte (void)        //读一个字节函数
  {   
     unsigned int j;              
	 unsigned char i,u=0;      
	       
	 for (i=1;i<=8;i++)      
	 {
	  GPGCON&=0xfffffffc;
	  GPGCON|=0x01;
	         
	  GPGDAT&=0xfffe; 
	  u >>= 1;
	//  GPGDAT|=0x01;
	  
	  GPGCON&=0xfffffffc;
	  j=GPGDAT;
	  if(j&0x01)  u |= 0x80;
	  
	  dmsec(46);
	     
	 }        
	 return (u);       
  
}
         
void tmwbyte (unsigned char dat)     //写一个字节函数
{                       
	 unsigned char j;      
	 
	 GPGCON&=0xfffffffc;
	 GPGCON|=0x01;       
	 for (j=1;j<=8;j++)      
	 { 
	   GPGDAT&=0xfffe;
	   dmsec(1);      
	   GPGDAT|= (dat & 0x01);  
	   dmsec(47);
	   GPGDAT|=0x01;   
	  dat = dat >> 1;      
	 
   }        
} 

 
void tmstart (void)         //发送ds1820 开始转换
  {                          
 	tmreset();             //复位    
 	dmsec(120);            //延时    
 	tmwbyte(0xcc);         //跳过序列号命令   
 	tmwbyte(0x44);         //发转换命令 44H,
  }         




void tmrtemp (void)       //读取温度
    {                          
		unsigned char a,b; 
		tmreset ();      //复位     
		dmsec (200);     //延时     
		tmwbyte (0xcc);  //跳过序列号命令   
		tmwbyte (0xbe);  //发送读取命令     
		a = tmrbyte ();  //读取低位温度    
		b = tmrbyte ();  //读取高位温度           
		
		sdata = a/16+b*16;      //整数部分
		
		//xiaoshu1 = (a&0x0f)*10/16;    //小数第一位
	//	xiaoshu2 = (a&0x0f)*100/16%10;//小数第二位
	//	xiaoshu=xiaoshu1*10+xiaoshu2; //小数两位
	xiaoshu1=(a&0x0f)*0.0625*10000;
	xiaoshu=xiaoshu1/100;
//	sdata= a/16+b*16+(a&0x0f)*0.0625;
} 
/*
void zh(unsigned char wdata)//将温度值转换为ascii值
{
  
  wd[0]=wdata / 10+0x30;
  wd[1]=wdata % 10+0x30; 
  wd[2]=xiaoshu / 10+0x30;
  wd[3]=xiaoshu % 10+0x30;
}
*/

void DS18B20PRO(void)         
{    
  tmstart();  // uart(10);     
  dmsec(5); 	//如果是不断地读取的话可以不延时 //
  tmrtemp(); 	//读取温度,执行完毕温度将存于TMP中 //
}									  

/*
       
void uart()               //串口函数用于发送温度值
{	
	
    UFCON0 = 0x0;
    UMCON0 = 0x0;
    ULCON0 = 0x3;  
    UCON0  = 0x245;  
    UBRDIV0=( (int)(50000000/16/115200+0.5) -1 );
  	
    	while(!(UTRSTAT0 & 0x2));
		UTXH0='\n';
		while(!(UTRSTAT0 & 0x2));            
		UTXH0=wd[0];
		while(!(UTRSTAT0 & 0x2));
		UTXH0=wd[1];
		while(!(UTRSTAT0 & 0x2));
		UTXH0=46;
		while(!(UTRSTAT0 & 0x2));
		UTXH0=wd[2];
		while(!(UTRSTAT0 & 0x2));
		UTXH0=wd[3];
		while(!(UTRSTAT0 & 0x2));
		UTXH0=39;
		while(!(UTRSTAT0 & 0x2));
		UTXH0=67;
}*/
/*
void Delay(unsigned int x)        
{ 
  unsigned int i,j,k; 
  for(i=0;i<=x;i++) 
    for(j=0;j<0xff;j++) 
      for(k=0;k<0xff;k++); 
} 
*/