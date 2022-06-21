x=[0:3*pi/2/200:3*pi/2]; y=cos(15*x); 
I=quadspln(x,y,0,3*pi/2)

x0=[0:3*pi/2/1000:3*pi/2]; y0=cos(15*x0);
y1=interp1(x,y,x0,'spline'); plot(x,y,x0,y1,':')

