function y=generatenew(x,lb,ub)
n=length(x);
y=zeros(1,n);
for i=1:n
    y(i)=unifrnd(lb(i),ub(i));
end
<i