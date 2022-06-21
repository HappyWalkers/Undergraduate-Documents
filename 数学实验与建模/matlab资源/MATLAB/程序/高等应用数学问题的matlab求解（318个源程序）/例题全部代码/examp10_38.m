H1=iir_pade(0.5,0,10,0.01); H2=iir_pade(0.5,0.75,10,0.01);
H2=minreal(H2); bode(H1,':',H2,'--')

t=0:0.01:pi; y=exp(-t).*sin(3*t+1); y0=glfdiff(y,t,0.5);
y2=filter(H2.num{1},H2.den{1},y); plot(t,y0,t,y2,':')