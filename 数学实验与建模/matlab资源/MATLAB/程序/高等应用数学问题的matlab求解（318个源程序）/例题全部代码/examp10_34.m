t=0:0.01:pi; y=sin(3*t+1); y1=3^0.75*sin(3*t+1+0.75*pi/2);
y2=glfdiff(y,t,0.75); plot(t,y1,t,y2)

