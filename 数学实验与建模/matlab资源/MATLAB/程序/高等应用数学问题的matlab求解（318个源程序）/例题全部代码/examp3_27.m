[x,y]=meshgrid(-3:.2:3,-2:.2:2); z=(x.^2-2*x).*exp(-x.^2-y.^2-x.*y);
[fx,fy]=gradient(z); fx=fx/0.2; fy=fy/0.2;
contour(x,y,z,30); hold on; quiver(x,y,fx,fy)

zx=-exp(-x.^2-y.^2-x.*y).*(-2*x+2+2*x.^3+x.^2.*y-4*x.^2-2*x.*y);
zy=-x.*(x-2).*(2*y+x).*exp(-x.^2-y.^2-x.*y);
surf(x,y,abs(fx-zx)); axis([-3 3 -2 2 0,0.08])
figure;
surf(x,y,abs(fy-zy)); axis([-3 3 -2 2 0,0.11])

[x,y]=meshgrid(-3:.1:3,-2:.1:2); z=(x.^2-2*x).*exp(-x.^2-y.^2-x.*y);
[fx,fy]=gradient(z); fx=fx/0.1; fy=fy/0.1;
zx=-exp(-x.^2-y.^2-x.*y).*(-2*x+2+2*x.^3+x.^2.*y-4*x.^2-2*x.*y);
zy=-x.*(x-2).*(2*y+x).*exp(-x.^2-y.^2-x.*y);
surf(x,y,abs(fx-zx)); axis([-3 3 -2 2 0,0.02])
figure; surf(x,y,abs(fy-zy)); axis([-3 3 -2 2 0,0.06])