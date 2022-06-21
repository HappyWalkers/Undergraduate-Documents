clear
close all
clc

rico=imread('Inked波多黎各_LI.jpg');

a=rico(:,:,1);
b=rico(:,:,2);
c=rico(:,:,3);

m=size(a,1);
n=size(a,2);

for i=1:m
    for j=1:n
        
%         if a(i,j)>200 && b(i,j)<100 && c(i,j)<100
%             annotation('arrow',[(i+50)/m,i/m],[(j+50)/n,j/n]);
%         end
        
        if a(i,j)>200 && b(i,j)<200 && c(i,j)<200%红色的点改为白色，其他为黑色
%             fprintf("the possible points of the hospitals are:(%d,%d)\n ",i,j);
            a(i,j)=255;
            b(i,j)=255;
            c(i,j)=255;
        else
            a(i,j)=0;
            b(i,j)=0;
            c(i,j)=0;
        end
       
    end
end

new_rico(:,:,1)=a;
new_rico(:,:,2)=b;
new_rico(:,:,3)=c;
imshow(new_rico);