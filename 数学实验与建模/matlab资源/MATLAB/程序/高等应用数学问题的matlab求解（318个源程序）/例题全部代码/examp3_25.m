syms m n; limit(symsum(1/m,m,1,n)-log(n),n,inf)

vpa(ans, 70)  % 显示 70 位有效数字