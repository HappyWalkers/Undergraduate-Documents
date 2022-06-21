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
%         else
%             m(n,k)=0;
        end
    end
end
imshow(m);