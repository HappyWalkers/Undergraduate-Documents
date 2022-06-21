clear
close all
clc

syms x y
As = [x.^2   2*x.*y   y.^2   2*x   2*y];

% �۲����ݣ�ת�ó����������Ա㹹�����
x0 = [5.764, 6.286, 6.759, 7.168, 7.408]';
y0 = [0.648, 1.202, 1.823, 2.526, 3.360]';

% �������Է����� A a = b
A = subs(As, {x, y}, {x0, y0});
b = 0*x0 - 1;

% ��ʾ�м����
disp('���Է����� Aa=b ϵ��:');
disp(num2str(double(A)));
disp(newline);

% ������Է�����
a = A\b;
disp('С���ǹ��δ֪�� a ��ֵ:');
disp(num2str(double(a)'));
disp(newline);

f = As * a + 1;
disp('С���ǹ������:');
disp(matlabFunction(collect(As * round(double(a),4) + 1, x)));
disp(newline);

figure;
plot(x0, y0, 'k*');
hold on;
fimplicit(f, [3 8 -1 5]);
legend('�۲��', 'С���ǹ켣','location','northwest');
xlabel('x');
ylabel('y');
axis([3.9 7.5 -0.3 3.9]);
title('С���ǹ��');