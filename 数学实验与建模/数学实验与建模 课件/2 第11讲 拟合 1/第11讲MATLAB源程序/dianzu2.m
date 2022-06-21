t=[20.5 32.5 51 73 95.7];
r=[765 826 873 942 1032];                  
R=[t' ones(5,1)];
aa=R\r';
a=aa(1)
b=aa(2)
y=polyval(aa,t);
plot(t,r,'k+',t,y,'r')

