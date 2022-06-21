syms t x; solve(exp(-3*t)*sin(4*t+2)+4*exp(-0.5*t)*cos(2*t)-0.5)

y=inline('exp(-3*t).*sin(4*t+2)+4*exp(-0.5*t).*cos(2*t)-0.5','t');
ff=optimset; ff.Display='iter'; [t,f]=fsolve(y,3.5203,ff)

ff=optimset; ff.TolX=1e-16; ff.TolFun=1e-30;
ff.Display='iter'; [t,f]=fsolve(y,3.5203,ff)
