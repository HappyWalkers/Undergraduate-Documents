#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

template<typename t>void print_array(t array[],int array_size){//模板，打印数组
    for(int i=0;i<array_size;i++){
        cout<<array[i]<<" ";
        if((i+1)%50==0)cout<<endl;
    }
    cout<<endl;
}

template<typename t>void my_swap(t &a,t &b){//模板，交换数据a、b
    t temp=a;
a=b;
    b=temp;
}

class ancestor
{
public:
    long cn = 0;//平均比较次数
    long mn = 0;//平均移动次数
    long tn = 0;//平均执行时间,单位：CPU时钟数
    int array_size;
    int *array;
    ancestor(int n)//初始化array,存放待用数字序列
    { 
        array_size = n;
        // array=new int[array_size];
        array = (int *)malloc(array_size * sizeof(int));//位array分配空间
        // int x[array_size];
        // array=x;
        srand((unsigned)time(NULL));//随机数种子
        for (int i = 0; i < array_size; i++)
        {
            array[i] = rand() % array_size;//用随机数序列初始化array
        }
    }
};

class seq_search : public ancestor//顺序查找
{
    public:
    seq_search(int n,int dest):ancestor(n)
    {
        clock_t start_time,end_time;
        start_time=clock();//计时程序
        int flag=0;//是否查找到的标志位
        for(int i=0;i<n;i++){//遍历查找
            cn++;
            if(array[i]==dest){//找到
                flag=1;
                // cout<<dest<<"位于序列的第"<<i+1<<"位"<<endl;
            }
        }
        end_time=clock();//停止计时
        // tn=(double)(end_time-start_time)/CLOCKS_PER_SEC;
        tn=end_time-start_time;
        if(flag==0){//没找到
            // cout<<"数字序列中没有"<<dest<<endl;
        }
    }
};

class insert_sort : public ancestor//插入排序
{
    public:
    insert_sort(int n):ancestor(n)
    {
        clock_t start_time,end_time;
        start_time=clock();//计时
        for(int i=1;i<n;i++){//遍历所有数据，看能否往前插入
            cn++;
            if(array[i]<array[i-1]){//若前一个比当前的大，就接着往前寻找，否则说明当前数据有序，不需要移动
                int temp=array[i];
                int j;
                for(j=i-1;temp<array[j] && j>=0;j--){//移动比当前所有数据大的数，向后移动一位，覆盖
                    array[j+1]=array[j];
                    cn++;//计数
                    mn++;
                    // cout<<j<<endl;
                }
                array[j+1]=temp;//最后，插入当前数据到比他略小的数据之后
            }
        }
        end_time=clock();
        tn=end_time-start_time;
    }
};

class merge_sort : public ancestor//归并排序
{
    public:
    merge_sort(int n):ancestor(n)
    {
        clock_t start_time,end_time;
        start_time=clock();//计时
        my_sort(array,array_size,0,array_size-1);//排序
        end_time=clock();
        tn=end_time-start_time;
    }
    void my_sort(int array[],int array_size,int left,int right){//array为待排序数组，left为拆开的下界，right为上界
        if(left<right){
            int mid=(int)((left+right)/2);
            my_sort(array,array_size,left,mid);//拆开上半部分
            my_sort(array,array_size,mid+1,right);//拆开下半部分
            merge(array,array_size,left,mid,right);//归并拆开的部分
        }
    }
    void merge(int array[],int array_size,int left,int mid,int right){//归并
        int i,j,k;
        int temp[right-left+1];//存放需要参加比较的数据
        for(int i=left;i<=right;i++){//从array赋值，初始化temp
            temp[i-left]=array[i];
        }
        for(i=left,j=mid+1,k=left;i<=mid && j<=right;k++){//两条数据合并，挨个比较并在一起
            if(temp[i-left]<=temp[j-left]){//i小，将i所在数据存入array
                array[k]=temp[i-left];
                i++;
            }else{//j小，将j所在数据存入array
                array[k]=temp[j-left];
                j++;
            }
            cn++;
            mn++;
        }
        while(i<=mid){//某条数据放完，将剩下的数据直接放入array
            array[k++]=temp[i-left];
            i++;
            mn++;
        }
        while(j<=right){
            array[k++]=temp[j-left];
            j++;
            mn++;
        }
    }
};

class heap_sort : public ancestor//堆排序
{
    public:
    heap_sort(int n):ancestor(n)
    {
        clock_t start_time,end_time;
        start_time=clock();//计时
        for(int i=array_size/2;i>=0;i--){
            heap_adjust(i,array_size-1);//建立一个大顶堆
        }
        swap(array[0],array[array_size-1]);//将堆顶与堆底互换
        mn=mn+3;
        for(int i=array_size-2;i>0;i--){//不断将堆顶与堆底互换，画完调整堆，使之保持大顶堆。而有序的数据都挨个沉到堆底，最终从小到大排序
            heap_adjust(0,i);
            swap(array[0],array[i]);
            mn=mn+3;
        }
        end_time=clock();
        tn=end_time-start_time;
    }
    void heap_adjust(int s,int m){//大顶堆，调整堆，从array[s...m]使保持大顶堆（假设：除了以s的位置不对，其他都是对的）
        int temp=array[s];
        mn++;
        for(int j=2*s+1;j<=m;j=j*2+1){//调整以s为顶的堆
            if(j<m && array[j]<array[j+1]){//找到更大的儿子，j为儿子的下标
                j++;
            }
            if(temp>=array[j]){//若s所在已经是最大的位置，则是大顶堆，推出循环
                break;
            }
            array[s]=array[j];//更大的向上浮动
            s=j;//使s记录已经向上浮动数据的位置
            mn++;
        }
        array[s]=temp;//s所在数据放回堆中
        mn++;
    }
};

class quick_sort : public ancestor//快速排序
{
    public:
    quick_sort(int n):ancestor(n)
    {
        clock_t start_time,end_time;
        start_time=clock();//计时
        q_sort(0,array_size-1);//排序
        end_time=clock();
        tn=end_time-start_time;
    }
    int partition(int low,int high){//分段，并且使一次排序
        int temp=array[low];//分界数，根据分界数将待排序列分成大小的两段
        mn++;
        while(low<high){//遍历，分别从左右向中间靠近，左右互换，完成一次排序
            while(low<high && array[high]>=temp){//从右边，挨个寻找比分界数小的数
                high--;
                cn++;
            }
            if(low<high){//判断是处理特殊情况
                array[low++]=array[high];//找到比分界数小的数，放大左边去
                mn++;
            }
            
            while(low<high && array[low]<=temp){//从左边，挨个寻找比分界数大的数
                low++;
                cn++;
            }
            if(low<high){
                array[high--]=array[low];//找到比分界数大的数，放到右边去（此时，右边该位置的数，已经放到左边）
                mn++;
            }
            
        }
        array[low]=temp;//将分界数放回
        mn++;
        return low;
    }
    void q_sort(int low,int high){//快排
        if(low<high){
            int mid=partition(low,high);//分段，排一次，此时，左边都是比分界数小的数，右边都是比分界数大的数
            q_sort(low,mid-1);//排列左半边的数字序列
            q_sort(mid+1,high);//排列右半边的数字序列
        }
    }
};

int main()
{
    int times_test[]={100,200,300,1000,2000,5000,10000,50000};//用来排序的数字个数，组成的集合
    int times_test_size=sizeof(times_test)/sizeof(int);
    for(int i=0;i<times_test_size;i++){//测试数据
        seq_search ss=seq_search(times_test[i],times_test[i]/2);
        insert_sort is=insert_sort(times_test[i]);
        merge_sort ms=merge_sort(times_test[i]);
        heap_sort hs=heap_sort(times_test[i]);
        quick_sort qs=quick_sort(times_test[i]);
        cout<<"-----------"<<times_test[i]<<"个数"<<"------------"<<endl;
        cout<<"方法"<<"\t\t"<<"cn"<<"\t"<<"mn"<<"\t"<<"tn"<<"\t"<<endl;
        cout<<"顺序查找"<<"\t"<<ss.cn<<"\t"<<ss.mn<<"\t"<<ss.tn<<"\t"<<endl;
        cout<<"插入排序"<<"\t"<<is.cn<<"\t"<<is.mn<<"\t"<<is.tn<<"\t"<<endl;
        cout<<"归并排序"<<"\t"<<ms.cn<<"\t"<<ms.mn<<"\t"<<ms.tn<<"\t"<<endl;
        cout<<"堆排序"<<"\t\t"<<hs.cn<<"\t"<<hs.mn<<"\t"<<hs.tn<<"\t"<<endl;
        cout<<"快速排序"<<"\t"<<qs.cn<<"\t"<<qs.mn<<"\t"<<qs.tn<<"\t"<<endl;
    }

    // ancestor a=ancestor(100);
    // print_array(a.array,a.array_size);

    // seq_search ss=seq_search(100,50);
    // print_array(ss.array,ss.array_size);
    // cout<<"执行时间(单位：CPU时钟数)"<<ss.tn<<endl;

    // insert_sort is=insert_sort(100);
    // print_array(is.array,is.array_size);
    // cout<<"执行时间(单位：CPU时钟数)"<<is.tn<<endl;

    // merge_sort ms=merge_sort(100);
    // print_array(ms.array,ms.array_size);
    // cout<<"执行时间(单位：CPU时钟数)"<<ms.tn<<endl;

    // heap_sort hs=heap_sort(100);
    // print_array(hs.array,hs.array_size);
    // cout<<"执行时间(单位：CPU时钟数)"<<hs.tn<<endl;

    // quick_sort qs=quick_sort(100);
    // print_array(qs.array,qs.array_size);
    // cout<<"执行时间(单位：CPU时钟数)"<<qs.tn<<endl;
    return 0;
}