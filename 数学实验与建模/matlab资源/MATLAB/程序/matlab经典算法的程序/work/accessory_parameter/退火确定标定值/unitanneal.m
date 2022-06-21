%function x=unitanneal(L,s,t,dt,x,lb,ub)
%x为标定值，lb为下界，ub为上界
function x=unitanneal(L,s,t,dt,x,lb,ub)
s0=0;
while 1
    a=0;
    for k=1:L
        newx=generatenew(x,lb,ub);
        df=accyouhua(newx)-accyouhua(x);
        if accept(t,df)
            x=newx,a=1;
        end
    end
    t=t*dt
    if a==0
        s0=s0+1;
    else 
        s0=0;
    end
    if s0==s
        break;
    end
end
<i