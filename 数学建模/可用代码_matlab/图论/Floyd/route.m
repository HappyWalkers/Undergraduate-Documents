% floyd Ëã·¨´úÂë
clear
close all
clc
d=[inf 6 0 4 0 0 0
   0 inf 0 0 5 0 0
   4 7 inf 0 0 5 0
   0 0 4 inf 0 3 0
   0 0 2 0 inf 0 0
   0 0 0 0 4 inf 5
   0 0 0 0 6 0 inf];
[m,n]=size(d);
first=1;
last=7;
direction=zeros(m,m);
for i=1:m
    direction(:,i)=i;
end
for i=1:m
    for j=1:m
        for k=1:m
            small=min(d(i,k),d(k,j));
            if d(i,j)<small
                d(i,j)=small;
                direction(i,j)=direction(i,k);
            end
        end
    end
end
arrow=zeros(1,m);
arrow(1)=first;
i=2;
p=first;
while p~=last
    p=direction(p,last);
    arrow(i)=p;
    i=i+1;
end


