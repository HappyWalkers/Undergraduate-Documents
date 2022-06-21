syms u v; syms a positive;
x=u*cos(v); y=u*sin(v); z=v; f=z;
E=simple(diff(x,u)^2+diff(y,u)^2+diff(z,u)^2);
F=diff(x,u)*diff(x,v)+diff(y,u)*diff(y,v)+diff(z,u)*diff(z,v);
G=simple(diff(x,v)^2+diff(y,v)^2+diff(z,v)^2);
I=int(int(f*sqrt(E*G-F^2),u,0,a),v,0,2*pi)
