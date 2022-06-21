function y = fquadImp(x,a)
% ���ڼ���n-1�κ���ֵy 
% y = a(1) + a(2)*x + a(3).*x^2 + ...
a = a(:)';
x = x(:)';

na = length(a);
X = repmat(x, na, 1);
X(1,:) = 1;

for i=3:na
    X(i,:) = X(i-1,:) .* x;
end

y = a * X;
end
