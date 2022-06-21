syms t z; syms a positive
F=maple('mellin',1/(t+a)^8,t,z)

f1=maple('invmellin',F,z,t)