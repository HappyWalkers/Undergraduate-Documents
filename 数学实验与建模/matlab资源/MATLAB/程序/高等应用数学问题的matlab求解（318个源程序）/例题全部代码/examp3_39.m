syms t; syms a positive; x=a*cos(t); y=a*sin(t);
F=[(x+y)/(x^2+y^2),-(x-y)/(x^2+y^2)]; ds=[diff(x,t);diff(y,t)];
I=int(F*ds,t,2*pi,0)  % ÕıÏòÔ²ÖÜ