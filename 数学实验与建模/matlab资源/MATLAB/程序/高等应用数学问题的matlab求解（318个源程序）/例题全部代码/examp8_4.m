x0=0:pi/30:pi; y0=sin(x0); I=quadspln(x0,y0,0,pi)

x0=0:pi/10:pi; y0=sin(x0); I1=trapz(x0,y0)

I=quadspln(x0,y0,0,pi)

x0=[0,0.4,1 2,pi]; y0=sin(x0);  % 生成样本点
plot(x0,y0,x0,y0,'o')   % 绘制出的样本点折线如图 8-3a 所示。
I=quadspln(x0,y0,0,pi)  % 大约有 1% 的相对误差，应该说是相当精确的

I1=trapz(x0,y0)   % 用 trapz() 函数将得出很大的相对误差 (7.9%)

x=[0:0.01:pi,pi]; y0a=sin(x); y=interp1(x0,y0,x,'spline');
plot(x0,y0,x,y,':',x,y0a,x0,y0,'o')