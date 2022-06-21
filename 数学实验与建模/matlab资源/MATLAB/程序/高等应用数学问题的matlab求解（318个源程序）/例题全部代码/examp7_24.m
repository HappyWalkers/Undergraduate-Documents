[t,y]=shooting('c7fun1','c7fun2',[0,1],[1;2]); plot(t,y)

y0=((exp(2)-3)*exp(t)+(3-exp(1))*exp(2*t))/(4*exp(1)*(exp(1)-1))+3/4+t/2;
norm(y(:,1)-y0)  % 整个解函数检验

norm(y(end,1)-2) % 终点条件检验
