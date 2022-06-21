syms x y; f=(x^2-2*x)*exp(-x^2-y^2-x*y);
pretty(-simple(diff(f,x)/diff(f,y)))