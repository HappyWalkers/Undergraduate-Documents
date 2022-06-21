function y = fLargrange(x, Y, xi)
n = length(x);
m = length(xi);
y = 0*xi;

for idz = 1:m
    xq = xi(idz);
    for i = 1:n
        p = 1;
        for j=1:n
            if j~=i
                p = p * (xq-x(j))/ (x(i)-x(j));
            end
        end
        y(idz) = y(idz) + p * Y(i);
    end
end