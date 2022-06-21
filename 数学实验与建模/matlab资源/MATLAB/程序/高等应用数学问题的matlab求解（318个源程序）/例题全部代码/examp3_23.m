syms n; s=symsum(1/((3*n-2)*(3*n+1)),n,1,inf)

m=1:10000000; s1=sum(1./((3*m-2).*(3*m+1)));
format long; s1 % 以长型方式显示得出的结果
