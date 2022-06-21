function Z=accyouhua(x)
x10=x(1);x20=x(2);x30=x(3);x40=x(4);x50=x(5);x60=x(6);x70=x(7);
chengben=[0 25 0;0 50 20;200 50 20;500 100 50;0 0 50;100 25 10;100 25 0];
rongcha=[0.05 0.1 0.1 0.1 0.1 0.1 0.05];
NC=0;NF=0;
for n=1:1000
    x1=normal(x10,(rongcha(1)*x10/3)^2,1);
    x2=normal(x20,(rongcha(2)*x20/3)^2,1);
    x3=normal(x30,(rongcha(3)*x30/3)^2,1);
    x4=normal(x40,(rongcha(4)*x40/3)^2,1);
    x5=normal(x50,(rongcha(5)*x50/3)^2,1);
    x6=normal(x60,(rongcha(6)*x60/3)^2,1);
    x7=normal(x70,(rongcha(7)*x70/3)^2,1);
    y=174.42*(x1/x5)*(x3/(x2-x1))^0.85*sqrt((1-2.62*(1-0.36*(x4/x2)^(-0.56))^1.5*(x4/x2)^1.16)/(x6*x7));
    if (y>=1.2&y<=1.4)|(y>1.6&y<=1.8)
        NC=NC+1;
    end
    if y<1.2|y>1.8
        NF=NF+1;
    end
end
Q=NC+NF*9;
C=0;
for i=1:7
    if rongcha(i)==0.01
        C=C+chengben(i,1);
    end
    if rongcha(i)==0.05
        C=C+chengben(i,2);
    end
    if rongcha(i)==0.1
        C=C+chengben(i,3);
    end
end
Z=Q+C
<i