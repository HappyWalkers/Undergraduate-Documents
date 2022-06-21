x=0:.12:1;
y=(x.^2-3*x+5).*exp(-5*x).*sin(x); plot(x,y,x,y,'o')

x1=0:.02:1; y0=(x1.^2-3*x1+5).*exp(-5*x1).*sin(x1);
y1=interp1(x,y,x1); y2=interp1(x,y,x1,'cubic');
y3=interp1(x,y,x1,'spline'); y4=interp1(x,y,x1,'nearest');
plot(x1,[y1',y2',y3',y4'],':',x,y,'o',x1,y0)
[max(abs(y0(1:49)-y2(1:49))),max(abs(y0-y3)),max(abs(y0-y4))]
