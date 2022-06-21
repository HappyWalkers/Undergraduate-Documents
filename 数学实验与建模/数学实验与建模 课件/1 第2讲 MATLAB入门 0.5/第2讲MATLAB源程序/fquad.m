function y = fquad(x)
% 这是我的第一个matlab函数，用于计算四次函数值y 
y = 3*fx4(x) + 2*x + 1;
end

function y = fx4(x)
y = x.^4;
end
