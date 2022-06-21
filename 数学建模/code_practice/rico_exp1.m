clear
close all
clc
%% preparation
rico=imread('the path.jpg');
a=rico(:,:,1);
b=rico(:,:,2);
c=rico(:,:,3);

m=size(a,1);
n=size(a,2);

%% 改色
for i=1:m
    for j=1:n
  
        if a(i,j)<185 && a(i,j)>175 && b(i,j)<210 && b(i,j)>200 && c(i,j)>210&& c(i,j)<220%红黑色的路线改为黑色，其他为白色
            a(i,j)=0;
            b(i,j)=0;
            c(i,j)=0;
        else
            a(i,j)=255;
            b(i,j)=255;
            c(i,j)=255;
        end
       
    end
end


%% plot
new_rico(:,:,1)=a;
new_rico(:,:,2)=b;
new_rico(:,:,3)=c;
imshow(new_rico);

% hos_y=[45 78 30 239 113];%医院
% hos_x=[598 1151 1237 1302 1657];
% text(hos_x,hos_y,'o','color','r');
% text(1209,78,'o','color','g');%集装箱
