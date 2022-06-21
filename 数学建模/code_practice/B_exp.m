clear
close all
clc

rico=imread('波多黎各.jpg');

a=rico(:,:,1);
b=rico(:,:,2);
c=rico(:,:,3);

m=size(a,1);
n=size(a,2);

hos2=[1151,78];
hos3=[1237,30];
hos4=[1302,239];


D=64*35*0.7;%0.7是假设系数
sum_dis=1000000*ones(1,1000000);
best_po=zeros(2,1000000);
k=1;

for i=1:m%遍历图上所有点，找出符合条件的点
    for j=1:n
        best=[i,j];% best is the right point
        x2=dis(best,hos2);
        x3=dis(best,hos3);
        x4=dis(best,hos4);
        
        if x2<=D/2 && x3<=D/2 && x4<=D/2
            sum_dis(k)=x2+x3+x4;
            best_po(1,k)=best(1);
            best_po(2,k)=best(2);
            k=k+1;
        end
        
    end
end

min_dis=max(sum_dis);
min_point=[0,0];
for i=1:length(sum_dis)
    if sum_dis(i)<=min_dis
        min_dis=sum_dis(i);
        min_point(1)=best_po(1,i);
        min_point(2)=best_po(2,i);
    end
end

fprintf("the coordinate of the best point is:");
disp(min_point);








