alpha=0.1255;
m=1.109e5;
 
run=200;
X1=zeros(run+1,1);
X2=zeros(run+1,1);
X3=zeros(run+1,1);
X4=zeros(run+1,1);

k=0.5;%
error=1e-5;
f_k=zeros(floor((1-k)/error+1),1);
t=0;
for k=0.5:error:1
t=t+1;
k
X1(1)=122e9;
X2(1)=29.7e9;
X3(1)=10.1e9;
X4(1)=3.29e9;
    for j=1:1:run
beta=1.22e11/(1.22e11+0.5*m*(1-alpha-0.42*k)^8*X3(j)+m*(1-alpha-k)^8*X4(j));
X1(j+1)=0.5*m*beta*(1-alpha-0.42*k)^8*X3(j)+m*beta*(1-alpha-k)^8*X4(j);
X2(j+1)=(1-alpha)^12*X1(j+1);
X3(j+1)=(1-alpha)^12*X2(j+1);
X4(j+1)=(1-alpha)^4*(1-alpha-0.42*k)^8*X3(j+1)+(1-alpha)^4*(1-alpha-k)^8*X4(j);
%%
if norm(X1(j+1)-X1(j))<=error&&norm(X2(j+1)-X2(j))<=error&&norm(X3(j+1)-X3(j))<=error&&norm(X4(j+1)-X4(j))<=error
    target=j+1;
    break;
end
target=j+1;
%%
end
f_k(t)=0.42*k*(1-(1-alpha-0.42*k)^8)/(alpha+0.42*k)*X3(target)+k*(1-(1-alpha-k)^8)/(alpha+k)*X4(target);
end
 
k=0.5:error:1;
plot(k,f_k);
[f_max I]=max(f_k);
 
k=k(I)
 for j=1:1:run
beta=1.22e11/(1.22e11+0.5*m*(1-alpha-0.42*k)^8*X3(j)+m*(1-alpha-k)^8*X4(j));
X1(j+1)=0.5*m*beta*(1-alpha-0.42*k)^8*X3(j)+m*beta*(1-alpha-k)^8*X4(j);
X2(j+1)=(1-alpha)^12*X1(j+1);
X3(j+1)=(1-alpha)^12*X2(j+1);
X4(j+1)=(1-alpha)^4*(1-alpha-0.42*k)^8*X3(j+1)+(1-alpha)^4*(1-alpha-k)^8*X4(j);
%%
if norm(X1(j+1)-X1(j))<=error&&norm(X2(j+1)-X2(j))<=error&&norm(X3(j+1)-X3(j))<=error&&norm(X4(j+1)-X4(j))<=error
    target=j+1;
    break;
end
target=j+1;
%%
end
X1(target)
X2(target)
X3(target)
X4(target)
f_max
