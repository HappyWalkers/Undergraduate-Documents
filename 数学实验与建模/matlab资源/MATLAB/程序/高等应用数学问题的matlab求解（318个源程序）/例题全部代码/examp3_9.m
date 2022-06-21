syms t; y=sin(t)/(t+1)^3; x=cos(t)/(t+1)^3;
latex(diff(y,t,4)/diff(x,t,4))