syms t; y=sym('f(t)')  % ����ԭ����
laplace(diff(y,t,2))

laplace(diff(y,t,8))
