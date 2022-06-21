xb=0;yb=1300;xc=0;yc=2600;
for l=3:0.1:5
    EB=0;EC=0;
    for z0=0:0.1:21.6
        for x0=(-sqrt(60*z0):0.1:sqrt(60*z0))
            y0=sqrt(60*z0-x0^2);
            for b=-l/2:0.1:l/2
                if cosa(x0,y0,z0,b)==cosb(x0,y0,z0,xb,yb)
                    EB=EB+dE(x0,y0,z0,b);
                end
                if cosa(x0,y0,z0,b)==cosb(x0,y0,z0,xc,yc)
                    EC=EC+dE(x0,y0,z0,b);
                end
            end
        end
    end
    if EB>=2*EC
        break;
    end
end

        <i