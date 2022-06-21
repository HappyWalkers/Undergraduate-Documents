//meal_tele_fun.c

#include "meal_tele_fun.h"

void admin_opti(Info guest[])//管理员功能选项 
{
	    int option=0;
		printf("输入1以查看订单信息，输入2以查看已删除的订单信息");
		printf("\n请输入选项: ");
		scanf("%d",&option);
		
		if(1==option)
		{
			print_all(guest);
		}
		else if(2==option)
		{
			FILE* fp=fopen("D:\\guest_dele_info.txt","r");//读入信息到结构体数组 
			if(NULL==fp)
			{
				printf("fopen fain in admin_option fp");
				return;
			}
			Info guest_dele[101];
			for(int guest_number=1;guest_number<=100;guest_number++)
         	{
    		fscanf(fp,"%s",guest_dele[guest_number].name);
    		fscanf(fp,"%ld",&guest_dele[guest_number].tele);
     		fscanf(fp,"%d",&guest_dele[guest_number].peo_num);
    		fscanf(fp,"%s",guest_dele[guest_number].time);
    		fscanf(fp,"%s",guest_dele[guest_number].like);
    		fscanf(fp,"%d",&guest_dele[guest_number].number); 
    		if(guest_dele[guest_number].tele==0) break;//由于tele总是被初始化为0，故碰到0时，即停止读入剩下的空结构体
    	    }
			fclose(fp);
			
			print_all(guest_dele);
		}
		else
		{
			printf("请输入正确的选项!\n");
			admin_opti(guest);
		}
}

void print(Info guest)
{
	
	printf("姓名: %s\n",guest.name);
	printf("电话号码: %ld\n",guest.tele);
	printf("用餐人数: %d\n",guest.peo_num);
	printf("用餐时间: %s\n",guest.time);
	printf("用餐喜好: %s\n",guest.like);
}

void print_all(Info guest[])//输出此结构体数组所有信息 
{
	printf("姓名\t电话号码\t用餐人数\t用餐时间\t用餐喜好\n");
    for(int k=1;k<=100;k++)
    	{
    		if(guest[k].tele==0 && guest[k].peo_num==0 && guest[k].number==0)//遇到尚未存入信息的项就截止 
    		{
    			break;
    		}
    		printf("%s\t%ld\t\t %d \t\t %s \t\t %s \n",guest[k].name,guest[k].tele,guest[k].peo_num,guest[k].time,guest[k].like);
	    }	
}

void admin(Info guest[])//管理员功能 
{
	printf("\n请输入管理员密码以查看全部信息: ");
	int key=0;
	scanf("%d",&key);
	if(12345==key)
	{
		admin_opti(guest);
	}
	else
	{
		printf("密码错误，请重新输入!\n");
		admin(guest);
	}
}

int read(Info guest[])//从txt文件中将顾客数据读入到结构体，返回最后一位顾客的编号 （遇到已删除的，删除并重读，遇到截止，停止读入） 
{
	int guest_number=0;
	FILE *fp=fopen("D:\\guest_info.txt","a+");
	if(NULL==fp)
	{
		printf("fopen fail in read");
		return 0;
	}
	
	for(guest_number=1;guest_number<=100;guest_number++)
	{
		fscanf(fp,"%s",guest[guest_number].name);
		fscanf(fp,"%ld",&guest[guest_number].tele);
		fscanf(fp,"%d",&guest[guest_number].peo_num);
		fscanf(fp,"%s",guest[guest_number].time);
		fscanf(fp,"%s",guest[guest_number].like);
		fscanf(fp,"%d",&guest[guest_number].number);
		if(guest[guest_number].tele==0 && strcmp(guest[guest_number].name,"0")==0)//遇到被删除的内容，即0 0 1，指针退格再读 
		{
			dele_gue(guest,guest_number);//利用dele_gue的删除、重新写入的功能，逐个排除已被删除的内容 
			read(guest);//重新从文件读入结构体 
		} 
		if(guest[guest_number].tele==0) break;//由于tele总是被初始化为0，故碰到0时，即停止读入剩下的空结构体
	}
    fclose(fp);
	return *&guest_number-1;//由于其实多读了一个，所以减一 
}

void dele_gue(Info guest[],int guest_number)//先将要删除的数据存入新的文件，再删除结构体数组中的指定内容，再将结构体重新写入 
{
	FILE* fs=fopen("D:\\guest_dele_info.txt","a");
	if(NULL==fs)
	{
		fprintf(stderr,"fopen fain in dele_gue fs");
		return;
	}
	fprintf(fs,"%s %ld %d %s %s %d\n",guest[guest_number].name,  guest[guest_number].tele, guest[guest_number].peo_num, guest[guest_number].time, guest[guest_number].like, guest_number);
	fclose(fs);
	
	for(int j=0;j<30;j++)//再清除对应结构体 
	{
		guest[guest_number].name[j]=0;
		guest[guest_number].time[j]=0;
		guest[guest_number].like[j]=0;
	}
	guest[guest_number].tele=0;
	guest[guest_number].peo_num=0;
	
	FILE *fp=fopen("D:\\guest_info.txt","w+");//将结构体重新写入 
	if(NULL==fp)
	{
		printf("fopen fail in dele_gue");
		return;
	}
	for(int k=1;k<=guest_number-1;k++)//重新写入，遇到尚未存入新信息的项就截止 
	{
		fprintf(fp,"%s %ld %d %s %s %d\n",guest[k].name,  guest[k].tele, guest[k].peo_num, guest[k].time, guest[k].like, guest[k].number);
	}
	for(int k=guest_number+1;k<=100;k++)
	{
		if(guest[k].tele==0 && guest[k].peo_num==0 && guest[k].number==0)
		{
			break;
		}
		fprintf(fp,"%s %ld %d %s %s %d\n",guest[k].name,  guest[k].tele, guest[k].peo_num, guest[k].time, guest[k].like, guest[k].number);
	}
	fclose(fp);
}

void meal_canc_option(Info guest[],int i)//读入meal_canc里的option选项，根据选项进行功能切换，i为符合输入的顾客编号 
{
	int option=0;
	scanf("%d",&option);
	if(1==option)
   	{
    	dele_gue(guest,i);
   	}
   	else if(2==option)
   	{
   		meal_canc(guest);
	}
	else if(3==option)
	{
		system("CLS");
		interface();
	}
	else
	{
		printf("请重新输入正确的选项: ");
		meal_canc_option(guest,i);
	}
}

int compare(Info guest[])//根据输入的姓名和电话号码寻找符合的顾客信息，输出信息，返回顾客编号 
{
	printf("\n请输入您的姓名: ");
	char name[30];
	scanf("%s",name);
	
	printf("请输入您的电话号码: ");//防止同名
	long tele;
	scanf("%ld",&tele);
	
	int i=0;
	for(i=1;i<=100;i++)
	{
		if(strcmp(name,guest[i].name)==0 && tele==guest[i].tele)
		{
			printf("\n请核对您的信息");
			print(guest[i]);
			return *(&i);
		}
	}
	printf("对不起，系统未检测到您的信息");
	return 0;
}

void interface()//初始界面 
{
	printf("-------------------------欢迎使用升华酒店电话订餐系统----------------------------\n");
	printf("请按编号输入您的要求，我们将竭诚为您服务\n");
	printf("option 1: 订餐登记\n");
	printf("option 2: 取消订餐\n");
	printf("option 3: 查询订餐信息\n");
	printf("option 4: 更改订餐信息\n");
	printf("option 5: 退出本订餐系统\n");
	printf("option 6: 使用管理员权限\n");
	printf("oprion 7: 信息写入到数据库\n");
	printf("请输入选项编号: ");
}

void meal_regi_opti(Info guest[],int guest_number)
{ 
	printf("请按对应序号输入您的用餐选项: ");
	int sele=0;
	scanf("%d",&sele);
	if(1==sele)
	{
		strcpy(guest[guest_number].like,"套餐一");
	}
	else if(2==sele)
	{
		strcpy(guest[guest_number].like,"套餐二");
	}
	else if(3==sele)
	{
		strcpy(guest[guest_number].like,"套餐三");
	}
	else
	{
		printf("请重新输入正确选项");
		meal_regi_opti(guest,guest_number);
	}
	
}

void meal_regi(Info guest[],int guest_number)//订餐登记，将信息存入结构体，再存到txt文件中去，注意地址 
{
	guest[guest_number].number=guest_number;
	printf("请输入您的姓名： ");
	scanf("%s",guest[guest_number].name);
	printf("请输入您的电话号码: ");
	scanf("%ld",&guest[guest_number].tele);
	printf("请输入用餐人数: ");
	scanf("%d",&guest[guest_number].peo_num);
	printf("请输入用餐时间:(y/m/d/h/min) ");
	scanf("%s",guest[guest_number].time);
	printf("我们提供三个套餐供选择:\n");
	printf("套餐一: 西红柿炒蛋+米饭+冬瓜排骨汤\n");
	printf("套餐二: 土豆红烧肉+米饭+肉丸汤\n");
	printf("套餐三: 汉堡+鸡腿+鸡肉卷\n");
	meal_regi_opti(guest,guest_number);
	
	FILE *fp=fopen("D:\\guest_info.txt","a");
	if(NULL==fp)
	{
		printf("fopen fail in meal_regi");
		return;
	}
	//向文件依次写入 姓名 电话号码 用餐人数 用餐时间 用餐喜好 编号（放最后，方便读取） 
	fprintf(fp,"%s %ld %d %s %s %d\n",guest[guest_number].name,  guest[guest_number].tele, guest[guest_number].peo_num, guest[guest_number].time, guest[guest_number].like, guest_number);
	fclose(fp);
}

void meal_canc(Info guest[])//取消订餐 
{
	int i=compare(guest);//符合输入的顾客编号 
	if(0==i)
	{
		return;
	}
	printf("请问是否确认取消此次订餐(确认请输入1，信息错误想重新填写请输入2，否并返回主菜单请输入3\n");
   	printf("请输入选项: ");	
	meal_canc_option(guest,i);
}

void meal_inqu(Info guest[])
{
	printf("\n选择姓名请输入1，选择电话号码请输入2\n");
	printf("请输入选项: ");
	int option=0;
	scanf("%d",&option);
	
	char name[30];
	long tele;
	if(1==option)
	{
		printf("请输入姓名: ");
		scanf("%s",name);
		for(int i=1;i<=100;i++)
		{
			if(strcmp(name,guest[i].name)==0)
			{
			print(guest[i]);
			return;
			}
		}
		printf("对不起，系统未检测到您的信息");
	}
	else if(2==option)
	{
		printf("请输入电话号码: ");
		scanf("%ld",&tele);
		for(int i=1;i<=100;i++)
		{
			if(tele==guest[i].tele)
			{
			print(guest[i]);
			return;
			}
		}
		printf("对不起，系统未检测到您的信息");
	}
	else
	{
		printf("请重新输入正确的选项!\n");
		meal_inqu(guest);
	}
}

void meal_rewr(Info guest[])//将结构体重新写入文件流 
{
	FILE *fp=fopen("D:\\guest_info.txt","w+");
	if(NULL==fp)
	{
		printf("fopen fail in meal_rewr");
		return;
	}
	for(int k=1;k<=100;k++)
	{
		if(guest[k].tele==0 && guest[k].peo_num==0 && guest[k].number==0)//遇到尚未存入信息的项就截止 
		{
			break;
		}
		fprintf(fp,"%s %ld %d %s %s %d\n",guest[k].name,  guest[k].tele, guest[k].peo_num, guest[k].time, guest[k].like, guest[k].number);
	}
	fclose(fp);
}

void meal_chan(Info guest[])
{
	printf("更改就餐时间请输入1，更改就餐人数请输入2，都更改请输入3\n");
	printf("请输入选项: ");
	int option=0;
	scanf("%d",&option);
	
	if(1==option)
	{
	int i=compare(guest);
	if(0==i)return;//未查询到信息时退出
	printf("请输入修改后的时间: ");
	char new_time[30];
	scanf("%s",new_time);
	strcpy(guest[i].time,new_time);
	meal_rewr(guest);
    }
    
    else if(2==option)
    {
    int i=compare(guest);
	if(0==i)return;//未查询到信息时退出
	printf("请输入修改后的就餐人数: ");
	int new_num=0;
	scanf("%d",&new_num);
	guest[i].peo_num=new_num;
	meal_rewr(guest); 
	}
	
	else if(3==option)
	{
	int i=compare(guest);
	if(0==i)return;//未查询到信息时退出
	printf("请输入修改后的时间: ");
	char new_time[30];
	scanf("%s",new_time);
	strcpy(guest[i].time,new_time);
	
	printf("请输入修改后的就餐人数: ");
	int new_num;
	scanf("%d",&new_num);
	guest[i].peo_num=new_num;
	
	meal_rewr(guest);
	}
	
	else
	{
		printf("请重新输入正确的选项!\n");
		meal_chan(guest);
	}
}
