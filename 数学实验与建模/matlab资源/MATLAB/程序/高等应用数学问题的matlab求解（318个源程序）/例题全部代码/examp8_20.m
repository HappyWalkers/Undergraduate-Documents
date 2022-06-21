syms x; fun='sin(x)*exp(-x)/(x+1)^3';  % fun 应该为字符串
maple('with(numtheory):'); f=maple(['cfe:=cfrac(' fun ',x,10)'])

n=collect(maple('nthnumer','cfe',8),x);  % 分子多项式合并同类项
d=collect(maple('nthdenom','cfe',8),x); [n,d]=numden(n/d); G=n/d; latex(G)
n=collect(maple('nthnumer','cfe',10),x);
d=collect(maple('nthdenom','cfe',10),x);
[n,d]=numden(n/d); G1=n/d; latex(G1) % 显示从略

ezplot(fun,[0,2]), hold on; ezplot(G,[0,2]); ezplot(G1,[0,2])
figure;  ezplot(fun,[0,5]), hold on; ezplot(G,[0,5]); ezplot(G1,[0,5])
