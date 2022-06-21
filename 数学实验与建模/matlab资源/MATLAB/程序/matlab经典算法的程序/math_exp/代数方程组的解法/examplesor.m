clear;
a=[4 -2 -4;-2 17 10;-4 10 9];
b=[10 3 -7]';
n=3;
u=zeros(n,1);
w=1;
[X1,K1]=sor(a,b,n,u,w);
disp('超松弛系数:')
w
disp('方程组的解:');
X1
disp('迭代的次数：')
K1
w=1.46;
[X2,K2]=sor(a,b,n,u,w);
disp('超松弛系数:')
w
disp('方程组的解:');
X2
disp('迭代的次数：')
K2

<i