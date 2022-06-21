//node_practice_operation.c

#include "node_practice_operation.h"

node * create(INFO info)//only used to create and return a head node
{
	node * head;
	head=malloc(sizeof(node));
	if(NULL==head)
	{
		printf("Error: malloc failed in create \n");
	}
	head->info=info;
	head->next=NULL;
	return head;
}

int length(node * head)//include head
{
	int len=0;
	while(NULL!=head)
	{
		head=head->next;
		len++;
	}
	return len;
}

int inquire(node* head,int number)//inquire the number of the input
{
	int position=1;
	node* p=head;//pointer of work
	while(position<=length(head) && p->info.score!=number)
	{
		p=p->next;
		position++;
	}
	if(position<=length(head))return position;
	else return 0;
}

node* inverse(node* head)
{
	node* now=head;
	node* pre=head;
	node* aft=head;
	int len=length(head);
	int i=0;
	do
	{
		if(i==0)
		{
			aft=now->next;
			now->next=NULL;
		}
		else
		{
			pre=now;
			now=aft;
			aft=now->next;
	    	now->next=pre;
		}
		i++;
	}while(i<len);
	return now;
}

node* insert(node * head,INFO info,int position)//插入到head之后的第position个位置 
{
	if(position<0 || position>length(head))
	{
		printf("Illegal position in insert");
		return;
	}
	
	node* new_node=malloc(sizeof(node));
	if(NULL==new_node)
	{
		printf("Error: malloc failed in insert \n");
	}
	
	new_node->info=info;
	
	if(position==0)
	{
		new_node->next=head;
		head=new_node;
	}
	else
	{
	while(--position)head=head->next;
	new_node->next=head->next;
	head->next=new_node;
	}
	return new_node;
}

void delete(node* head,int position)//删除head之后的第position个节点 
{
	if(position<1 || position>length(head))
	{
		printf("Illegal poisition in delete");
		return;
	}
	while(--position)head=head->next;
	head->next=head->next->next;
}

void print(node *head)
{
	while(NULL!=head)
	{
		printf("the score of the node is: ");
		printf("%d\n",head->info.score);
		head=head->next;
	}
}

void destory(node* head)
{
	int count=length(head);
	while(--count)
	{
		delete(head,count);
	}
	free(head);
}

void swap(int *a,int *b)
{
	int temp=*a;
	*a=*b;
	*b=temp;
}

void bubble_sort1(node* head)//soga,in my opinion...in fact,it's selection sort
{
	for(node* p=head;NULL!=p; p=p->next)
	{
		for(node* q=p;NULL!=q;q=q->next)
		{
			if(q->info.score > p->info.score)
			{
				swap(&p->info.score,&q->info.score);//jiao huan liang jie dian weizhi
			}
		}
	}
}

void bubble_sort2(node* head)//bubble sort is j & j+1, but not i & j(selection) emmm maybe
{
	int len=length(head);
	int flag;
	node *c1,*c2;
	for(int i=0;i<len-1;i++)
	{
		flag=0;
		for(int j=0;j<len-1-i;j++)
		{
			c1=get_node(head,j);
			c2=c1->next;
			if(c1->info.score < c2->info.score)
			{
				swap_info(&c1->info,&c2->info);
				flag=1;
			}
		}
		if(flag==0)
		{
			break;
		}
	}
}

void swap_info(INFO* a,INFO* b)
{
	INFO temp=*a;
	*a=*b;
	*b=temp;
}

node* get_node(node* head, int pos)//return NO.pos node after head, just like a arrray
{
	if(pos<0 || pos>=length(head))
	{
		printf("Illegal position in get_node");
		return NULL;
	}
	while(NULL!=head && pos--)head=head->next;
	return head;
}

void selection_sort(node * head)//from big to small
{
	node *c1,*c2;
	int len=length(head);
	for(int i=0;i<len;i++)
	{
		int flag=i;
		for(int j=i+1;j<len;j++)
		{
			c1=get_node(head,j);
			c2=get_node(head,flag);
			if(c1->info.score > c2->info.score)
			{
				flag=j;
			}
		}
		
		if(i!=flag)
		{
			c1=get_node(head,i);
			c2=get_node(head,flag);
			swap_info(&c1->info,&c2->info);
		}
	}
}

node* insertion_sort(node* head)
{
	int len=length(head);
	node *c1,*c2;
	for(int i=1;i<len;i++)
	{
		c1=get_node(head,i);
		int flag=i;
		for(int j=i-1;j>=0;j--)
		{
			c2=get_node(head,j);
			if(c1->info.score > c2->info.score)
			{
				node* p=insert(head,c1->info,j);
			    if(j==0)
			    {
			    	delete(head,flag);
			    	head=p;
				}
				else
				{
					delete(head,flag+1);
				}
			}
			else
			{
				c2->next=c1;
			}
			flag--;
			
		}
	}
	return head;
}

void quick_sort_recursive(node* head,int start,int end)//just like a array
{
	if(start>=end)return;
	int left=start,right=end;
	INFO mid=head->info;
	INFO com1,com2;
	while(left<right)
	{
		do
		{
			left++;
			com1=get_node(head,left)->info;
		}while(com1.score <= mid.score && left<end);
		
		do
		{
			com2=get_node(head,right)->info;
			right--;
		}while(com2.score >= mid.score && right>start);
		right++;//使right与com2对应 
		if(left<right)
		{
			swap_info(&com1,&com2);
		}
	}
	swap_info(&mid,&com2);
	quick_sort_recursive(head,start,left-1);//left is the first number of the higher area
	quick_sort_recursive(head,left,end-1);
}

void quick_sort(node* head)
{
	int len=length(head);
	quick_sort_recursive(head,0,len-1);
}
