A=[]; B=[]; p=normrnd(0.5,1.5,30000,1); n=1:5;
for r=n,
    A=[A, sum(p.^r)/length(p)]; B=[B,moment(p,r)];
end
A,B

syms x; A1=[]; B1=[]; p=1/(sqrt(2*pi)*1.5)*exp(-(x-0.5)^2/(2*1.5^2));
for i=1:5
    A1=[A1,vpa(int(x^i*p,x,-inf,inf),12)];
    B1=[B1,vpa(int((x-0.5)^i*p,x,-inf,inf),12)];
end

A1, B1
