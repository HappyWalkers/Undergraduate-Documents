#include<stdio.h>
#include<stdlib.h>
#define maxsize 10
typedef int ElemType;
typedef struct{
    ElemType* base;
    ElemType top;//下标
}stack;
stack* Init(){//初始化函数
    stack* s;
    s->base=(ElemType*)malloc(maxsize*sizeof(ElemType));//申请空间
    if(s==NULL){
        printf("malloc fail in Init");
        return NULL;
    }
    s->top=0;
    return s;
}
void push(stack* s,ElemType e){//压栈
    if(s->top==maxsize){//溢出
        printf("stack is overflow");
        return;
    }
    *(s->base+s->top)=e;//压入
    s->top++;//栈顶上移
}
int pop(stack* s){//出栈
    if(s->top==0){//空栈
        printf("stack is underflow");
        return 0;
    }
    s->top--;//栈顶下移
    return *(s->base+s->top);//返回移出的值
}
int getTop(stack* s){//取栈顶，而不动栈顶指针
    if(s->top==0){//空栈
        printf("stack is underflow");
        return 0;
    }
    return *(s->base+s->top-1);
}
void print(stack* s){//从栈顶到栈底打印栈
    printf("stack:\n");
    for(int i=s->top-1;i>=0;i--){
        printf("%d\n",*(s->base+i));
    }
}
int main(){
    stack* s=(stack*)malloc(sizeof(stack));//产生一个栈
    s->base=(ElemType*)malloc(maxsize*sizeof(ElemType));
    if(s==NULL){
        printf("malloc fail in main");
        return 0;
    }
    s->top=0;//栈顶指针初始为0，该指针仅代表数组的下标
    push(s,1);
    push(s,2);
    push(s,3);
    print(s);
    printf("pop:%d\n",pop(s));
    print(s);
    printf("getTop:%d\n",getTop(s));
    return 0;
}