x0=0:.1:1; y0=(x0.^2-3*x0+5).*exp(-5*x0).*sin(x0);
p3=polyfit(x0,y0,3); vpa(poly2sym(p3),10) % 可以如下显示多项式

x=0:.01:1; ya=(x.^2-3*x+5).*exp(-5*x).*sin(x);
y1=polyval(p3,x); plot(x,y1,x,ya,x0,y0,'o')

p4=polyfit(x0,y0,4); y2=polyval(p4,x);
p5=polyfit(x0,y0,5); y3=polyval(p5,x);
p8=polyfit(x0,y0,8); y4=polyval(p8,x);
plot(x,ya,x0,y0,'o',x,y2,x,y3,x,y4)

vpa(poly2sym(p8),5)

syms x; y=(x^2-3*x+5)*exp(-5*x)*sin(x);
vpa(taylor(y,9),5)
