opt_minmax=1;     %目标优化类型：1最大化、-1最小化
sub=-1;            %变量取值下限
up=2.5;            %变量取值上限
delt=(up-sub)/5;
yita=0.99;
trace=[];          %模拟退火迭代性能跟踪器
k_total=3000;      %迭代总次数
tx=sub:.01:up;
y=fun_sigv(tx);
T=max(y)-min(y);   %模拟温度初始化
plot(tx,y)
xlabel('x')
ylabel('y')
title('一元函数优化结果')
hold on
x0=sub+(up-sub)*rand;
f0=fun_sigv(x0);   %随机产生初始点
k=0;
 plot(x0,f0,'ro','linewidth',2)  %在函数图像上标出初始点位置
while k<k_total
   x1=x0+(2*rand-1)*delt;
   x1=min(x1,up);
   x1=max(x1,sub);                        %在当前点附近随机产生下一个迭代点位置，并保证在所考查区域内
   f1=fun_sigv(x1);
   if opt_minmax*f1>opt_minmax*f0         %迭代点优于当前点，接受迭代结果并设置为当前点
       x0=x1;
       f0=f1;
   elseif rand<exp(opt_minmax*(f1-f0)/T)   %迭代点劣于当前点，以boltzmann概率接受迭代结果并设置为当前点
        x0=x1;
        f0=f1;
   end
   T=yita*T;                               %以缓慢速度衰减温度T
    k=k+1;
    trace=[trace;f0];                      %跟踪模拟退火的迭代优化过程
    [x0,f0]
end
plot(x0,f0,'r*','linewidth',2)
figure
plot(trace(:),'r-*')
hold on
xlabel('迭代次数')
ylabel('目标函数优化情况')
title('一元函数优化过程')
