function dy=vdpMod(t,y,a)
dy=zeros(2,1);
dy(1)=y(2);
dy(2)=a*(1-y(1)^2)*y(2)-y(1);