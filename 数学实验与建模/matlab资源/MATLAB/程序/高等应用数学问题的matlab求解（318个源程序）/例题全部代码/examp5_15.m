syms t z; syms a positive
for i=1:8
    f=1/(t+a)^i; disp(int(f*t^(z-1),t,0,inf))
end