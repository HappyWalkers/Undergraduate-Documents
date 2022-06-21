x=[1 2 4 7 9 12 13 15 17];
f=[1.5 3.9 6 11.7 12.6 18.8 20.3 20.6 21.1];
axis([0 18 1  22])
xlabel('x')
ylabel('f')
y=1:0.1:17;

figure(1)
plot(x,f,'o')
gtext('已知数据点')
hold on;pause
bb1=interp1(x,f,y,'nearest')
plot(y,bb1)
gtext('nearest')
hold on;pause
a=polyfit(x,f,3)
aa=polyval(a,y)
plot(y,aa)
gtext('曲线拟合')
hold off;pause

figure(2)

plot(x,f,'o')
gtext('已知数据点')
hold on;pause
bb1=interp1(x,f,y,'linest')
plot(y,bb1)
gtext('linest')
hold on;pause
a=polyfit(x,f,3)
aa=polyval(a,y)
plot(y,aa)
gtext('曲线拟合')
hold off;pause

figure(3)

plot(x,f,'o')
gtext('已知数据点')
hold on;pause
bb1=interp1(x,f,y,'spline')
plot(y,bb1)
gtext('spline')
hold on;pause
a=polyfit(x,f,3)
aa=polyval(a,y)
plot(y,aa)
gtext('曲线拟合')
hold off;pause
