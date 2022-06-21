syms A1 A2 w1 w2 t1 t2 t tau T; x=A1*cos(w1*t+t1)+A2*cos(w2*t+t2);
Rxx=simple(limit(int(x*subs(x,t,t+tau),t,0,T)/T,T,inf))