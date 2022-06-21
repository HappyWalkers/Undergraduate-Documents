clear
close all
clc

hos4=[78,1151];
hos3=[30,1237];
hos2=[239,1302];
sum=1000000*ones(3,1000000);
k=1;

for i=1:300
    for j=1:1400
        right=[i,j];
        x2=dis(right,hos2);
        x3=dis(right,hos3);
        x4=dis(right,hos4);
        sum(1,k)=x2+x3+x4;
        sum(2,k)=i;
        sum(3,k)=j;
        k=k+1;
    end
end

[value,point]=min(sum(1,:))


        