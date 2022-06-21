[x,y]=meshgrid(-2:.1:2);
z=1./(sqrt((1-x).^2+y.^2))+1./(sqrt((1+x).^2+y.^2));
surf(x,y,z), shading flat

xx=[-2:.1:-1.2, -1.1:0.02:-0.9, -0.8:0.1:0.8, 0.9:0.02:1.1, 1.2:0.1:2];
yy=[-1:0.1:-0.2, -0.1:0.02:0.1, 0.2:.1:1];
[x,y]=meshgrid(xx,yy);
z=1./(sqrt((1-x).^2+y.^2))+1./(sqrt((1+x).^2+y.^2));
surf(x,y,z), shading flat; set(gca,'zlim',[0,15])
