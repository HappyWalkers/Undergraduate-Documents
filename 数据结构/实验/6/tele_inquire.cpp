#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

typedef struct
{
    string name;
    string phoneNumber;
    string mobileNumber;
    string email;
} Tele;//存放信息的结构体
const int Tele_size_max = 10;
Tele t[Tele_size_max];//Tele数组
int Tele_size = 0;

void store_tele_to_file(Tele t[])//将Tele[]存入文件
{ 
    ofstream outfile;
    outfile.open("./Tele_info.txt", ios::out);//打开文件
    for (int i = 0; i < Tele_size; i++)//向文件写入数据
    {
        outfile << t[i].name << " " << t[i].phoneNumber << " " << t[i].mobileNumber << " " << t[i].email << endl;
    }
    outfile.close();//关闭文件
    cout<<"写入成功"<<endl;
}

void extract_tele_from_file(Tele t[])//从文件中提取Tele
{ 
    ifstream infile;
    infile.open("./Tele_info.txt", ios::in);//打开文件
    while(!infile.eof()){//从文件中读出数据
        infile >> t[Tele_size].name >> t[Tele_size].phoneNumber >> t[Tele_size].mobileNumber >> t[Tele_size].email;
        Tele_size++;
    }
    infile.close();//关闭文件
    cout<<"导入成功"<<endl;
}

int inquire_tele_index(Tele t[], string name)//从Tele[]中根据姓名查询Tele所在下标，返回位置
{ 
    for (int i = 0; i < Tele_size; i++)
    {
        if (name.compare(t[i].name) == 0)
        {
            return i;
        }
    }
    cout << "fail to find " << name << endl;
    return -1;//查找失败返回-1
}

Tele inquire_tele(Tele t[], string name)//从Tele[]中根据姓名查询Tele，返回查到的结构体
{ 
    return t[inquire_tele_index(t, name)];
}

void insert_tele(Tele t[], Tele temp) //将temp插入Tele[]中
{
    t[Tele_size++] = temp;
}

void delete_tele(Tele t[], string name)//从Tele[]中根据姓名删除对应Tele
{ 
    for(int i=inquire_tele_index(t,name)+1;i<=Tele_size;i++){//后面前挪覆盖
        t[i-1]=t[i];
    }
    // memset(&t[Tele_size-1], 0, sizeof(Tele));
    Tele_size--;
}

void modi_tele(Tele t[], int choice, string name, string info)
{ //根据choice和提供的name选择性修改Tele中的某项内容,choice:1、name 2、phoneNumber 3、mobileNumber 4、email
    switch (choice)//根据choice选择功能
    {
    case 1:
        t[inquire_tele_index(t, name)].name = info;
        break;
    case 2:
        t[inquire_tele_index(t, name)].phoneNumber = info;
        break;
    case 3:
        t[inquire_tele_index(t, name)].mobileNumber = info;
        break;
    case 4:
        t[inquire_tele_index(t, name)].email = info;
        break;
    default:
        cout << "illegal choice" << endl;
        break;
    }
}

void print_tele(Tele t)//打印结构体
{
    cout << t.name << " " << t.phoneNumber << " " << t.mobileNumber << " " << t.email << endl;
}

void print_teles(Tele t[])//打印结构体数组
{
    cout<<"Tele数组中的内容为："<<endl;
    for (int i = 0; i < Tele_size; i++)//遍历
    {
        print_tele(t[i]);
    }
}

int main()//测试
{
    //插入
    Tele temp1={"小刚","111","222","333"};
    insert_tele(t,temp1);
    print_teles(t);
    Tele temp2={"小明","444","555","666"};
    insert_tele(t,temp2);
    print_teles(t);
    //查询
    cout<<"以"<<temp1.name<<"为名的查询结果为："<<endl;
    print_tele(inquire_tele(t,temp1.name));
    //删除
    cout<<"删除后还剩："<<endl;
    delete_tele(t,temp1.name);
    print_teles(t);
    //修改
    cout<<"修改结果："<<endl;
    modi_tele(t,4,temp2.name,"777");
    print_teles(t);
    //存入文件
    store_tele_to_file(t);
    cout<<"删除后还剩："<<endl;
    delete_tele(t,temp2.name);
    print_teles(t);
    //从文件读出
    extract_tele_from_file(t);
    print_teles(t);
    return 0;
}