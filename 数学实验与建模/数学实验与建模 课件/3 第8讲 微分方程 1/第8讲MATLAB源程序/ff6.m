clear all
close all
clc

x0=0;
xf=0.99999;
[x,y]=ode23('eq1',[x0 xf],[0 0]);
Y=0:0.01:2;

figure;
plot(1,Y,'g.')
hold on
plot(x,y(:,1),'b*')
xlabel('t');
ylabel('y');
title('µ¼µ¯×·×ÙÎÊÌâ');


