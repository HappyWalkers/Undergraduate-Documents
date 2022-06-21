clear
% close all
clc

L = 2;
r1 = 1/2;
r2 = 3/4;
q = 1000;
M0 = 900;
E = 200e+9; %E和I都是科学记数法表示 en还可以用10^n来表示
I = 2e-6;
Fb = (q * r1 * L / 2 + M0) / L; %此行与下一行都是利用静力学三平衡方程求解支座反力
Fa = q * L * r1 - Fb;

n = 100;
x = linspace(0, L, n+1);
dx = L/n;%截取所求数值的点，保证包含突变控制截面
M1 = Fa*x(1:51)-q*x(1:51).^2/2;
M2 = Fb*(L-x(52:76))-M0;
M3 = Fb*(L-x(77:101));
M = [M1,M2,M3];
A0 = cumtrapz(M)*dx/(E*I);%A0为求出的不带积分常量的转角
Y0 = cumtrapz(A0)*dx; %Y0为求出的不带积分常量的挠度
C = [0,1;L,1]\[-Y0(1);-Y0(101)];%此处为边界方程的线性代数解法 
Ca = C(1);
Cy = C(2);%标黄部分可以替代为Ca = (Y0(101)-Y0(1))/(x(1)-x(101));Cy = -Y0(1)-Ca*x(1);
A = A0+Ca;
Y = Y0+Ca*x+Cy;

figure;
subplot(3,1,1);
plot(x,M, 'r');
xlabel('Position');
title('Bending Moment Diagram');
grid;

subplot(3,1,2);
plot(x,A, 'g');
xlabel('Position');
title('Slope Diagram');
ylabel('Slope');
grid;

subplot(3,1,3);
plot(x,Y, 'b');
xlabel('Position');
title('Deflection Diagram');
ylabel('deflection');
grid;

