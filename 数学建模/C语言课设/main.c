//main.c 
#include "meal_tele_fun.h"
int main(int argc, char *argv[]) {
	Info guest[101];//����������100�ݶ��ͣ�1-100 
	int guest_number=0;//��ţ�ÿ�ζ��͵Ǽ�ʱ��һ ,���ļ�����
	guest_number=read(guest);
	interface();//������� 
	int option=0;
	int flag=0;
	while(1)//ѡ�����û�����Ƿ�ѡ��ʱ�����������룬һ�β�����ɺ������һ��������ʾ 
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
        	default: printf("������������ȷ�ı��: ");flag=1;break;
     	}
     	if(flag==1)break;
		}while(option!=1 && option!=2 && option!=3 && option!=4 && option!=5 && option!=6 && option!=7);
    	if(flag==1)continue;
    	printf("\n\n�ϴβ�������ɣ��������һ�β���\n");
    	printf("option 1: ���͵Ǽ�\n");
    	printf("option 2: ȡ������\n");
    	printf("option 3: ��ѯ������Ϣ\n");
    	printf("option 4: ���Ķ�����Ϣ\n");
    	printf("option 5: �˳�������ϵͳ\n");
    	printf("option 6: ʹ�ù���ԱȨ��\n");
    	printf("oprion 7: ��Ϣд�뵽���ݿ�\n");
    	printf("������ѡ����: ");
	}
	return 0;
}
