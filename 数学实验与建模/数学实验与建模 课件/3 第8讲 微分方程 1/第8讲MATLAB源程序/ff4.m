clear all
close all
clc

syms y(x)
eqn = diff(y,x,2) + 4 * diff(y,x) + 29 * y == 0;
Dy = diff(y, x);
con = [y(0) == 0, Dy(0) == 15];
yRes(x) = dsolve(eqn, con)
yRes(x) = dsolve(eqn)

syms x(t)
eqn = diff(x,t,2) - 1000*(1-x^2)*diff(x,t,1) - x == 0;
Dx = diff(x, t, 1);
con = [x(0)==2, Dx(0)==0];
xSol(t) = dsolve(eqn, con)

tic
[T,Y]=ode15s('vdp1000',[0 3000],[2 0]);
t1 = toc
a = 1000;
[T1,Y1]=ode23(@(t,y)vdpMod(t,y,a),[0 3000],[2 0]);
t2 = toc;
delta = t2 - t1

tic
[T,Y]=ode45('vdp1000',[0 3000],[2 0]);
toc

a = 1000;
[T1,Y1]=ode23(@(t,y)vdpMod(t,y,a),[0 3000],[2 0]);


figure;
plot(T,Y(:,1),'k-')
hold on;
plot(T1,Y1(:,1),'r:')
xlabel('t');
ylabel('y');
title('二阶常微分方程数值解');

