syms z; f=1/(z*sin(z));
c0=limit(f*z^2,z,0)

k=[-4 4 -3 3 -2 2 -1 1]; c=[];
for kk=k; c=[c,limit(f*(z-kk*pi),z,kk*pi)]; end; c

