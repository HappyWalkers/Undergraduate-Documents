syms n; s=symsum(1/((3*n-2)*(3*n+1)),n,1,inf)

m=1:10000000; s1=sum(1./((3*m-2).*(3*m+1)));
format long; s1 % �Գ��ͷ�ʽ��ʾ�ó��Ľ��
