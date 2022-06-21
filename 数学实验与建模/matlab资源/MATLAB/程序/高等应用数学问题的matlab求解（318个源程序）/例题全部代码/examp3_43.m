syms u v; syms a b c positive;
x=a*sin(u)*cos(v); y=b*sin(u)*sin(v); z=c*cos(u);
A=diff(y,u)*diff(z,v)-diff(z,u)*diff(y,v);
I=int(int(x^3*A,u,0,pi/2),v,0,2*pi)