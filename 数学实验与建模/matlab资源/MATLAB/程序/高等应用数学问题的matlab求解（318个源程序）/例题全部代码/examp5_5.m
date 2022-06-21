syms t; y=sym('f(t)')  % 定义原函数
laplace(diff(y,t,2))

laplace(diff(y,t,8))
