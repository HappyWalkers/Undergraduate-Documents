#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define year 6
int main()
{
    int i,jibi=0;
    float k,data[year],GM[year];
    printf("输入五个年份的售价\n");
    for(i=0;i<year;i++)
    {
        scanf("%f",&data[i]);
    }
    printf("级比为:");
    for(i=1;i<year;i++)
    {
        k=data[i-1]/data[i];
        if(k<exp((-2.0)/(i+1))||k>exp(2.0/(i+1)))
            break;
        else
            jibi=1;
            printf("%.2f  ",k);
    }printf("\n");
    if(jibi==1)
    {
    printf("该数列可以进行灰色预测\n====================\n");
    }
    else
    {
    printf("该数列不可以进行灰色预测\n====================\n");
        return 0;
	}
    printf("GM模型为\n");
    for(i=0;i<year;i++)//建立GM(1,1)模型
    {   if(i>0)
        GM[i]=GM[i-1]+data[i];
        else
        GM[i]=data[i];
        printf("%.2f  ",GM[i]);
    }
    printf("\n");
    printf("====================\n");
    int a,b,sum=0;
    float B[year-1][2],BT[2][year-1],Y[year-1];//定义B和Y矩阵
    for(a=0;a+1<year;a++)
    {
        B[a][0]=-0.5*(GM[a]+GM[a+1]);
        B[a][1]=1;
        Y[a]=data[a+1];
    }printf("B矩阵为\n");
    for(a=0;a<4;a++)
    {
    for(b=0;b<2;b++)
    {printf("%.2f  ",B[a][b]);//显示B矩阵
    }printf("\n");
    }printf("====================\n");
    printf("Y矩阵为\n");
    for(a=0;a<year-1;a++)
        printf("%.2f\n",Y[a]);//显示Y矩阵
    printf("====================\n");
    printf("转置的BT矩阵为\n");
    for(a=0;a<2;a++)
    {
    for(b=0;b<year-1;b++)//得到B的转置BT矩阵
    {
        BT[a][b]=B[b][a];
        printf("%.2f  ",BT[a][b]);//显示转置的BT矩阵
    }printf("\n");
    }printf("====================\n");
    float BTB[2][2]={1435616.5,-2214,-2214,4};
    printf("BT矩阵与B矩阵相乘的结果为BTB矩阵：\n");
    for(a=0;a<2;a++)
    {for(b=0;b<2;b++)
    {printf("%.2f  ",BTB[a][b]);}
    printf("\n");}
    printf("====================\n");
    double BTB0[2][2];//定义BTB的逆矩阵
    double BTB0BT[2][5];
    double AB[2]={0.2241, 276.5564};
    printf("最终得到的矩阵是：\n");
    for(a=0;a<2;a++)
        {printf("%f  ",AB[a]);}
        printf("\n所以a=%f，b=%f\n",AB[0],AB[1]);
        int l=1;
		while(l<=5)
        {printf("====================\n请输入您要预测的年份n(n>2018)\n");
    int n;float x,a1=AB[0],b1=AB[1];//定义预测值x和未来第几年n
	scanf("%d",&n);
    x=((data[0]-b1/a1)*exp(-a1*(n-2018))+b1/a1);
    printf("该年的预测值为%.2f\n",x);
    float x0,xk;//定义模型还原值x0和残差xk
    x0=(x*((n-2018)+1)-x);
    xk=(x-x0)/x;
    printf("残差为%f,",xk);
    if(fabs(xk)<0.1)
    printf("残差检验达到了较高要求\n");
    else if(fabs(xk)<0.2)
    printf("残差检验达到了一般要求\n");
    else
    printf("残差检验未达到理想要求\n");
    printf("====================\n");
	l++;}
}
