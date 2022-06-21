syms x; f=abs(x)/x;  % 定义方波信号
xx=[-pi:pi/200:pi]; xx=xx(xx~=0); xx=sort([xx,-eps,eps]); % 剔除零点
yy=subs(f,x,xx); plot(xx,yy), hold on  % 绘制出理论值并保持坐标系
for n=2:20
    [a,b,f1]=fseries(f,x,n), y1=subs(f1,x,xx); plot(xx,y1)
end
% 本例在 MATLAB 6.1, 6.5 和 7.0 中正常， 但6.5.1有问题

[a,b,f1]=fseries(f,x,14); latex(f1)