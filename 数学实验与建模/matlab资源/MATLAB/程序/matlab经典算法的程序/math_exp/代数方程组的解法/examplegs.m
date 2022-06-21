clear;
a=[1 0 3 0;0 2 1 2;3 1 15 0;0 2 0 4];
b=[1 6 5 8]';
n=4;
u=zeros(n,1);
[X,K]=gausei(a,b,n,u);
disp('方程组的解:');
X
disp('迭代的次数：')
K
<i