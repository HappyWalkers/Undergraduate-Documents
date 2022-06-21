//meal_tele_fun.c

#include "meal_tele_fun.h"

void admin_opti(Info guest[])//����Ա����ѡ�� 
{
	    int option=0;
		printf("����1�Բ鿴������Ϣ������2�Բ鿴��ɾ���Ķ�����Ϣ");
		printf("\n������ѡ��: ");
		scanf("%d",&option);
		
		if(1==option)
		{
			print_all(guest);
		}
		else if(2==option)
		{
			FILE* fp=fopen("D:\\guest_dele_info.txt","r");//������Ϣ���ṹ������ 
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
    		if(guest_dele[guest_number].tele==0) break;//����tele���Ǳ���ʼ��Ϊ0��������0ʱ����ֹͣ����ʣ�µĿսṹ��
    	    }
			fclose(fp);
			
			print_all(guest_dele);
		}
		else
		{
			printf("��������ȷ��ѡ��!\n");
			admin_opti(guest);
		}
}

void print(Info guest)
{
	
	printf("����: %s\n",guest.name);
	printf("�绰����: %ld\n",guest.tele);
	printf("�ò�����: %d\n",guest.peo_num);
	printf("�ò�ʱ��: %s\n",guest.time);
	printf("�ò�ϲ��: %s\n",guest.like);
}

void print_all(Info guest[])//����˽ṹ������������Ϣ 
{
	printf("����\t�绰����\t�ò�����\t�ò�ʱ��\t�ò�ϲ��\n");
    for(int k=1;k<=100;k++)
    	{
    		if(guest[k].tele==0 && guest[k].peo_num==0 && guest[k].number==0)//������δ������Ϣ����ͽ�ֹ 
    		{
    			break;
    		}
    		printf("%s\t%ld\t\t %d \t\t %s \t\t %s \n",guest[k].name,guest[k].tele,guest[k].peo_num,guest[k].time,guest[k].like);
	    }	
}

void admin(Info guest[])//����Ա���� 
{
	printf("\n���������Ա�����Բ鿴ȫ����Ϣ: ");
	int key=0;
	scanf("%d",&key);
	if(12345==key)
	{
		admin_opti(guest);
	}
	else
	{
		printf("�����������������!\n");
		admin(guest);
	}
}

int read(Info guest[])//��txt�ļ��н��˿����ݶ��뵽�ṹ�壬�������һλ�˿͵ı�� ��������ɾ���ģ�ɾ�����ض���������ֹ��ֹͣ���룩 
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
		if(guest[guest_number].tele==0 && strcmp(guest[guest_number].name,"0")==0)//������ɾ�������ݣ���0 0 1��ָ���˸��ٶ� 
		{
			dele_gue(guest,guest_number);//����dele_gue��ɾ��������д��Ĺ��ܣ�����ų��ѱ�ɾ�������� 
			read(guest);//���´��ļ�����ṹ�� 
		} 
		if(guest[guest_number].tele==0) break;//����tele���Ǳ���ʼ��Ϊ0��������0ʱ����ֹͣ����ʣ�µĿսṹ��
	}
    fclose(fp);
	return *&guest_number-1;//������ʵ�����һ�������Լ�һ 
}

void dele_gue(Info guest[],int guest_number)//�Ƚ�Ҫɾ�������ݴ����µ��ļ�����ɾ���ṹ�������е�ָ�����ݣ��ٽ��ṹ������д�� 
{
	FILE* fs=fopen("D:\\guest_dele_info.txt","a");
	if(NULL==fs)
	{
		fprintf(stderr,"fopen fain in dele_gue fs");
		return;
	}
	fprintf(fs,"%s %ld %d %s %s %d\n",guest[guest_number].name,  guest[guest_number].tele, guest[guest_number].peo_num, guest[guest_number].time, guest[guest_number].like, guest_number);
	fclose(fs);
	
	for(int j=0;j<30;j++)//�������Ӧ�ṹ�� 
	{
		guest[guest_number].name[j]=0;
		guest[guest_number].time[j]=0;
		guest[guest_number].like[j]=0;
	}
	guest[guest_number].tele=0;
	guest[guest_number].peo_num=0;
	
	FILE *fp=fopen("D:\\guest_info.txt","w+");//���ṹ������д�� 
	if(NULL==fp)
	{
		printf("fopen fail in dele_gue");
		return;
	}
	for(int k=1;k<=guest_number-1;k++)//����д�룬������δ��������Ϣ����ͽ�ֹ 
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

void meal_canc_option(Info guest[],int i)//����meal_canc���optionѡ�����ѡ����й����л���iΪ��������Ĺ˿ͱ�� 
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
		printf("������������ȷ��ѡ��: ");
		meal_canc_option(guest,i);
	}
}

int compare(Info guest[])//��������������͵绰����Ѱ�ҷ��ϵĹ˿���Ϣ�������Ϣ�����ع˿ͱ�� 
{
	printf("\n��������������: ");
	char name[30];
	scanf("%s",name);
	
	printf("���������ĵ绰����: ");//��ֹͬ��
	long tele;
	scanf("%ld",&tele);
	
	int i=0;
	for(i=1;i<=100;i++)
	{
		if(strcmp(name,guest[i].name)==0 && tele==guest[i].tele)
		{
			printf("\n��˶�������Ϣ");
			print(guest[i]);
			return *(&i);
		}
	}
	printf("�Բ���ϵͳδ��⵽������Ϣ");
	return 0;
}

void interface()//��ʼ���� 
{
	printf("-------------------------��ӭʹ�������Ƶ�绰����ϵͳ----------------------------\n");
	printf("�밴�����������Ҫ�����ǽ��߳�Ϊ������\n");
	printf("option 1: ���͵Ǽ�\n");
	printf("option 2: ȡ������\n");
	printf("option 3: ��ѯ������Ϣ\n");
	printf("option 4: ���Ķ�����Ϣ\n");
	printf("option 5: �˳�������ϵͳ\n");
	printf("option 6: ʹ�ù���ԱȨ��\n");
	printf("oprion 7: ��Ϣд�뵽���ݿ�\n");
	printf("������ѡ����: ");
}

void meal_regi_opti(Info guest[],int guest_number)
{ 
	printf("�밴��Ӧ������������ò�ѡ��: ");
	int sele=0;
	scanf("%d",&sele);
	if(1==sele)
	{
		strcpy(guest[guest_number].like,"�ײ�һ");
	}
	else if(2==sele)
	{
		strcpy(guest[guest_number].like,"�ײͶ�");
	}
	else if(3==sele)
	{
		strcpy(guest[guest_number].like,"�ײ���");
	}
	else
	{
		printf("������������ȷѡ��");
		meal_regi_opti(guest,guest_number);
	}
	
}

void meal_regi(Info guest[],int guest_number)//���͵Ǽǣ�����Ϣ����ṹ�壬�ٴ浽txt�ļ���ȥ��ע���ַ 
{
	guest[guest_number].number=guest_number;
	printf("���������������� ");
	scanf("%s",guest[guest_number].name);
	printf("���������ĵ绰����: ");
	scanf("%ld",&guest[guest_number].tele);
	printf("�������ò�����: ");
	scanf("%d",&guest[guest_number].peo_num);
	printf("�������ò�ʱ��:(y/m/d/h/min) ");
	scanf("%s",guest[guest_number].time);
	printf("�����ṩ�����ײ͹�ѡ��:\n");
	printf("�ײ�һ: ����������+�׷�+�����Ź���\n");
	printf("�ײͶ�: ����������+�׷�+������\n");
	printf("�ײ���: ����+����+�����\n");
	meal_regi_opti(guest,guest_number);
	
	FILE *fp=fopen("D:\\guest_info.txt","a");
	if(NULL==fp)
	{
		printf("fopen fail in meal_regi");
		return;
	}
	//���ļ�����д�� ���� �绰���� �ò����� �ò�ʱ�� �ò�ϲ�� ��ţ�����󣬷����ȡ�� 
	fprintf(fp,"%s %ld %d %s %s %d\n",guest[guest_number].name,  guest[guest_number].tele, guest[guest_number].peo_num, guest[guest_number].time, guest[guest_number].like, guest_number);
	fclose(fp);
}

void meal_canc(Info guest[])//ȡ������ 
{
	int i=compare(guest);//��������Ĺ˿ͱ�� 
	if(0==i)
	{
		return;
	}
	printf("�����Ƿ�ȷ��ȡ���˴ζ���(ȷ��������1����Ϣ������������д������2���񲢷������˵�������3\n");
   	printf("������ѡ��: ");	
	meal_canc_option(guest,i);
}

void meal_inqu(Info guest[])
{
	printf("\nѡ������������1��ѡ��绰����������2\n");
	printf("������ѡ��: ");
	int option=0;
	scanf("%d",&option);
	
	char name[30];
	long tele;
	if(1==option)
	{
		printf("����������: ");
		scanf("%s",name);
		for(int i=1;i<=100;i++)
		{
			if(strcmp(name,guest[i].name)==0)
			{
			print(guest[i]);
			return;
			}
		}
		printf("�Բ���ϵͳδ��⵽������Ϣ");
	}
	else if(2==option)
	{
		printf("������绰����: ");
		scanf("%ld",&tele);
		for(int i=1;i<=100;i++)
		{
			if(tele==guest[i].tele)
			{
			print(guest[i]);
			return;
			}
		}
		printf("�Բ���ϵͳδ��⵽������Ϣ");
	}
	else
	{
		printf("������������ȷ��ѡ��!\n");
		meal_inqu(guest);
	}
}

void meal_rewr(Info guest[])//���ṹ������д���ļ��� 
{
	FILE *fp=fopen("D:\\guest_info.txt","w+");
	if(NULL==fp)
	{
		printf("fopen fail in meal_rewr");
		return;
	}
	for(int k=1;k<=100;k++)
	{
		if(guest[k].tele==0 && guest[k].peo_num==0 && guest[k].number==0)//������δ������Ϣ����ͽ�ֹ 
		{
			break;
		}
		fprintf(fp,"%s %ld %d %s %s %d\n",guest[k].name,  guest[k].tele, guest[k].peo_num, guest[k].time, guest[k].like, guest[k].number);
	}
	fclose(fp);
}

void meal_chan(Info guest[])
{
	printf("���ľͲ�ʱ��������1�����ľͲ�����������2��������������3\n");
	printf("������ѡ��: ");
	int option=0;
	scanf("%d",&option);
	
	if(1==option)
	{
	int i=compare(guest);
	if(0==i)return;//δ��ѯ����Ϣʱ�˳�
	printf("�������޸ĺ��ʱ��: ");
	char new_time[30];
	scanf("%s",new_time);
	strcpy(guest[i].time,new_time);
	meal_rewr(guest);
    }
    
    else if(2==option)
    {
    int i=compare(guest);
	if(0==i)return;//δ��ѯ����Ϣʱ�˳�
	printf("�������޸ĺ�ľͲ�����: ");
	int new_num=0;
	scanf("%d",&new_num);
	guest[i].peo_num=new_num;
	meal_rewr(guest); 
	}
	
	else if(3==option)
	{
	int i=compare(guest);
	if(0==i)return;//δ��ѯ����Ϣʱ�˳�
	printf("�������޸ĺ��ʱ��: ");
	char new_time[30];
	scanf("%s",new_time);
	strcpy(guest[i].time,new_time);
	
	printf("�������޸ĺ�ľͲ�����: ");
	int new_num;
	scanf("%d",&new_num);
	guest[i].peo_num=new_num;
	
	meal_rewr(guest);
	}
	
	else
	{
		printf("������������ȷ��ѡ��!\n");
		meal_chan(guest);
	}
}
