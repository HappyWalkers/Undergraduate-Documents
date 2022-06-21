syms t; y=exp(-3*t)*sin(4*t+2)+4*exp(-0.5*t)*cos(2*t)-0.5;
y1=diff(y,t); % 求取一阶导函数
ezplot(y1,[0,4])  % 绘制出选定区间内一阶导函数曲线

t0=solve(y1)    % 求出一阶导数等于零的点

y2=diff(y1); b=subs(y2,t,t0) % 并验证二阶导数为正