n=3;
u=[0 0 0]';
disp('初始值x=[0 0 0]的结果：');
[X,k]=newton(u,n);
X
k

u=[8 8 8]';
disp('初始值x=[8 8 8]的结果：');
[X,k]=newton(u,n);
X
k<i