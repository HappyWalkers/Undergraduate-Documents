syms x y; syms a positive; z=a-x-y;
I=int(int(x*y*z*sqrt(1+diff(z,x)^2+diff(z,y)^2),y,0,a-x),x,0,a)
