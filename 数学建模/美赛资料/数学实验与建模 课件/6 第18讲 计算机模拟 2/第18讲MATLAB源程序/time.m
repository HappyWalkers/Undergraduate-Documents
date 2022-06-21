clear
clc

maxTankNum = 10000;
maxTime = 3;
lamda = 4;
t = zeros(maxTankNum, 1);

j = 1;
t(j) = exprnd(1/lamda);
timeLeft = maxTime - t(j);
while timeLeft>0
   j = j + 1;
   t(j) = t(j-1) +exprnd(1/lamda);
   timeLeft = maxTime - t(j);
end
j = j - 1;
T = t(1:j);
T;
x = 1:j;

figure;
plot(x, T,'-k.');
xlabel('顾客到达');
ylabel('到达时间');
for i=1:j
 text(x(i)+0.2, T(i)-0.025, ['(' num2str(x(i)) ', ' num2str(T(i)) ')']);
end
