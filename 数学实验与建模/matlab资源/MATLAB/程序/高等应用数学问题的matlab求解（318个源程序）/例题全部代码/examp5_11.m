syms t w; syms a positive
f=t^6*exp(-a*t); F=maple('fouriercos',f,t,w); latex(F)

f1=maple('invfouriercos',F,w,t)