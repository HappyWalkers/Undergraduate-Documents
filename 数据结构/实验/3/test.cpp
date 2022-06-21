#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <cstring>
#include <string>
#include <iomanip>
#include <cstdio>
using namespace std;

#define failure -1;
#define success 0;
int row_count_block1 = 0;
int row_count_block2 = 0;
int row_count_block3 = 0;

class const_varible//各路常量
{
public:
    static const int active_max_len = 100;//活区最大行块数，注意：是行块，不是行。
    static const int active_readin_len = 80;//初始化时读入的行块数，留一点空间方便用户插入
    static const int line_len_array = 81;//行块长度
    static const int line_num_array = 4;
    static const int delete_index_flag = 0;

    // static const char line_end_flag = 12; //ascII码为12的字符，为非打印字符，用作行结束标志（没用到）
};

class file_operation//对文件操作的函数集合
{
private:
    const string test_file_path = "./notepad_test_source.txt";//测试文件路径，按需修改即可

public:
    char active_area_str[const_varible::active_max_len][const_varible::line_len_array]; //活区，存字符串（100行，81列）
    int active_area_index[const_varible::active_max_len];                               //下标对应的活区行块所在行号（size=100)
    /*
    以上这两个数组的关系使这样的
    比如
    1（行） str................................
    2（行） str................................................................
    2（行） str.............................................
    3（行） str................................................
    其中第二行超过80个字符，所以占两个行块active_area_str，相应的，其行号也用了两个active_area_index
    */

    int count = 0;//活区数组尾部标志，记录活区当前尾部,注意：插入仅在活区尾部进行（由于有行号标注，所以不会乱掉）

    file_operation()//构造函数，初始化为数组置0
    {
        memset(active_area_index, 0, sizeof(active_area_index));
        memset(active_area_str, 0, sizeof(active_area_str));
    }
    //打开文件
    
    
    int read_text(int temp) //从文件读80行块到活区
    {
        count = 0;
        ifstream in_file;
        in_file.open(test_file_path, ios::in);
        if (!in_file)//未成功打开抛出提示，返回
        {
            cout << "文件打开失败" << endl;
            return failure;
        }
        for (int i = 0; i < temp; i++) {
            string s;
            getline(in_file, s);
        }
        //从文件读取前80个行块（若需要打开其他行块，略作修改即可）
        string s;//暂存读入的行的字符串
        int row = 0; //记录行号
        while (getline(in_file, s))//只要不为空，就一直读取
        {
            row_count_block2++;
            if (s.length() < const_varible::line_len_array)//如果读入的行大小小于81，直接存入行块，并设置行号
            {
                str_to_char_array(s, active_area_str[count]);//将s存入活区数组
                row++;//行加一
                
                active_area_index[count] = row;//设置下标
                count++;//当前活区数组尾部标志往后移动
            }
            else//若读入的行大小超过81，则分割存入行块，并设置行号
            {
                row++;
                
                for (int i = 0; i < ceil((double)s.length() / const_varible::line_len_array); i++)//分成几块
                {
                    // active_area_str[count]=s.substr(i*(const_varible::line_len_array-1),const_varible::line_len_array-1);
                    str_to_char_array(s.substr(i * (const_varible::line_len_array - 1), const_varible::line_len_array - 1), active_area_str[count]);//按顺序把从s分出来的块存入活区
                    active_area_index[count] = row;
                    count++;
                }
            }
            if (count == const_varible::active_readin_len)//当前活区数组尾部标志等于80，即已经读入80个行块，退出循环
            {
                break;
                in_file.close();//关闭文件
            }
        }

        
        return success;
    }

    void str_to_char_array(string s, char c[])//将字符串s存入字符数组c
    {
        for (int i = 0; i < s.length(); i++)
        {
            c[i] = s[i];
        }
    }
    int ip = 0;
    void print_active_area_str()//打印当前活区数组
    {
        if (count >= 80) {
            for (int i = 0; i < count; i++)
            {
                //cout << active_area_index[i] << " " << active_area_str[i] << endl;
                cout << setw(4) << setfill('0') << active_area_index[i] << ':' << ' ' << active_area_str[i] << endl;
            }
            cout << endl;
        }
        else {
            if (ip == 0) {
                ip = 1;
                for (int i = 0; i < count; i++)
                {
                    //cout << active_area_index[i] << " " << active_area_str[i] << endl;
                    cout << setw(4) << setfill('0') << active_area_index[i] << ':' << ' ' << active_area_str[i] << endl;
                }
            }
            cout << "已结束"<<endl;
        }
          
    }

    void check_count()//检查当前活区数组尾部是否大于100，若是则说明溢出
    {
        if (count >= 100)
        {
            cout << "活区溢出" << endl;
            exit(-1);
        }
    }
};

class active_operation//对活区操作的函数集合
{
public:
    file_operation f;//为了从file_operation弄到活区数组
    active_operation()//初始化
    {
        total_row();
        f.read_text(0);
    }

    void insert_easy(int row, string s)//简化接口，调用即可
    {
        //查看要插入的行是否符合条件
        if (row<min(f.active_area_index) || row == 0 || row>max(f.active_area_index))
        {
            cout << "不在活区行号范围内" << endl;
            return;
        }
        insert_row(row, s);//插入到活区数组尾部
        clear_active_area();//使紧凑
        sort();//排序
    }

    void delete_easy(int row)//简化接口，调用即可
    {
        if (row<min(f.active_area_index) || row>max(f.active_area_index))
        {
            cout << "不在活区行号范围内" << endl;
            return;
        }
        delete_row(row);
        clear_active_area();
        sort();
    }

    void delete_easy(int start_row, int end_row)//简化接口，调用即可
    {
        if (start_row<min(f.active_area_index) || end_row>max(f.active_area_index))
        {
            cout << "不在活区行号范围内" << endl;
            return;
        }
        delete_row(start_row, end_row);
        clear_active_area();
        sort();
    }

    int max(int a[])//返回一个int[]中最大值
    {
        int max = 0;
        for (int i = 0; i < const_varible::active_max_len; i++)
        {
            if (a[i] > max)
            {
                max = a[i];
            }
        }
        return max;
    }

    int min(int a[])//返回一个int[]中最小值
    {
        int min = a[0];
        for (int i = 0; i < const_varible::active_max_len; i++)
        {
            if (a[i] < min)
            {
                min = a[i];
            }
        }
        return min;
    }

    void insert_row(int row, string s) //s为要插入的行，插入到row行之后（仅放入活区数组尾部，设置行号）
    {
        if (s.length() < const_varible::line_len_array)//若要插入的行长度小于81，直接放入活区数组
        {
            f.str_to_char_array(s, f.active_area_str[f.count]);//放入活区数组的尾部
            f.active_area_index[f.count] = row + 1;//设置行号
            f.count++;//活区数组尾部标志加一
        }
        else//若大于，则分割后放入活区数组
        {
            for (int i = 0; i < ceil((double)s.length() / const_varible::line_len_array); i++)
            {
                // active_area_str[count]=s.substr(i*(const_varible::line_len_array-1),const_varible::line_len_array-1);
                f.str_to_char_array(s.substr(i * (const_varible::line_len_array - 1), const_varible::line_len_array - 1), f.active_area_str[f.count]);
                f.active_area_index[f.count] = row + 1;
                f.count++;
            }
        }
        f.check_count();//检查下是否溢出

        // f.print_active_area_str();//查看
    }

    void delete_row(int row) //删除某行(仅将其行号置-1)
    {
        for (int i = 0; i < f.count; i++)//遍历寻找要删除的行
        {
            if (f.active_area_index[i] == row)//找到要删除的行号
            {
                f.active_area_index[i] = const_varible::delete_index_flag; //行号置-1
            }
            else if (f.active_area_index[i] > row)//要删除之后的行号需要减一
            {
                f.active_area_index[i] -= 1;
            }
        }

        // f.print_active_area_str();
    }

    void delete_row(int row_start, int row_end) //删除从row_start到row_end的行，包括两端（思路同其同名函数）
    {
        for (int i = 0; i < f.count; i++)
        {
            if (f.active_area_index[i] >= row_start && f.active_area_index[i] <= row_end)//要删除的行号
            {
                f.active_area_index[i] = const_varible::delete_index_flag;
            }
            else if (f.active_area_index[i] > row_end)//要删除之后的行号
            {
                f.active_area_index[i] -= row_end - row_start + 1;
            }
        }

        // f.print_active_area_str();
    }

    void clear_active_area() //在进行删除操作之后，活区中有无效区域，将有效区域填补到无效区域，使活区紧凑
    {
        for (int i = 0; i < const_varible::active_max_len; i++)
        {
            //从上往下遍历，寻找空位置
            if (f.active_area_index[i] == const_varible::delete_index_flag)
            {
                //找到空位置，从后往前寻找，找到有效区域，填补进内
                for (int j = const_varible::active_max_len - 1; j > 0; j--)
                {
                    if (j <= i)//从后往前没找到时，说明已经填补完成，退出
                    {
                        // f.print_active_area_str();//查看填补效果
                        f.count = i;
                        return;
                    }
                    if (f.active_area_index[j] != const_varible::delete_index_flag)
                    {
                        //找到有效区域，将其行号拷到无效区域，再将其行块拷到无效区域，最后将已经复制完成的有效行块的行号置-1
                        f.active_area_index[i] = f.active_area_index[j];
                        // f.active_area_str[i]=f.active_area_str[j];
                        strcpy(f.active_area_str[i], f.active_area_str[j]);
                        f.active_area_index[j] = const_varible::delete_index_flag;//已搬移的置为无效
                        break;
                    }
                }
            }
        }
    }

    void sort()//对活区排序，以行号为引，按顺序排列
    {
        for (int i = 0; i < const_varible::active_max_len; i++)//选择排序
        {
            for (int j = i; j < const_varible::active_max_len; j++)
            {
                if (f.active_area_index[i] > f.active_area_index[j] && f.active_area_index[j] != const_varible::delete_index_flag)//忽略无效区域
                {
                    swap(f.active_area_index[i], f.active_area_index[j]);//交换
                    swap(f.active_area_str[i], f.active_area_str[j]);
                }
            }
        }

        f.print_active_area_str();//查看
    }

    void swap(int& a, int& b)//交换两个int
    {
        int temp = a;
        a = b;
        b = temp;
    }

    void swap(char a[], char b[])//交换两个char[]
    {
        char temp[const_varible::line_len_array];
        strcpy(temp, a);
        strcpy(a, b);
        strcpy(b, temp);
    }
    ///////////////////////////////////
    void store_active_context() {
        ofstream write_file("C:\\Users\\刘润\\Desktop\\temp.txt", ios::out);
        ifstream read_file("C:\\Users\\刘润\\Desktop\\notepad_test_source.txt", ios::in);
        for (int i = 0; i < row_count_block1; i++) {
            string temp;
            getline(read_file, temp);
            write_file << temp;
            write_file << '\n';
        }
        for (int i = 0; i < f.count; i++) {
            write_file << f.active_area_str[i];
            write_file << '\n';
        }
        string s;
        for (int i = 0; i < row_count_block2; i++) {
            getline(read_file, s);
        }
        for (int i = 0; i < row_count_block3; i++) {
            string temp;
            getline(read_file, temp);
            write_file << temp;
            write_file << '\n';
        }
        write_file.close();
        read_file.close();
    }

    void active_area_switch_row_count() {
        row_count_block1 += row_count_block2;
        row_count_block2 = 0;
        f.read_text(row_count_block1);
        row_count_block3 = row_count_block3 - row_count_block2 - row_count_block1;
    }
 
    void total_row() {
        string s;
        ifstream read_file("C:\\Users\\刘润\\Desktop\\notepad_test_source.txt", ios::in);
        while (getline(read_file, s))
        {
            row_count_block3++;
        }
        read_file.close();
    }

    void n_option() {
        store_active_context();
        active_area_switch_row_count();
        f.read_text(row_count_block1);
    }

    void p_option(int &start) {
        for (int i = 0; i < 20; i++) {
            if (start + i < row_count_block2) {
                cout << setw(2) << setfill('0') << i << ':' << f.active_area_str[i+start] << endl;
            }
            else {
                start = 0;
                break;
            }
            
        }
        
    }
};
int main()//测试
{
    active_operation a;
    char option;
    a.f.print_active_area_str();
    int start = 0;
    while (cin >> option) {
        if (option == 'n') {
            a.n_option();
            cout << "已切换活区" << endl;
        }
        if (option == 'p') {
            a.p_option(start);
            start += 20;
        }
        if (option == 'd') {         
            string s;
            cin >> s;
            int num1 = 0, num2 = 0;
            int cp1 = 0;
            for (int i = 0; i < s.length(); i++) {
                if (s[i] < '9' && s[i]>'0'&&cp1==0) {
                    num1 = num1*10 + s[i] - '0';
                }
                if (s[i] == '\0' || s[i] == '\t') {
                    cp1 = 1;
                }
                if (s[i] < '9' && s[i]>'0' && cp1 == 1) {
                    num2 = num2*10 + s[i] - '0';
                }
            }
            if (num2 != 0) {
                a.delete_easy(num1, num2);
            }
            else{
                a.delete_easy(num1);
            }
            
        }
        if (option == 'i') {
            int num;
            cin >> num;
            string s;
            cin >> s;
            a.insert_easy(num, s);
        }
    }
    return 0;
}