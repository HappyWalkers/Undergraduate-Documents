x=0:.001:1.2; y1=x; y2=x.^2; plot(x,y1,x,y2)

syms x; y1=x; y2=x^2; I1=int((x^2+y2^2)*sqrt(1+diff(y2,x)^2),x,0,1);
I2=int((x^2+y1^2)*sqrt(1+diff(y1,x)^2),x,1,0); I=I2+I1