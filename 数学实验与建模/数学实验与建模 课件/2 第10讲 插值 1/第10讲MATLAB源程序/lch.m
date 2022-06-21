m=101;
x=-5:10/(m-1):5;
y=1./(1+x.^2);z=0*x;
plot(x,z,'r',x,y,'LineWidth',1.5),
gtext('y=1/(1+x^2)'),pause

n=3;
x0=-5:10/(n-1):5;
y0=1./(1+x0.^2);
y1=lagr1(x0,y0,x);
hold on,plot(x,y1,'b'),gtext('n=2'),pause,
hold off

n=5;
x0=-5:10/(n-1):5;
y0=1./(1+x0.^2);
y2=lagr1(x0,y0,x);
hold on,plot(x,y2,'b:'),gtext('n=4'),pause,
hold off

n=7;
x0=-5:10/(n-1):5;
y0=1./(1+x0.^2);
y3=lagr1(x0,y0,x);hold on,
plot(x,y3,'r'),gtext('n=6'),pause,
hold off

n=9;
x0=-5:10/(n-1):5;
y0=1./(1+x0.^2);
y4=lagr1(x0,y0,x);hold on,
plot(x,y4,'r:'),gtext('n=8'),pause,
hold off

n=11;
x0=-5:10/(n-1):5;
y0=1./(1+x0.^2);
y5=lagr1(x0,y0,x);hold on,
plot(x,y5,'m'),gtext('n=10')

