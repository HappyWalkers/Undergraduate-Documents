1.Attendance.zip
QT应用程序--考勤系统

2.wsn_storesys.sql
初始数据库表

3.xampp-win32-1.8.2-4-VC9-installer.exe
MySQL服务器工具

4.仓储管理系统PC端数据库使用说明书-中南大大学.pdf
系统使用说明

注意：
1）MainWidget.cpp中读卡器连接网关的串口：
#define	DEFAULT_RFID_125K_PORT	"/dev/ttyUSB0"      //根据实际情况调整

2）DBControl.cpp 中服务器IP地址：
#define DEFAULT_DB_SERVER_IP	"172.20.224.59"  
也要根据实际情况修改

3）编译QT为嵌入式版本，放在实验台的网关上运行。