#include<iostream>
#include<fstream>
#include<string>
#include<io.h>
using namespace std;

typedef struct{
    int chinese;
    int math;
    int english;
}score;//存放分数信息

typedef struct{
    string ID;
    string name;
    score ss;
}student_info;//存放学生信息

template<typename t>void my_swap(t &a,t &b){//交换数据，a、b
    t temp=a;
    a=b;
    b=temp;
}

void sort(student_info* si,int student_num){//根据总分排序学生
    int sum[student_num];
    for(int i=0;i<student_num;i++){//求出总分
        sum[i]=si[i].ss.chinese+si[i].ss.math+si[i].ss.english;
    }
    for(int i=0;i<student_num;i++){//选择排序
        for(int j=i;j<student_num;j++){
            if(sum[i]<sum[j]){
                my_swap(si[i],si[j]);
                my_swap(sum[i],sum[j]);
            }
        }
    }
    int temp_score=sum[0];
    int rank=1;
    cout<<"total\t"<<"rank\t"<<"ID\t"<<"name\t"<<"chinese\t"<<"math\t"<<"english\t"<<endl;//输出排好的学生数组
    for(int i=0;i<student_num;i++){
        if(sum[i]!=temp_score){
            temp_score=sum[i];
            rank++;
        }
        cout<<sum[i]<<"\t"<<rank<<"\t"<<si[i].ID<<"\t"<<si[i].name<<"\t"<<si[i].ss.chinese<<"\t"<<si[i].ss.math<<"\t"<<si[i].ss.english<<"\t"<<endl;
    }
}

int main(){
    ifstream infile;//打开文件
    infile.open("./student_info.txt",ios::in);
    student_info si[10];//假定不超过10个学生
    int index=0;
    while(!infile.eof()){//从文件读入学生信息
        infile>>si[index].ID;
        infile>>si[index].name;
        infile>>si[index].ss.chinese;
        infile>>si[index].ss.math;
        infile>>si[index].ss.english;
        index++;
    }
    sort(si,index);//排序展示
    return 0;
}