function c1ex4
[t,x]=ode45('myvdpeq',[0,10],[-1;1]);  % 直接求微分方程数值解
% 下面的函数描述 Van de Pol 方程本身
function y=myvdpeq(t,x)
y=[x(2); -(x(1)^2-1)*x(2)-x(1)];

%延迟微分方程可以用 dde23() 函数求解，也可以用 Simulink 求解，后者更直观
% 下面绘制出 Simulink 模型，选择 Simulation/Start 菜单可以启动求解程序
c1ex4mod