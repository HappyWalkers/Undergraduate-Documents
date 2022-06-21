close
clear
clc

N = 20000;
k1 = 0;
k2 = 0;
k3 = 0;

for i=1:N
    i;
    R1 = rand(1,1);
    if R1<=0.5
        R2=rand(1,1);
        if R2<=3/6
            k1=k1+1;
        elseif R2<5/6
            k2=k2+1;
        else
            k3=k3+1;
        end
    else
        k1=k1+1;
    end
end

E=(k2+k3)/N
E1=(0*k1+1*k2+2*k3)/N

