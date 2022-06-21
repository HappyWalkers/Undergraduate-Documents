clear all
close all
clc

w = [0   2   1   8   inf inf inf inf;
     2   0   inf 6   1   inf inf inf;
     1   inf 0   7   inf inf 9   inf;
     8   6   7   0   5   1   2   inf;
     inf 1   inf 5   0   3   inf 9;
     inf inf inf 1   3   0   4   6;
     inf inf 9   2   inf 4   0   3;
     inf inf inf inf 9   6   3   0]
n=size(w,1);
w1=w(1,:);

%赋初值
for i=1:n
    l(i)=w1(i);
    z(i)=1;
end
s=[];
s(1)=1;
u=s(1);
k=1
l
z


while k<n
    % 更新 l(v) 和 z(v)
    for i=1:n
        for j=1:k
            if i~=s(j)
                if l(i)>l(u)+w(u,i)
                    l(i)=l(u)+w(u,i);
                    z(i)=u;
                end
            end
        end
    end
    l
    z

    %求v*

    ll = l;
    for i=1:n
        for j=1:k
            if i~=s(j)
                ll(i)=ll(i);
            else
                ll(i)=inf;
            end
        end
    end

    lv=inf;
    for i=1:n
        if ll(i)<lv
            lv=ll(i);
            v=i;
        end
    end
    lv
    v

    s(k+1)=v
    k=k+1
    u=s(k)

end
l
z
