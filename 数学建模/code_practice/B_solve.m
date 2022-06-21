clear
close all
clc

load('hos_dis');
rico=imread('波多黎各.jpg');

a=rico(:,:,1);
b=rico(:,:,2);
c=rico(:,:,3);

m=size(a,1);
n=size(a,2);

hos1=[45,598];
hos2=[239,1302];
hos3=[78,1151];
hos4=[30,1237];
hos5=[113,1657];

xi=4/7;% xi是系数
D=64*35/60*0.7;%0.7是假设系数%单位: km
sum_dis=1000000*ones(1,1000000);
best_po=zeros(2,1000000);
lamda_line=max(dist)/dis(hos1,hos5);%单位：千米/点
save('lamda_line','lamda_line');
k=1;

for i=1:m%遍历图上所有点，找出符合条件的点
    for j=1:n
        best=[i,j];% best is the right point
        x2=dis(best,hos2);%单位: 点
        x3=dis(best,hos3);
        x4=dis(best,hos4);
        x2=lamda_line*x2;%单位：米
        x3=lamda_line*x3;
        x4=lamda_line*x4;
        max_x=[x2+x3,x2+x4,x3+x4];
        
        switch max(max_x)
            case x2+x3
                if xi*x2+x4<=D && xi*x4+x3<=D && xi*x3+x4<=D && xi*x4+x2<=D
                    sum_dis(k)=x2+x3+x4;
                    best_po(1,k)=best(1);
                    best_po(2,k)=best(2);
                    k=k+1;
                end
            case x2+x4
                if xi*x2+x3<=D && xi*x3+x4<=D && xi*x4+x3<=D && xi*x3+x2<=D
                    sum_dis(k)=x2+x3+x4;
                    best_po(1,k)=best(1);
                    best_po(2,k)=best(2);
                    k=k+1;
                end
            case x3+x4
                if xi*x3+x2<=D && xi*x2+x4<=D && xi*x4+x2<=D && xi*x2+x3<=D
                    sum_dis(k)=x2+x3+x4;
                    best_po(1,k)=best(1);
                    best_po(2,k)=best(2);
                    k=k+1;
                end
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
save('min_point','min_point');
x2_fina=lamda_line*dis(min_point,hos2);%单位：km
x3_fina=lamda_line*dis(min_point,hos3);
x4_fina=lamda_line*dis(min_point,hos4);
t2=x2_fina/64*60;%单位：分钟
t3=x3_fina/64*60;
t4=x4_fina/64*60;



