#include "def.h"
#define GPGCON (*(volatile unsigned *)0x56000060)     //18b20�Ĵ�������
#define GPGDAT (*(volatile unsigned *)0x56000064) 
#define GPGUP (*(volatile unsigned *)0x56000068) 
 
#define UFCON0     (*(volatile unsigned *)0x50000008)   //���ڼĴ�������
#define UMCON0     (*(volatile unsigned *)0x5000000c)
#define ULCON0     (*(volatile unsigned *)0x50000000)	
#define UCON0      (*(volatile unsigned *)0x50000004)
#define UBRDIV0    (*(volatile unsigned *)0x50000028)
#define UTRSTAT0   (*(volatile unsigned *)0x50000010)
#define UTXH0 		(*(volatile unsigned*)0x50000020)
#define URXH0 		(*(volatile unsigned*)0x50000024)
   

unsigned char wd[4];  
 unsigned int sdata;//���������¶ȵ���������
float xiaoshu1;//С����һλ
unsigned char xiaoshu2;//С���ڶ�λ
 unsigned int xiaoshu;//��λС��

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

int Temperature(void)                       //��ͣѭ������¶�ֵ����ת��Ϊasc||�룬ͨ�����ڴ�����
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

void dmsec (unsigned int t)       //��ȷ��ʱ����  
 {   
	unsigned int i;
    unsigned int j;
    j=1*t;
    for(i = 0; i < j; i++);
 } 
         
void tmreset (void)       //18b20��ʼ��
{   unsigned int i;                            
    
	GPGCON&=0xfffffffc;    //���üĴ�����18b20����д����
	GPGCON|=0x01;
	
	GPGDAT|=0x01;
    dmsec(100);

	GPGDAT&=0xfffe;     
	dmsec(600);
  
       	 
	GPGDAT|=0x01;
	
	dmsec(100);
	GPGCON&=0xfffffffc;     //���üĴ�����18b20���ж�����
	i=GPGDAT;
	//if(i&0x01)   
}             



unsigned char tmrbyte (void)        //��һ���ֽں���
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
         
void tmwbyte (unsigned char dat)     //дһ���ֽں���
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

 
void tmstart (void)         //����ds1820 ��ʼת��
  {                          
 	tmreset();             //��λ    
 	dmsec(120);            //��ʱ    
 	tmwbyte(0xcc);         //�������к�����   
 	tmwbyte(0x44);         //��ת������ 44H,
  }         




void tmrtemp (void)       //��ȡ�¶�
    {                          
		unsigned char a,b; 
		tmreset ();      //��λ     
		dmsec (200);     //��ʱ     
		tmwbyte (0xcc);  //�������к�����   
		tmwbyte (0xbe);  //���Ͷ�ȡ����     
		a = tmrbyte ();  //��ȡ��λ�¶�    
		b = tmrbyte ();  //��ȡ��λ�¶�           
		
		sdata = a/16+b*16;      //��������
		
		//xiaoshu1 = (a&0x0f)*10/16;    //С����һλ
	//	xiaoshu2 = (a&0x0f)*100/16%10;//С���ڶ�λ
	//	xiaoshu=xiaoshu1*10+xiaoshu2; //С����λ
	xiaoshu1=(a&0x0f)*0.0625*10000;
	xiaoshu=xiaoshu1/100;
//	sdata= a/16+b*16+(a&0x0f)*0.0625;
} 
/*
void zh(unsigned char wdata)//���¶�ֵת��Ϊasciiֵ
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
  dmsec(5); 	//����ǲ��ϵض�ȡ�Ļ����Բ���ʱ //
  tmrtemp(); 	//��ȡ�¶�,ִ������¶Ƚ�����TMP�� //
}									  

/*
       
void uart()               //���ں������ڷ����¶�ֵ
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