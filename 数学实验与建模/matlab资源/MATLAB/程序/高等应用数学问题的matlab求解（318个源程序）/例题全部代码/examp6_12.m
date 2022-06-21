f=inline('(x(1)^2-2*x(1))*exp(-x(1)^2-x(2)^2-x(1)*x(2))','x');
x0=[0; 0]; ff=optimset; ff.Display='iter';
x=fminsearch(f,x0,ff)

x=fminunc(f,[0;.0],ff)

xx=[2  0.2401 -0.1398 0.2168  0.3355  0.5514  0.6129  0.6111
    1  1.0502  0.5752 1.0210 -0.5508 -0.1775 -0.3053 -0.3058];
[x,y]=meshgrid(-3:.1:3, -2:.1:2);
z=(x.^2-2*x).*exp(-x.^2-y.^2-x.*y);
contour(x,y,z,30); line(xx(1,:),xx(2,:))
h=line(xx(1,:),xx(2,:)); set(h,'Marker','o')