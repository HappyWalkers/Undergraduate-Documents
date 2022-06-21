f=inline('exp(-x.^2/2).*sin(x.^2+y)','x','y');
y=dblquad(f,-2,2,-1,1),

