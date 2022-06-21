//node_practioce_main.c

#include "node_practice_operation.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void main(int argc, char *argv[]) {
	printf("-------create with 1 node-------\n");
	INFO info1={2000};
	node *head=create(info1);
	printf("length=%d\n",length(head));
	print(head);
	printf("\n");

	printf("--------Insert after 1st Node-----\n");
	INFO info2={2001};
	insert(head,info2,1);
	printf("length=%d\n",length(head));
	print(head);
	printf("\n");
	
	printf("-------Insert after 2nd Node-----\n");
	INFO info3={2002};
	insert(head,info3,2);
	printf("length=%d\n",length(head));
	print(head);
	printf("\n");
	
	printf("--Inquire the Node with the value of 2001--\n");
	int number_look=inquire(head,2001);
	if(number_look>0)
	{
		printf("the number of the node with 2001 is: ");
        printf("%d\n",number_look);
	}
	else
	printf("illegal position\n");
	printf("\n");
	
	printf("----Inverse the list------\n");
	printf("before inverse:\n");
	print(head);
	head=inverse(head);
	printf("after inverse:\n");
	print(head);
	printf("\n");
	
	printf("-----------Delete 3rd Node------\n");
	delete(head,2);
	printf("length=%d\n",length(head));
	print(head);
	printf("\n");
	
//	printf("--------Destroy all nodes-------\n");
//	destory(head);
//	printf("-----------destroy done-------\n\n");
//	printf("-------create several nodes -----\n");
//	head=create(info1);
//	insert(head,info2,1);
//	insert(head,info3,2);
//	printf("length=%d\n",length(head));
//	print(head);
//	printf("\n");
	
//	printf("------After bubble_sort1 ----\n");
//	bubble_sort1(head);
//	print(head);
//	printf("\n");
	
//	printf("------After bubble_sort2-----\n");//wrong
//	bubble_sort2(head);
//	print(head);
//	printf("\n");
	
//	printf("------After selection_sort------\n");
//	selection_sort(head);
//	print(head);
//	printf("\n");
	
//	printf("-----After insertion_sort-------\n");
//	head =insertion_sort(head);
//	print(head);
//	printf("\n");
	
//	printf("------After quick_sort---------\n");\\amazing, it works
//	quick_sort(head);
//	print(head);
//	printf("\n");
	

}
