//main.c 
#include "meal_tele_fun.h"
int main(int argc, char *argv[]) {
	Info guest[101];//餐厅最多接受100份订餐，1-100 
	int guest_number=0;//编号，每次订餐登记时加一 ,从文件读入
	guest_number=read(guest);
	interface();//绘出界面 
	int option=0;
	int flag=0;
	while(1)//选择，在用户输入非法选项时提醒重新输入，一次操作完成后给出下一步操作提示 
	{
		scanf("%d",&option);
		do{
		switch(option)
     	{
        	case 1: guest_number++;meal_regi(guest,guest_number);;break;
        	case 2: meal_canc(guest);break;
	        case 3: meal_inqu(guest);break;
        	case 4: meal_chan(guest);break;
        	case 5: return 0; 
        	case 6: admin(guest);break;
        	case 7: exp();break; 
        	default: printf("请重新输入正确的编号: ");flag=1;break;
     	}
     	if(flag==1)break;
		}while(option!=1 && option!=2 && option!=3 && option!=4 && option!=5 && option!=6 && option!=7);
    	if(flag==1)continue;
    	printf("\n\n上次操作已完成，请继续下一次操作\n");
    	printf("option 1: 订餐登记\n");
    	printf("option 2: 取消订餐\n");
    	printf("option 3: 查询订餐信息\n");
    	printf("option 4: 更改订餐信息\n");
    	printf("option 5: 退出本订餐系统\n");
    	printf("option 6: 使用管理员权限\n");
    	printf("oprion 7: 信息写入到数据库\n");
    	printf("请输入选项编号: ");
	}
	return 0;
}
