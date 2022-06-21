clear
clc
close all
p= imread('²¨¶àÀè¸÷.jpg');
m=p(:,:,2);
rows=size(m,1);
column=size(m,2);
for n=1:rows
    for k=1:column
        if m(n,k)>=200
            m(n,k)=255;
        end
    end
end
precision=5;
for i=1:fix(rows/precision)
    m(i*precision,:)=0;
end
for j=1:fix(column/precision)
    m(:,precision*j)=0;
end
M=[];
Q=0;
T=zeros(fix(rows/precision),fix(column/precision));
for i=1:fix(rows/precision)
    for j=1:fix(column/precision)   
        k=sum(m(((i-1)*precision+1):i*precision,((j-1)*precision+1):j*precision));
        k=sum(k);
        M=[M k];
        if k<(precision-1)*(precision-1.5)*255   
            m(((i-1)*precision+1):i*precision,((j-1)*precision+1):j*precision)=0;
            Q=Q+1;
            T(i,j)=1;
        end
    end
 end
imshow(m);