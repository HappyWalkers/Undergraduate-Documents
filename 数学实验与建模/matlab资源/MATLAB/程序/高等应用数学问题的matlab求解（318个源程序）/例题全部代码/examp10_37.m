H1=iir_frac(0.5,0,3,0.01); H2=iir_frac(0.5,0.5,3,0.01);
H3=iir_frac(0.5,0,4,0.01); H4=iir_frac(0.5,0,5,0.01);
bode(H1,'-',H2,'--',H3,':',H4,'-.')

t=0:0.01:pi; y=exp(-t).*sin(3*t+1); y0=glfdiff(y,t,0.5);
y1=filter(H1.num{1},H1.den{1},y); y2=filter(H2.num{1},H2.den{1},y);
y3=filter(H3.num{1},H3.den{1},y); y4=filter(H4.num{1},H4.den{1},y);
plot(t,y0,t,y1,':',t,y2,'--',t,y3,':')
