function y=anglek(kap,a,kap0)
kap0(1)=x0;kap0(2)=y0;
kap(2)=xp;kap(3)=yp;
xa=a(1);ya=a(2);
k1=(y0-ya)/(x0-xa);
k2=(yp-ya)/(xp-xa);

if yp>y0
    ca=1;
elseif yp<y0
    ca=0;
else
    if y0>ya
        if xp<x0
            ca=1;
        else
            ca=0;
        end
    else
        if xp<x0
            ca=0;
        else
            ca=1;
        end
    end
end

switch ca
case 0
    y=(k1-k2)/sqrt(1+k1*k2);
case 1
    y=(k2-k1)/sqrt(1+k1*k2);
end

    
<i