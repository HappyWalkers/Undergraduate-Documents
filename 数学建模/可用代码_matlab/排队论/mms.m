
s=2;%服务台个数
mu=4;%单位服务台 单位时间 内能够服务的顾客人数
lambda=3;%单位时间 内到达系统的人数
ro=lambda/mu;%服务强度
ros=ro/s;
sum1=0;

for i=0:(s-1)
    sum1=sum1+ro.^i/factorial(i);
end

sum2=ro.^s/factorial(s)/(1-ros);

p0=1/(sum1+sum2);
p=ro.^s.*p0/factorial(s)/(1-ros);
Lq=p.*ros/(1-ros);
L=Lq+ro;
W=L/lambda;
Wq=Lq/lambda;
fprintf('排队等待的平均人数为%5.2f人\n',Lq)
fprintf('系统内的平均人数为%5.2f人\n',L)
fprintf('平均逗留时间为%5.2f分钟\n',W*60)
fprintf('平均等待时间为%5.2f分种\n',Wq*60)