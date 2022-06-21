clear
close all
clc

rico=imread('波多黎各.jpg');

a=rico(:,:,1);
b=rico(:,:,2);
c=rico(:,:,3);

m=size(a,1);
n=size(a,2);

hos4=[78,1151];
hos3=[30,1237];
hos2=[239,1302];

xi=4/7;% xi是系数
D=64*35*0.7;%0.7是假设系数
sum_dis=[];
best_po_x=[];
best_po_y=[];

for i=1:m%遍历图上所有点，找出符合条件的点
    for j=1:n
        best=[i,j];% best is the right point
        x2=dis(best,hos2);
        x3=dis(best,hos3);
        x4=dis(best,hos4);
        max_x=[x2+x3,x2+x4,x3+x4];
        
        switch max(max_x)
            case x2+x3
                if xi*x2+x4<=D && xi*x4+x3<=D && xi*x3+x4<=D && xi*x4+x2<=D
                    sum_dis=[sum_dis x2+x3+x4];
                    best_po_x=[best_po_x best(1)];
                    best_po_y=[best_po_y best(2)];
                end
            case x2+x4
                if xi*x2+x3<=D && xi*x3+x4<=D && xi*x4+x3<=D && xi*x3+x2<=D
                    best_po_x=[best_po_x best(1)];
                    best_po_y=[best_po_y best(2)];
                end
            case x3+x4
                if xi*x3+x2<=D && xi*x2+x4<=D && xi*x4+x2<=D && xi*x2+x3<=D
                    best_po_x=[best_po_x best(1)];
                    best_po_y=[best_po_y best(2)];
                end
        end
        
    end
end

min_dis=max(sum_dis);
min_point=[0,0];
for i=1:length(sum_dis)
    if sum_dis(i)<=min_dis
        min_dis=sum_dis(i);
        min_point(1)=best_po_x(i);
        min_point(2)=best_po_y(i);
    end
end

fprintf("the coordinate of the best point is:");
disp(min_point);