//搜索链表1
struct node *search_list(struct node *list,int n)//list是该链表首地址,n是要搜索的结构体中的值，node为结构体名
{
	struct node*p;
	for(p=list;p!=NULL;p=p-next)//没到最后就接着寻找
	{
		if (p->value==n)//如果找到该值
		{
			return p;//返回这个节点的指针
		}
		return NULL;//没找到就返回空指针
	}
}

//搜索链表2,与1相比，直接使用list,由于为副本，So没错 并且改用while
struct node *search_list(struct node *list, int n)
{
	while(list!=NULL && list->value!=n)//没到最后 并且 没找到正确的值 时
	list =list->next;//指针后移，接着寻找
	return list;
}

//删除节点
struct node* delete_from_list(struct node *list,int n)
{
	struct node *cur, *prev;//cur为指向当前节点的指针，prev为指向前一节点的指针
	for(cur=list,prev=NULL ; cur!=NULL && cur->value!=n ; prev=cur, cur=cur->next)//没到最后，且cur没找到正确的n时，prev与cur后移，接着寻找
	;
	if(cur==NULL)//链表中没找到value为n的节点时
	return list;//此时，list即为NULL
	if(prev==NULL)//prev指向NULL,即cur指向第一个节点时，即n在第一个节点
	list=list->next;//链表头指针后移，即删除第一个节点
	else//n在其他节点时
	prev->next=cur-next;//n的前一个指针绕过n,指向n的后一个节点，即删除n所在节点
	free(cur);//释放已被删除的节点指针
	return list;//返回新链表的头指针
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

//蒙特卡洛求pi
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

//逆转字符串
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

