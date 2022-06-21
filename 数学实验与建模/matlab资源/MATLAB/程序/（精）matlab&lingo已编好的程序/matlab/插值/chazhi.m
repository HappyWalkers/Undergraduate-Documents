%产生原始数据
x=0:0.1:1;
y=(x.^2-3*x+7).*exp(-4*x).*sin(2*x);
%线性插值
xx=0:0.01:1;
y1=interp1(x,y,xx,'linear');
subplot(2,2,1)
plot(x,y,'o',xx,y1);
title('线性插值');
%最邻近点插值
y2=interp1(x,y,xx,'nearest');
subplot(2,2,2)
plot(x,y,'o',xx,y2);
title('最邻近点插值');
%三次插值
y3=interp1(x,y,xx,'cubic');
subplot(2,2,3)
plot(x,y,'o',xx,y3);
title('三次插值');
%三次样条插值
y4=interp1(x,y,xx,'spline');
subplot(2,2,4)
plot(x,y,'o',xx,y4);
title('三次样条插值');
