clc
clear all
opt_minmax=1;     %目标优化类型：1最大化、-1最小化
sub=-10;           %变量取值下限
up=10;            %变量取值上限
delt=(up-sub)/5;
yita=0.99;
trace=[];          %模拟退火迭代性能跟踪器
k_total=3000;      %迭代总次数
[tx,ty]=meshgrid(sub:.1:up);
tz=fun_mutv(tx,ty);
T=max(max(tz))-min(min(tz));   %模拟温度初始化
mesh(tx,ty,tz)
xlabel('x')
ylabel('y')
zlabel('z')
title('多元函数优化结果')
hold on
x0=[sub+(up-sub)*rand,sub+(up-sub)*rand];
f0=fun_mutv(x0(1),x0(2));           %随机产生初始点
k=0;
plot3(x0(1),x0(2),f0,'ko','linewidth',2)  %在函数图像上标出初始点位置
while k<k_total
   x1=[x0(1)+(2*rand-1)*delt,x0(2)+(2*rand-1)*delt];
   x1=[min(x1(1),up),min(x1(2),up)];
   x1=[max(x1(1),sub),max(x1(2),sub)];       %在当前点附近随机产生下一个迭代点位置，并保证在所考查区域内
   f1=fun_mutv(x1(1),x1(2));
   if opt_minmax*f1>opt_minmax*f0         %迭代点优于当前点，接受迭代结果并设置为当前点
       x0=x1;
       f0=f1;
   elseif rand<exp(opt_minmax*(f1-f0)/T)   %迭代点劣于当前点，以boltzmann概率接受迭代结果并设置为当前点
        x0=x1;
        f0=f1;
   end
   T=yita*T;                             %以缓慢速度衰减温度T
    k=k+1;
    trace=[trace;f0];                      %跟踪模拟退火的迭代优化过程
    [x0,f0]
end
plot3(x0(1),x0(2),f0,'k*','linewidth',2)
figure
plot(trace(:),'r-*')
hold on
xlabel('迭代次数')
ylabel('目标函数优化情况')
title('多元函数优化过程')
