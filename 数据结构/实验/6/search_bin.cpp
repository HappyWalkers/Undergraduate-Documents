#include<iostream>
using namespace std;

typedef int KeyType;//数据类型
typedef struct{
    KeyType key;
}ElemType,TElemType;//数组中数据类型
typedef struct{
    ElemType *elem;//数组
    int length;//数组中元素个数
}SSTable;//存放二分查找的数据类型
int search_bin(SSTable ST,KeyType kval){//二分查找
    int low=0;
    int high=ST.length;
    while(low<=high){//不断二分
        int mid=(low+high)/2;
        if(kval==ST.elem[mid].key){//找到返回位置
            return mid;
        }else if(kval<ST.elem[mid].key){//没找到缩小范围继续寻找
            high=mid-1;
        }else{
            low=mid+1;
        }
    }
    return -1;
}
int main(){//测试
    SSTable ST;
    int length;
    int kval;
    cout<<"输入将要输入的数字个数"<<endl;//输入数据，初始化要查找的数组
    cin>>length;
    ST.length=length;
    ST.elem=(ElemType*)malloc(length*sizeof(ElemType));
    cout<<"输入数字序列"<<endl;
    for(int i=0;i<length;i++){
        cin>>ST.elem[i].key;
    }
    cout<<"输入要查找的数字"<<endl;
    cin>>kval;
    if(search_bin(ST,kval)!=-1){
        cout<<"要查找的数字位于第"<<search_bin(ST,kval)+1<<"个"<<endl;
    }else{
        cout<<"要查找的数字不存在"<<endl;
    }
    return 0;
}