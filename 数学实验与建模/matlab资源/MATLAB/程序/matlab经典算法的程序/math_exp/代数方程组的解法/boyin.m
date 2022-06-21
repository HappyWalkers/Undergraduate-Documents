h=0.5;
a=0;
b=8;
n=80;
d=(b-a)/n;
for i=1:n+1
   pr(i)=a+(i-1)*d;
   p=pr(i);
   n=-78*p^2+655*p+125;
   x=h*n;
   r=p*x;
   c=50+1.5*x+8*x^(3/4);
   l(i)=r-c;
end
plot(pr,l);
grid on
xlabel('Price:p');
title ('Profit Curve:R(p)');<i