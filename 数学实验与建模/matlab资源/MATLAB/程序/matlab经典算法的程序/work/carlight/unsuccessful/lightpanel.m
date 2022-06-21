%请先运行B&C,得到l值，再运行此程序
x=-1:0.05:1;
y=-3:0.05:3;
nx=length(x);
ny=length(y);
light_panel=zeros(nx,ny);
for r=1:nx
    for c=1:ny
        for z0=0:0.1:21.6
            for x0=-sqrt(60*z0):0.1:sqrt(60*z0)
                y0=sqrt(60*z0-x0^2);
                for b=-l/2:0.1:l/2
                    if cosa(x0,y0,z0,b)==cosb(x0,y0,z0,x(r),y(c))
                        light_panel(r,c)=light_panel(r,c)+dE(x0,y0,z0,b);
                    end
                end
            end
        end
    end
end
<i