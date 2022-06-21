syms t w; syms a positive
for i=1:8
    f=t^i*exp(-a*t); F=int(f*cos(w*t),t,0,inf); latex(simple(F))
end

