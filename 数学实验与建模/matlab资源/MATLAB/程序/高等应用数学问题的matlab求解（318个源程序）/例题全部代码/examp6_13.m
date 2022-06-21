f=inline('exp(-2*t).*cos(10*t)+exp(-3*(t+2)).*sin(2*t)','t'); % Ä¿±êº¯Êý

t0=1; [t1,f1]=fminsearch(f,t0); [t1 f1]

t0=0.1; [t2,f2]=fminsearch(f,t0); [t2 f2]

syms t; y=exp(-2*t)*cos(10*t)+exp(-3*(t+2))*sin(2*t);
ezplot(y,[0,2.5]); set(gca,'Ylim',[-0.6,1])

ezplot(y,[-0.5,2.5]); set(gca,'Ylim',[-2,1.2])
t0=-0.2; [t3,f3]=fminsearch(f,t0); [t3 f3]
