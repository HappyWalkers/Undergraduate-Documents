sj=[-66.16 18.41;
    -66.25 18.43;
    -66.43 18.45;
    -66.54 18.43;
    -66.68 18.44;];
d1=[-66.30,18.41]; 
sj=[d1;sj;d1]; 
sj=sj*pi/180; 
d=zeros(7);
for i=1:6
    for j=i+1:7 
        temp=cos(sj(i,1)-sj(j,1))*cos(sj(i,2))*cos(sj(j,2))+sin(sj(i,2))*sin(sj(j,2));  
        d(i,j)=6370*acos(temp);     
    end
end
d=d+d';
S0=[];
Sum=inf; 
rand('state',sum(clock));
for j=1:1000  
    S=[1 1+randperm(5),7]; 
    temp=0;
    for i=1:6
        temp=temp+d(S(i),S(i+1));
    end
    if temp<Sum   
        S0=S;Sum=temp; 
    end
end
e=0.1^30;
L=20000;
at=0.999;
T=1; %退火过程 
for k=1:L  
    %产生新解 
    c=2+floor(5*rand(1,2)); 
    c=sort(c);
    c1=c(1);
    c2=c(2);   %计算代价函数值  
    df=d(S0(c1-1),S0(c2))+d(S0(c1),S0(c2+1))-d(S0(c1-1),S0(c1))-d(S0(c2),S0(c2+1));    %接受准则  
    if df<0  
        S0=[S0(1:c1-1),S0(c2:-1:c1),S0(c2+1:7)]; 
        Sum=Sum+df;  
    elseif exp(-df/T)>rand(1)
        S0=[S0(1:c1-1),S0(c2:-1:c1),S0(c2+1:7)];
        Sum=Sum+df;  
    end
    T=T*at;   
    if T<e  
        break;  
    end
end
% 输出巡航路径及路径长度 
S0,Sum
 plot(sj(:,1),sj(:,2),'o')
 plot(sj(S0(1:end),1),sj(S0(1:end),2),'r*-');