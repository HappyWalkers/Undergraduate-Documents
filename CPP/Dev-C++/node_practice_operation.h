//node_practice_operation.h

#include <stdio.h>
#include <stdlib.h>
#include "node_practice_struct.h"

node * create(INFO info);//only used to create and return a head node
int length(node * head);//include head
int inquire(node* head,int number);
node* insert(node * head,INFO info,int position);//插入到head之后的第position个位置 
node* inverse(node* head);
void delete(node* head,int position);//删除head之后的第position个节点 
void print(node *head);
void destory(node* head);
void swap(int *a,int *b);
void bubble_sort1(node* head);//soga,in my opinion...in fact,it's selection sort
void bubble_sort2(node* head);//bubble sort is j & j+1, but not i & j(selection) emmm maybe
void swap_info(INFO* a,INFO* b);
node* get_node(node* head, int pos);//return NO.pos node after head, just like a arrray
void selection_sort(node * head);//from big to small
node* insertion_sort(node* head);
void quick_sort_recursive(node* head,int start,int end);//just like a array
void quick_sort(node* head);

