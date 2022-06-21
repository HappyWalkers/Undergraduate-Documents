a=[1 2 4 1 7;2 3 0 1 8;4 1 7 6 1;1 1 0 2 1;1 3 0 1 1]
b=[15 14 19 5 6]'
r=[a,b]
n=5;
[A,x]=gauss(r,n);
disp('the solution of the equations:');
A
x<i