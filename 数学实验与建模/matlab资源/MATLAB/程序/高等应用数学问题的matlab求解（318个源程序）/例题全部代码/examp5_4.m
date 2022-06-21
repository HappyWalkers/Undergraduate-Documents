syms t s; f=t^2*exp(-2*t)*sin(t+pi);
F=simple(laplace(diff(f,t,5)))

F0=laplace(f); simple(F-s^5*F0)

ss=0; f1=f;
for i=4:-1:0
    ss=ss-s^i*subs(f1,t,0); f1=diff(f1,t);
end