x=-3+6*rand(200,1); y=-2+4*rand(200,1);
z=(x.^2-2*x).*exp(-x.^2-y.^2-x.*y);   % 生成已知数据
plot(x,y,'x')   % 样本点的二维分布
figure, plot3(x,y,z,'x'), axis([-3,3,-2,2,-0.7,1.5])

[x1,y1]=meshgrid(-3:.2:3, -2:.2:2);
z1=griddata(x,y,z,x1,y1,'cubic'); surf(x1,y1,z1), axis([-3,3,-2,2,-0.7,1.5])
z2=griddata(x,y,z,x1,y1,'v4');
figure; surf(x1,y1,z2), axis([-3,3,-2,2,-0.7,1.5])

z0=(x1.^2-2*x1).*exp(-x1.^2-y1.^2-x1.*y1);  % 新网格各点的函数值
surf(x1,y1,abs(z0-z1));  axis([-3,3,-2,2,0,0.15])
figure; surf(x1,y1,abs(z0-z2));  axis([-3,3,-2,2,0,0.15])