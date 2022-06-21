syms w t; syms a positive
f=exp(-a*abs(t))/sqrt(abs(t)); F=fourier(f,t,w)

f1=exp(a*t)/sqrt(-t); f2=exp(-a*t)/sqrt(t); j=sym(sqrt(-1));
F=int(f1*exp(-j*w*t),-inf,0)+int(f2*exp(-j*w*t),0,inf)