x=0.1:0.1:1;
y=[2.3201,2.6470,2.9707,3.2885,3.6008,3.9090,4.2147,4.5191,4.8232,5.1275];

a=lsqcurvefit('c8f3',[1;2;2;3],x,y); a'

y1=c2f3(a,x); plot(x,y,x,y1)
