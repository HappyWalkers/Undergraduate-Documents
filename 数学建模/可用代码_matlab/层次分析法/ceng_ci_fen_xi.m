disp('�������жϾ���A(n��)');
A=input('A=');
[n,n]=size(A);
x=ones(n,100);
y=ones(n,100);
m=zeros(1,100);
m(1)=max(x(:,1));
y(:,1)=x(:,1);
x(:,2)=A*y(:,1);
m(2)=max(x(:,2));
y(:,2)=x(:,2)/m(2);
p=0.0001;i=2;k=abs(m(2)-m(1));
while  k>p
    i=i+1;
    x(:,i)=A*y(:,i-1);
    m(i)=max(x(:,i));
    y(:,i)=x(:,i)/m(i);
    k=abs(m(i)-m(i-1));
end
a=sum(y(:,i));
w=y(:,i)/a;
t=m(i);
disp(w);
%������һ���Լ���
CI=(t-n)/(n-1);
% RI=[0 0 0.52 0.89 1.12 1.26 1.36 1.41 1.46 1.49 1.52 1.54 1.56 1.58 1.59];


p = [1,2,3,4,5,6,7,8,9,1/2,1/3,1/4,1/5,1/6,1/7,1/8,1/9];
L = length(p);
A = ones(n,n);
number = 8192;
R = 0;
for kp = 1:number
    for i = 1:n-1
        for j = i+1:n
            k = floor(1+L*rand(1));
            A(i,j) = p(k);
            A(j,i) = 1/p(k);
        end
    end
    lambda = max(eig(A));
    temp = (lambda - n)/(n-1);
    R = R+temp;
end
RI = R/number;

CR=CI/RI;
if CR<0.10
    disp('�˾����һ���Կ��Խ���!');
    disp('CI=');disp(CI);
    disp('CR=');disp(CR);
end
