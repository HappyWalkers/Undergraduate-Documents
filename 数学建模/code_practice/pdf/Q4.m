function [R_best,L_best,L_ave,Shortest_Route,Shortest_Length]=Q4(C,NC_max,m,Alpha,Beta,Rho,Q)
n=size(C,1);
D=zeros(n,n);
for i=1:n
    for j=1:n
        if i~=j D(i,j)=((C(i,1)-C(j,1))^2+(C(i,2)-C(j,2))^2)^0.5;
        else
            D(i,j)=eps;
        end
        D(j,i)=D(i,j);
    end
end
Eta=1./D;
Tau=ones(n,n);
Tabu=zeros(m,n);
NC=1;
R_best=zeros(NC_max,n);
L_best=inf.*ones(NC_max,1);
L_ave=zeros(NC_max,1);
while NC<=NC_max
    Randpos=[];
    for i=1:(ceil(m/n)) Randpos=[Randpos,randperm(n)];
    end
    Tabu(:,1)=(Randpos(1,1:m))';
    
    
    for j=2:n
        for i=1:m
            visited=Tabu(i,1:(j-1));
            J=zeros(1,(n-j+1));
            P=J;
            Jc=1;
            for k=1:n
                if length(find(visited==k))==0
                    J(Jc)=k;
                    Jc=Jc+1;
                end
            end
            
            for k=1:length(J)
                P(k)=(Tau(visited(end),J(k))^Alpha)*(Eta(visited(end),J(k))^Beta);
            end
            P=P/(sum(P));
            Pcum=cumsum(P);
            Select=find(Pcum>=rand);
            to_visit=J(Select(1));
            Tabu(i,j)=to_visit;
        end
    end
    if NC>=2 Tabu(1,:)=R_best(NC-1,:);
    end
    L=zeros(m,1);
    for i=1:m R=Tabu(i,:);
        for j=1:(n-1)
            L(i)=L(i)+D(R(j),R(j+1));
        end
        L(i)=L(i)+D(R(1),R(n));
    end
    
    
    L_best(NC)=min(L);
    pos=find(L==L_best(NC));
    R_best(NC,:)=Tabu(pos(1),:);
    L_ave(NC)=mean(L);
    NC=NC+1
    
    Delta_Tau=zeros(n,n);
    for i=1:m
        for j=1:(n-1) Delta_Tau(Tabu(i,j),Tabu(i,j+1))=Delta_Tau(Tabu(i,j),Tabu(i,j+1))+Q/L(i);
        end
        Delta_Tau(Tabu(i,n),Tabu(i,1))=Delta_Tau(Tabu(i,n),Tabu(i,1))+Q/L(i);
    end
    Tau=(1-Rho).*Tau+Delta_Tau;
    Tabu=zeros(m,n);
end

Pos=find(L_best==min(L_best));
Shortest_Route=R_best(Pos(1),:)
Shortest_Length=L_best(Pos(1))
figure(1)
DrawRoute(C,Shortest_Route)
figure(2)
plot(L_best)
title('The shortest distance')


