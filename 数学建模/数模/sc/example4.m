clear
close all
clc

format long g

syms x t
f = x^t * exp(x-1);
F = int(f,x,0,1);
simplify(F)

N = 6;
n = 9999;
nDisplay = 9;

E1 = zeros(n,1);
for i=1:n
    E1(i) = round(double(subs(F,t,i)), N);
end
[E1(nDisplay) E1(n)]


E2 = zeros(n,1);
E2(1) = round(1/exp(1),N);
for i=2:n
    E2(i) = round(1-i*E2(i-1),N);
end
[E2(nDisplay) E2(n)]


E3(n) = round(1/(n+1),N);
for i=(n-1):-1:1
    E3(i) = round((1-E3(i+1))/(i+1),N);
end
[E3(nDisplay) E3(n)]


nDraw = 10;
figure;
plot(1:nDraw, E1(1:nDraw),'-k.');
hold on;
plot(1:nDraw, E2(1:nDraw),'-r.');
plot(1:nDraw, E3(1:nDraw),'-b.');
legend('符号运算','正向计算','反向计算');
xlabel('n');
ylabel('积分结果');


nDraw = 325;
figure;
plot(1:nDraw, E1(1:nDraw),'-k.');
hold on;
plot(1:nDraw, E3(1:nDraw),'-b.');
legend('符号运算','反向计算');
xlabel('n');
ylabel('积分结果');

