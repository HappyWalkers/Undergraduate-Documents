syms a x; f=simple(int(x^3*cos(a*x)^2,x))

f1=x^4/8+(x^3/(4*a)-3*x/(8*a^3))*sin(2*a*x)+...
    (3*x^2/(8*a^2)-3/(16*a^4))*cos(2*a*x);
simple(f-f1)  % 求两个结果的差