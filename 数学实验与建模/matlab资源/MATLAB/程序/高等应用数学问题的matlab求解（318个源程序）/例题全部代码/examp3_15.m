syms x y z; f0=-4*z*exp(-x^2*y-z^2)*(cos(x^2*y)-10*cos(x^2*y)*y*x^2+...
    4*sin(x^2*y)*x^4*y^2+4*cos(x^2*y)*x^4*y^2-sin(x^2*y));
f1=int(f0,z); f1=int(f1,y); f1=int(f1,x); f1=simple(int(f1,x))

f2=int(f0,z); f2=int(f2,x); f2=int(f2,x); f2=simple(int(f2,y))

simple(f1-f2)