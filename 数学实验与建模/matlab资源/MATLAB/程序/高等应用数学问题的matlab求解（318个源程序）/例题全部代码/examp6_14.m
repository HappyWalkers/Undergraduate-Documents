[x,y]=meshgrid(0.5:0.01:1.5); z=100*(y.^2-x).^2+(1-x).^2;
contour3(x,y,z,100), set(gca,'zlim',[0,310])

f=inline('100*(x(2)-x(1)^2)^2+(1-x(1))^2','x');
ff=optimset; ff.TolX=1e-10; ff.TolFun=1e-20; ff.Display='iter';
x=fminunc(f,[0;0],ff)

syms x1 x2; f=100*(x2-x1^2)^2+(1-x1)^2;
J=jacobian(f,[x1,x2])

ff.GradObj='on'; x=fminunc('c6fun3',[0;0],ff)

