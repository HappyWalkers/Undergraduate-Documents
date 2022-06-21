clear
close all
clc

dsolve('Du=1+u^2','t')

syms u(t)
dsolve(diff(u,t) == 1+u^2)











