clear
close all
clc

% 计算1
syms t
diff(sin(t^2))

% 计算2
syms t
diff(t^6,'t',5)

% 计算3
syms x
f = 1/x^2;
int(f)

% 计算4
syms x
f = sqrt(x^2+3);
int(f, x, -1, 1)

% 计算5
f = @(x,y) exp(-x.^2/3).*sin(x.^2+2*y);
I = integral2(f, -1, 1, -1, 1)

% 计算6
f = @(x,y,z) y.*sin(x)+z.*cos(x);
Q = integral3(f,0,pi,0,1,-1,1)

% 计算7
syms y(x) x
eqn = diff(y,x,2)+2*diff(y,x)+exp(x)==0;
ySol(x) = dsolve(eqn)

% 计算8
syms y(x) x
eqn = x*diff(y,x)+2*y==exp(x);
cond = y(1)==2*exp(1);
ySol(x) = dsolve(eqn,cond)

ySol2(x) = dsolve('x*Dy+2*y-exp(x)=0','y(1)=2*exp(1)','x') 

% 计算9 代码1
syms x(t) t
eqn = diff(x,t,2)-1000*(1-x^2)*diff(x,t)-x==0;
Dx = diff(x,t);
cond = [x(0)==2, Dx(0)==0];
xSol(t) = dsolve(eqn,cond)

% 计算9 代码2
xSol2(t) = dsolve('D2x-1000*(1-x^2)*Dx-x','x(0)=2','Dx(0)=0','t')

% 计算9 代码3
[t,y] = ode15s(@fvdp1000,[0 3000],[2 0]);

figure;
plot(t,y(:,1),'-o')
xlabel('t');
ylabel('x');
title('高阶常微分方程数值解例子');













