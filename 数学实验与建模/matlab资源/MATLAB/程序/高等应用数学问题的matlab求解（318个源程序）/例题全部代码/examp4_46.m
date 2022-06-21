syms t; A=[-3,-1,-1; 0,-3,-1; 1,2,0]; simple(expm(A*t))

[V,J]=jordan(A)   % Jordan æÿ’Û±‰ªª

J1=[exp(-2*t), t*exp(-2*t), 1/2*t^2*exp(-2*t);
            0,   exp(-2*t),       t*exp(-2*t);
            0,           0,         exp(-2*t)];

A1=simple(V*J1*inv(V))