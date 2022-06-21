x0=-1+2*[0:10]/10; y0=1./(1+25*x0.^2);
x=-1:.01:1; ya=1./(1+25*x.^2);
p3=polyfit(x0,y0,3); y1=polyval(p3,x);
p5=polyfit(x0,y0,5); y2=polyval(p5,x);
p8=polyfit(x0,y0,8); y3=polyval(p8,x);
p10=polyfit(x0,y0,10); y4=polyval(p10,x);
plot(x,ya,x,y1,x,y2,'-.',x,y3,'--',x,y4,':')

syms x; y=1/(1+25*x^2); p=taylor(y,x,10)

x1=-1:0.01:1; ya=1./(1+25*x1.^2); y1=subs(p,x,x1); plot(x1,y1)