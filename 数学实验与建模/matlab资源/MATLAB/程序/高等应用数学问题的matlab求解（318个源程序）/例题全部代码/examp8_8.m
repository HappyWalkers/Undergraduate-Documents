x=-3+6*rand(200,1); y=-2+4*rand(200,1);  % 重新生成样本点
z=(x.^2-2*x).*exp(-x.^2-y.^2-x.*y);
ii=find((x+1).^2+(y+0.5).^2>0.5^2);  % 找出不满足条件的点坐标
x=x(ii); y=y(ii); z=z(ii); plot(x,y,'x')
t=[0:.1:2*pi,2*pi]; x0=-1+0.5*cos(t); y0=-0.5+0.5*sin(t);
line(x0,y0)   % 在图形上叠印该圆，可见，圆内样本点均已剔除

[x1,y1]=meshgrid(-3:.2:3, -2:.2:2);
z1=griddata(x,y,z,x1,y1,'v4');
surf(x1,y1,z1), axis([-3,3,-2,2,-0.7,1.5])

z0=(x1.^2-2*x1).*exp(-x1.^2-y1.^2-x1.*y1);
surf(x1,y1,abs(z0-z1)), axis([-3,3,-2,2,0,0.1])

contour(x1,y1,abs(z0-z1),30); hold on, plot(x,y,'x'); line(x0,y0)