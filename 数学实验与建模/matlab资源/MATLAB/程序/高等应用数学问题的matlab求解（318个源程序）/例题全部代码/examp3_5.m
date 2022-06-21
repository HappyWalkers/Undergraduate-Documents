syms x y
z=(x^2-2*x)*exp(-x^2-y^2-x*y);
zx=simple(diff(z,x))

zy=diff(z,y)

[x,y]=meshgrid(-3:.2:3,-2:.2:2);
z=(x.^2-2*x).*exp(-x.^2-y.^2-x.*y);
surf(x,y,z), axis([-3 3 -2 2 -0.7 1.5]) % 直接绘制三维曲面

contour(x,y,z,30), hold on   % 绘制等值线
zx=-exp(-x.^2-y.^2-x.*y).*(-2*x+2+2*x.^3+x.^2.*y-4*x.^2-2*x.*y);
zy=-x.*(x-2).*(2*y+x).*exp(-x.^2-y.^2-x.*y);    % 偏导的数值解
quiver(x,y,zx,zy)  % 绘制引力线