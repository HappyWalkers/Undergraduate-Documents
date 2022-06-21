clear all
clc
PS=imread('1.jpg'); 
subplot(1,2,1);
imshow(PS)                                             
title('原图')
p=rgb2gray(PS);
subplot(1,2,2)
imshow(p)
title('原灰度图')

[m,n]=size(p);  
GP=zeros(1,256);       
for k=0:255
GP(k+1)=length(find(p==k))/(m*n);  
end
figure
subplot(1,2,1);
bar(0:255,GP,'g')                          
title('原灰度直方图')

max_index=[];
for i=3:length(GP)-2
if((GP(i)>=GP(i+1))&(GP(i)>=GP(i-1)))&((GP(i+1)>=GP(i+2))&(GP(i-1)>=GP(i-2)))
max_index(end+1)=i-1;
end
end
possible=GP(max_index);
[max_value,index]=max(possible);
TT=max_index(index)-2;

[m,n]=size(p);
R=zeros(m,n);
for i=1:m
    for j=1:n
        if p(i,j)<TT
           R(i,j)=0;
        else R(i,j)=256;
        end
    end
end
subplot(1,2,2);
imshow(R);
title('二值图');
