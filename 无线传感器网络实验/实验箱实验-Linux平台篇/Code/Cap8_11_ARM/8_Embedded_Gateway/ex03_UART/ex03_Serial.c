/*=========================================================================
  工程名称：	ex03_UART  
  组成文件：	ex03_Serial.c
  功能描述： 	用串口实现终端和试验箱之间通信
  硬件连接：			
  维护记录：	2011-04-12 v1.1		add by sunplus
=========================================================================*/

#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>

int main()
{
	struct termios options, oldoptions;										// 定义串口属性结构体变量，其中options用于重新设置串口属性，oldoptions用于原设置，用于恢复到原来的属性
	int fd;
	fd = open("/dev/s3c2410_serial0", O_RDWR);											// 打开串口0
	if(fd<0)
	{
		perror("tty open:");
		_exit(1);
	}
	tcgetattr(fd, &oldoptions);														// 获得当前的串口设置信息
	tcgetattr(fd, &options);
	cfsetispeed(&options, B115200);												// 设置输入波特率为115200
	cfsetospeed(&options, B115200);												// 设置输出波特率为115200

	options.c_cflag &= ~PARENB;														// 设置串口属性为：数据位为8位，停止位为1位，无奇偶校验
	options.c_cflag &= ~CSTOPB;
	options.c_cflag |= CSTOPB;
	options.c_cflag &= ~CSIZE;
	options.c_cflag &= ~CS8;
	options.c_cflag |= CS8;
	 
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);		// 设置串口为Raw模式
	options.c_oflag &= ~OPOST;

	tcsetattr(fd, TCSANOW, &options);											// 将上述设置生效
	
	char buf[1024];
	int len = 1024;
	int nByte;
	int rdadByte;
	write(fd, "testSerial:\n", 12);													// 向串口发送数据
	while(1)
	{
		rdadByte = read(fd, buf, len);												// 读串口
		if(buf[0] == '1')																		// 如果输入的字符为‘1’则回复串口的原设置并退出程序
		{
			printf("\n");
			tcsetattr(fd, TCSANOW, &oldoptions);
			break;
		}
		unsigned int i = 0;
		for(i = 0; i < 0xfffff; i++);
		nByte = write(fd, buf, rdadByte);													// 写串口							
	}
}
