i=sym(sqrt(-1)); syms z
f=1/((z+i)^10*(z-1)*(z-3));   % 定义被积函数
r1=limit(diff(f*(z+i)^10,z,9)/prod(1:9),z,-i);
r2=limit(f*(z-1),z,1); a=2*pi*i*(r1+r2)

a+pi*i/(3+i)^10

r3=limit(f*(z-3),z,3); b=2*pi*i*(r1+r2+r3)