[x,y]=meshgrid(-3:.6:3, -2:.4:2); z=(x.^2-2*x).*exp(-x.^2-y.^2-x.*y);
surf(x,y,z), axis([-3,3,-2,2,-0.7,1.5])

[x1,y1]=meshgrid(-3:.2:3, -2:.2:2);
z1=interp2(x,y,z,x1,y1); surf(x1,y1,z1), axis([-3,3,-2,2,-0.7,1.5])

z1=interp2(x,y,z,x1,y1,'cubic'); z2=interp2(x,y,z,x1,y1,'spline');
surf(x1,y1,z1), axis([-3,3,-2,2,-0.7,1.5])
figure; surf(x1,y1,z2), axis([-3,3,-2,2,-0.7,1.5])

z=(x1.^2-2*x1).*exp(-x1.^2-y1.^2-x1.*y1);  % 新网格各点的函数值
surf(x1,y1,abs(z-z1)), axis([-3,3,-2,2,0,0.08])
figure; surf(x1,y1,abs(z-z2)), axis([-3,3,-2,2,0,0.025])
