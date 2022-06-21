clear all
close all
clc

t0=0;
tf=2;
[t,y]=ode45('eq2',[t0 tf],[0 0]);
% X=1;
Y=0:0.01:2;
X = Y * 0 + 1;
% X = 1;

figure;
plot(X,Y,'k-')
axis([0 2.2 0 2.2]);
hold on
plot(y(:,1),y(:,2),'-k.')

