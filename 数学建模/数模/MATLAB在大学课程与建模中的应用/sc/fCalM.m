function M = fCalM(x, r, L, Fa, Fb, q, M0)
if r<=1/2
    M = Fa*x-q*x.^2/2;
elseif r<=3/4
    M = Fb*(L-x)-M0;
else
    M = Fb*(L-x);
end