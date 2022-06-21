syms t w; syms a positive
f=t^a; F=maple('hankel',f,t,w,0)

syms t x a;
F=maple('hankel',a/(a^2+t^2)^(3/2),t,w,0)