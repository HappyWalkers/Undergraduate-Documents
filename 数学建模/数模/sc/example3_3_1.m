clear
close all
clc

syms t x
L = 2;
r1 = 1/2;
r2 = 3/4;
q = 1000;
M0 = 900;
E = 200e+9; % E和I都是科学记数法表示 en还可以用10^n来表示
I = 2e-6;
Fb = (q * r1 * L / 2 + M0) / L; % 此行与下一行都是利用静力学三平衡方程求解支座反力
Fa = q * L * r1 - Fb;

n = 100;
l1 = linspace(0, L*r1, ceil(n*r1));
l2 = linspace(L*r1, L*r2, ceil(n*(r2-r1)));
l2 = l2(2:end);
l3 = linspace(L*r2, L, ceil(n*(1-r1)));
l3 = l3(2:end);
xx = [l1 l2 l3];

M1 = Fa*x-q*x.^2/2;
M2 = Fb*(L-x)-M0;
M3 = Fb*(L-x);

A1 = int(M1, 0, x) / (E*I); % A1 为求出的不带积分常量的转角
A2 = subs(A1, x, L*r1) + int(M2, L*r1, x) / (E*I); % A2 为求出的不带积分常量的转角
A3 = subs(A2, x, L*r2) + int(M3, L*r2, x) / (E*I); % A3 为求出的不带积分常量的转角

Y1 = int(A1, 0, x); % Y1 为求出的不带积分常量的转角
Y2 = subs(Y1, x, L*r1) + int(A2, L*r1, x); % Y2 为求出的不带积分常量的转角
Y3 = subs(Y2, x, L*r2) + int(A3, L*r2, x); % Y3 为求出的不带积分常量的转角

M = double([subs(M1, x, l1), subs(M2, x, l2), subs(M3, x, l3)]);
A0 = double([subs(A1, x, l1), subs(A2, x, l2), subs(A3, x, l3)]);
Y0 = double([subs(Y1, x, l1), subs(Y2, x, l2), subs(Y3, x, l3)]);

C = [0, 1;  L, 1] \ [-Y0(1);  -Y0(101)]; % 此处为边界方程的线性代数解法 
Ca = C(1);
Cy = C(2); % 标黄部分可以替代为Ca = (Y0(101)-Y0(1))/(x(1)-x(101));Cy = -Y0(1)-Ca*x(1);
A = A0 + Ca;
Y = Y0+ Ca * xx + Cy;

figure;
subplot(3,1,1);
plot(xx, M, 'r');
xlabel('Position');
title('Bending Moment Diagram');
grid;

subplot(3,1,2);
plot(xx, A, 'g');
xlabel('Position');
title('Slope Diagram');
ylabel('Slope');
grid;

subplot(3,1,3);
plot(xx, Y, 'b');
xlabel('Position');
title('Deflection Diagram');
ylabel('deflection');
grid;

