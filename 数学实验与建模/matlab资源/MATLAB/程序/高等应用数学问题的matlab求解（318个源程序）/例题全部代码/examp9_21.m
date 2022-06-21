f=inline('a(1)*exp(-a(2)*x)+a(3)*exp(-a(4)*x).*sin(a(5)*x)','a','x');
x=0:0.1:10; y=f([0.12,0.213,0.54,0.17,1.23],x);
[a,r,j]=nlinfit(x,y,f,[1;1;1;1;1]); a

ci=nlparci(a,r,j)

y=f([0.12,0.213,0.54,0.17,1.23],x)+0.02*rand(size(x));
[a,r,j]=nlinfit(x,y,f,[1;1;1;1;1]); a

ci=nlparci(a,r,j)
