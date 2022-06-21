#include<stdio.h>
#include<stdlib.h>
#define maxsize 10
typedef int ElemType;
typedef struct{
    ElemType* base;
    ElemType top;//下标
}stack;
void push(stack* s,ElemType e){//压栈
    if(s->top==maxsize){//溢出
        printf("stack is overflow");
        return;
    }
    *(s->base+s->top)=e;//压入
    s->top++;//栈顶上移
}
void print(stack* s){//从栈顶到栈底打印栈
    for(int i=s->top-1;i>=0;i--){
        printf("%d",*(s->base+i));
    }
}
int main(){
    //产生一个栈
    stack* s=(stack*)malloc(sizeof(stack));//产生一个栈
    s->base=(ElemType*)malloc(maxsize*sizeof(ElemType));
    if(s==NULL){
        printf("malloc fail in main");
        return 0;
    }
    s->top=0;//栈顶指针初始为0，该指针仅代表数组的下标
    //转换数制
    int d=8;//要转化为的数制
    int dest=1348;//目标数
    int cout=dest;//记录，用于输出
    int remainder=0;//余数
    while(1){
        remainder=dest%d;//取余，压到栈中
        push(s,remainder);
        dest=dest/d;
        if(dest==0){
            break;
        }
    }
    printf("十进制数%d转化为八进制数后为：",cout);
    print(s);
}