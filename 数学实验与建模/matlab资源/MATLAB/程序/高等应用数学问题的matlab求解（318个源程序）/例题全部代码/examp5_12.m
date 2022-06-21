syms t w; syms a positive
f=cos(t); F=simple(int(f*cos(w*t),t,0,a)); latex(F)
