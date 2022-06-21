//struct_info

typedef struct mystruct
{
	int number;//编号 
	char name[30];
	long tele;
	int peo_num;//用餐人数<=20
	char time[30];
	char like[100];//用餐喜好，动态分配内存
}Info;
