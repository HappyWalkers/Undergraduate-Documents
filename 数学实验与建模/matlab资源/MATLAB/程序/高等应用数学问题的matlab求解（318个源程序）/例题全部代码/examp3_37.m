syms t; syms a positive; x=a*cos(t); y=a*sin(t); z=a*t;
I=int(z^2/(x^2+y^2)*sqrt(diff(x,t)^2+diff(y,t)^2+diff(z,t)^2),t,0,2*pi)