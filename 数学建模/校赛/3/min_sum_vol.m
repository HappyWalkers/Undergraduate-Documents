function [distance]=min_sum_vol(pRoute,rng,dmat,ifshow)
v=10;
r=0.05;
f=1;
T=0;
data=xlsread("C:\Users\mashed potato\Desktop\校赛\附件2.xlsx");
vi=data(2:end,3);
vi=vi/3600;
dmat=dmat*1000;
distance=0;
for s = 1:4
    d = 0;
    d = d + dmat(1,pRoute(rng(s,1))); % Add Start Distance
    for k = rng(s,1):rng(s,2)-1
        d = d + dmat(pRoute(k),pRoute(k+1));%中间的路程
    end
    d = d + dmat(pRoute(rng(s,2)),1); % Add End Distance
    
    n=rng(s,2)-rng(s,1)+1;
    b=(1-(n-1)/r.*vi(pRoute(rng(s,1):rng(s,2))-1))*f+(d/v+T).*vi(pRoute(rng(s,1):rng(s,2))-1);
    a=zeros(n,n);
    for i=1:n
        temp=vi(pRoute(rng(s,1):rng(s,2))-1);
        a(i,:)=-temp(i)/r;
        a(i,i)=1;
    end
    c=ones(n,1);
    [x,fval]=linprog(c,-a,-b,[],[],[],[],optimset('Display','off') );
% [x,fval]=linprog(c,-a,-b);
    distance=distance+fval;
    if ifshow==1
        x
    end
end
if ifshow==1
    distance
end