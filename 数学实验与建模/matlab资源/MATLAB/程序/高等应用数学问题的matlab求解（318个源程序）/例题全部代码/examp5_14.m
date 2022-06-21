syms t z; syms a positive;
f=log(t)/(t+a); M=simple(int(f*t^(z-1),t,0,inf)), latex(M)

