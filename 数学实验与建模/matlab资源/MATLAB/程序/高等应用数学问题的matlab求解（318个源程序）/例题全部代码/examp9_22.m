a=[1;1;1;1;1;1]';
f=inline(['(a(1)*x(:,1).^3+a(2)).*sin(a(3)*x(:,2).*x(:,3))+',...
    '(a(4)*x(:,3).^3+a(5)*x(:,3)+a(6))'],'a','x');
X=randn(120,4); y=f(a,X)+sqrt(0.2)*randn(120,1);

[ahat,r,j]=nlinfit(X,y,f,[0;2;3;2;1;2]); ahat

ci=nlparci(ahat,r,j); ci
