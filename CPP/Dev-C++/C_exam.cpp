//��������1
struct node *search_list(struct node *list,int n)//list�Ǹ������׵�ַ,n��Ҫ�����Ľṹ���е�ֵ��nodeΪ�ṹ����
{
	struct node*p;
	for(p=list;p!=NULL;p=p-next)//û�����ͽ���Ѱ��
	{
		if (p->value==n)//����ҵ���ֵ
		{
			return p;//��������ڵ��ָ��
		}
		return NULL;//û�ҵ��ͷ��ؿ�ָ��
	}
}

//��������2,��1��ȣ�ֱ��ʹ��list,����Ϊ������Soû�� ���Ҹ���while
struct node *search_list(struct node *list, int n)
{
	while(list!=NULL && list->value!=n)//û����� ���� û�ҵ���ȷ��ֵ ʱ
	list =list->next;//ָ����ƣ�����Ѱ��
	return list;
}

//ɾ���ڵ�
struct node* delete_from_list(struct node *list,int n)
{
	struct node *cur, *prev;//curΪָ��ǰ�ڵ��ָ�룬prevΪָ��ǰһ�ڵ��ָ��
	for(cur=list,prev=NULL ; cur!=NULL && cur->value!=n ; prev=cur, cur=cur->next)//û�������curû�ҵ���ȷ��nʱ��prev��cur���ƣ�����Ѱ��
	;
	if(cur==NULL)//������û�ҵ�valueΪn�Ľڵ�ʱ
	return list;//��ʱ��list��ΪNULL
	if(prev==NULL)//prevָ��NULL,��curָ���һ���ڵ�ʱ����n�ڵ�һ���ڵ�
	list=list->next;//����ͷָ����ƣ���ɾ����һ���ڵ�
	else//n�������ڵ�ʱ
	prev->next=cur-next;//n��ǰһ��ָ���ƹ�n,ָ��n�ĺ�һ���ڵ㣬��ɾ��n���ڽڵ�
	free(cur);//�ͷ��ѱ�ɾ���Ľڵ�ָ��
	return list;//�����������ͷָ��
}

//special prime
#include <stdio.h>
#include <stdlib.h>

int is_prime(int n)
{
	int i;
	for(i=2;i<=n/2;i++)
	{
		if(n%i==0)
		return 0;
	}
	return 1;
}

void split(int n,int a[])
{
	for(int i=0;;i++)
	{
		a[i]=n%10;
		n/=10;
		if(i==3)break;
	}
	return;
}
int sum(int a[])
{
	int all=0;
	int i;
	for(i=0;i<10;i++)
	{
		all+=a[i];
	}
	return all;
}
void main()
{
	int a[10]={0};
	int i;
	int flag=0;
	for(i=2;i<=5000;i++)
	{
		if(is_prime(i))
		{
			split(i,a);
			int j;
			for(j=0;j<4;j++)
			{
				if(is_prime(a[j]))
				{
					flag=1;
				}
				else
				{
					flag=0;
					break;
				}
			}
			if(flag==1 && is_prime(sum(a)))
			{
				printf("we find a special prime: %d\n",i);
			}
		}
	}
}

//���ؿ�����pi
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
int main()
{
	srand((unsigned int)time(NULL));
    long long m=0;
    long long n=100000000; //1ww
    double x,y,pi;
    long long i; 
    for(i=0; i<n;i++)
    {
        x = 1.0*rand()/RAND_MAX;
        y =1.0*rand()/RAND_MAX;
        if( (x*x+y*y)<=1.0)
        {
            m++;
        }
    }
    pi = 4.0*m/n;
    return  pi;
}

//��ת�ַ���
#include <stdio.h>
#include <stdlib.h>
int main()
{
	char a[10]="abcdefghi";
	int i=0,j=8;//a[9]='/0'
	while(1)
	{
		if(j<=i)break;
		char temp=a[i];
		a[i]=a[j];
		a[j]=temp;
		i++;
		j--;
	}
	puts(a);
}

