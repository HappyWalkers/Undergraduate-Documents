clc
clear
T=xlsread('T.xlsx')
S=113.990;
n=91;
Save=S/n;
Sd=39.5/2;
r=Sd/Save;
re=[];
maxsum=0;
suum=[];
for i=3:1:15
    for j=3:30
        if sqrt((4-i)^2+(4-j)^2)>r
            continue
        else
            ymin=max(1,ceil(i-r));
            ymax=min(30,floor(i+r));
            xmin=max(1,ceil(j-r));
            xmax=min(97,floor(j+r));
            sum=0;
            for p=ymin:ymax
                for q=xmin:xmax
                    sum=sum+T(p,q);
                end
            end
            suum=[suum sum];
            if sum>=maxsum
                maxsum=sum;
                re=[i,j,sum]
            end
        end
    end
end