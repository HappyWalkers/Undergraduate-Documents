clear
close all
clc
%% preparation
rico=imread('�������_��.jpg');
a=rico(:,:,1);
b=rico(:,:,2);
c=rico(:,:,3);

m=size(a,1);
n=size(a,2);

hos_y=[45 78 30 239 113];
hos_x=[598 1151 1237 1302 1657];

%% ��ɫ
for i=1:m
    for j=1:n
  
        if a(i,j)<200 && b(i,j)<200 && c(i,j)<200%��ɫ��·�߸�Ϊ��ɫ������Ϊ��ɫ
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

% %% �޲�
% fw=50;%������Χ
% for i=1:m
%     for j=1:n
%         if a(i,j)==0%��Ϊ�ڵ�
%             
%             if a(i-1,j-1)>0 && a(i-1,j)>0 && a(i-1,j+1)>0 && a(i,j-1)>0 ...
%                 && a(i,j+1)>0 && a(i+1,j-1)>0 && a(i+1,j)>0 && a(i+1,j+1)>0%���߶�
%             a(i,j)=0;
%             if i-fw<1
%                 x_l=1;
%             else
%                 x_l=i-fw;
%             end
%             
%             if i+fw>m
%                 x_r=m;
%             else
%                 x_r=i+fw;
%             end
%             
%             if j-fw<1
%                 y_l=1;
%             else
%                 y_l=j-fw;
%             end
%             
%             if j+fw>n
%                 y_r=n;
%             else 
%                 y_r=j+fw;
%             end
%             
%             for ii=x_l:x_r
%                 for jj=y_l:y_r%������Χ50�Ƿ��кڵ�
%                     if a(ii,jj)==0
%                         A=a(i:ii,j:jj);
%                         A( logical(eye(size(A))))=0;%����
%                         a(i:ii,j:jj)=A;
%                         B=b(i:ii,j:jj);
%                         B( logical(eye(size(B))))=0;
%                         b(i:ii,j:jj)=B;
%                         C=c(i:ii,j:jj);
%                         C( logical(eye(size(C))))=0;
%                         c(i:ii,j:jj)=C;
%                     end
%                 end
%             end
%             end
%             
%         end
%     end
% end

%% plot
new_rico(:,:,1)=a;
new_rico(:,:,2)=b;
new_rico(:,:,3)=c;
imshow(new_rico);%ͼ�У���Ϊx����Ϊy�������еߵ�

text(hos_x,hos_y,'o','color','r');
text(1209,78,'o','color','g');
imwrite(new_rico,'�������_ԭʼ.jpg','jpg');

save('a','a');
save('hos_x','hos_x');
save('hos_y','hos_y');
