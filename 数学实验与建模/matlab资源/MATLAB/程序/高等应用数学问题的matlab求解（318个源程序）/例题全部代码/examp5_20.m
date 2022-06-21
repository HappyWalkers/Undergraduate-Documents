syms z
f=sin(z+pi/3)*exp(-2*z)/(z^3*(z-1))
limit(diff(f*z^3,z,2)/prod(1:2),z,0)

limit(f*(z-1),z,1)