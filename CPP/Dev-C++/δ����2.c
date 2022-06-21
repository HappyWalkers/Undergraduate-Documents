#include<stdio.h>
#include<stdlib.h>
#define queuesize (5+2+1)
typedef int ElemType;
typedef struct sqqueue{
    ElemType sq[queuesize];
    int front;
    int rear;
}que;
void en_cycque(que* q,ElemType x ){
    int i=(q->rear+1)%queuesize;
    if(i==q->front){
        printf("overflow in en_cycque\n");
        return;
    }
    q->sq[q->rear]=x;
    q->rear=i;
}
void dl_cycque(que* q,ElemType* x){
    if(q->front==q->rear){
        printf("empty in dl_cycque\n");
        return;
    }
    *x=q->sq[q->front];
    q->front=(q->front+1)%queuesize;
}
void get_head(que* q,ElemType* x){
    if(q->front==q->rear){
        printf("empty in dl_cycque\n");
        return;
    }
    *x=q->sq[q->front];
}
int isempty(que q){
    if(q.front==q.rear)return 1;
    else return 0;
}
void yanghui(){
    que q={NULL,0,0};
    for(int i=1;i<=queuesize-3;i++)printf(" ");
    printf("%d\n",1);
    en_cycque(&q,0);
    en_cycque(&q,1);
    en_cycque(&q,1);
    int k=1;
    ElemType s,e;
    while(k<queuesize-3){
        for(int i=1;i<=queuesize-3-k;i++){
            printf(" ");
        }
        en_cycque(&q,0);
        do{
            dl_cycque(&q,&s);
            get_head(&q,&e);
            if(e!=0)printf("%d ",e);
            else printf("\n");
//            printf("hhh\n");
            en_cycque(&q,s+e);
        }while(e!=0);
        k++;
//        printf("hhh");
    }
//    en_cycque(&q,0);
    dl_cycque(&q,&e);
    while(isempty==0){
        dl_cycque(&q,&e);
        printf("%d",e);
    }
}
void main(){
    yanghui();
}
