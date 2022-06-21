clear
% close all
clc

L = 2;
r1 = 1/2;
r2 = 3/4;
q = 1000;
M0 = 900;
E = 200e+9; %E��I���ǿ�ѧ��������ʾ en��������10^n����ʾ
I = 2e-6;
Fb = (q * r1 * L / 2 + M0) / L; %��������һ�ж������þ���ѧ��ƽ�ⷽ�����֧������
Fa = q * L * r1 - Fb;

n = 100;
x = linspace(0, L, n+1);
dx = L/n;%��ȡ������ֵ�ĵ㣬��֤����ͻ����ƽ���
M1 = Fa*x(1:51)-q*x(1:51).^2/2;
M2 = Fb*(L-x(52:76))-M0;
M3 = Fb*(L-x(77:101));
M = [M1,M2,M3];
A0 = cumtrapz(M)*dx/(E*I);%A0Ϊ����Ĳ������ֳ�����ת��
Y0 = cumtrapz(A0)*dx; %Y0Ϊ����Ĳ������ֳ������Ӷ�
C = [0,1;L,1]\[-Y0(1);-Y0(101)];%�˴�Ϊ�߽緽�̵����Դ����ⷨ 
Ca = C(1);
Cy = C(2);%��Ʋ��ֿ������ΪCa = (Y0(101)-Y0(1))/(x(1)-x(101));Cy = -Y0(1)-Ca*x(1);
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

