startp=[0,800];endp=[4000,2000];
unit=100;bb=0.125;%bb为坡度
n=1;
a(n,:)=startp;
while 1
    if a(n,:)==endp;
        break;
    end
    xx=unit*(fix(a(n,1)/unit)+1);
    if rem(a(n,2)/unit,1)~=0
        if fix(a(n,2)/unit)==fix(linex(xx,a(n,:),endp)/unit)
            x0=xx;y0=linex(xx,a(n,:),endp);
        elseif fix(a(n,2)/unit)<fix(linex(xx,a(n,:),endp)/unit)
            y0=unit*(fix(a(n,2)/unit)+1);x0=liney(y0,a(n,:),endp);
        else
            y0=unit*fix(a(n,2)/unit);x0=liney(y0,a(n,:),endp);
        end
        z0=griddata(X,Y,z,x0,y0,'cubic');
        if isnan(z0)
            z0=griddata(xi,yi,zi,x0,y0,'cubic');
        end
        za=griddata(X,Y,z,a(n,1),a(n,2),'cubic');
        if isnan(za)
            za=griddata(xi,yi,zi,a(n,1),a(n,2),'cubic');
        end
        k=(z0-za)/sqrt((x0-a(n,1)).^2+(y0-a(n,2)).^2);
        if abs(k)<=bb
            n=n+1;a(n,:)=[x0,y0];
        else
            p=zeros(31,2);ylow=unit*fix(a(n,2)/unit);yup=ylow+unit;
            p(1,:)=[a(n,1),yup];
            for i=1:10
                p(1+i,:)=[a(n,1)+i*unit/10,yup];
            end
            for i=1:10
                p(11+i,:)=[a(n,1)+unit,yup-i*unit/10];
            end
            for i=1:10
                p(21+i,:)=[a(n,1)+unit-i*unit/10,ylow];
            end
            xp=p(:,1);yp=p(:,2);
            
            
            
            zp=griddata(X,Y,z,xp,yp,'cubic');
            %zp中可能出现nan
            
            
            kp=(zp-za)./sqrt((xp-a(n,1)).^2+(yp-a(n,2)).^2);
            kap=[];kn=0;%kap存放坡度小于bb的点，kn为kap的大小
            for i=1:31
                    if n==1
                        if abs(kp(i))<=bb
                            kn=kn+1;kap(kn,1)=kp(i);kap(kn,2)=xp(i);kap(kn,3)=yp(i);
                        end
                    else
                        if abs(kp(i))<=bb&(xp(i)~=a(n-1,1)|yp(i)~=a(n-1,2))
                            kn=kn+1;kap(kn,1)=kp(i);kap(kn,2)=xp(i);kap(kn,3)=yp(i);
                        end
                    end
            end
            if kn==0
                break;
            else
                bk=inf;
                kap0=[x0,y0];
                for i=1:kn
                    if bk==inf
                        bk=kap(i,1);
                    end
                    if kap(i,1)>=0&bk>=0
                        bk=min(kap(i,1),bk);
                    elseif kap(i,1)>=0&bk<0
                        bk=kap(i,1);
                    elseif bk>=0&kap(i,1)<0
                        bk=bk;
                    else 
                        bk=max(kap(i,1),bk);
                    end
                end
            end
            for i=1:31
                if bk==kp(i)
                    break;
                end
            end
            n=n+1;a(n,:)=p(i,:);
        end
    else
        if a(n,2)==0
            downexist=0;
        else
            downexist=1;
        end
        if downexist==0
            if fix(a(n,2)/unit)==fix(linex(xx,a(n,:),endp)/unit)
               x0=xx;y0=linex(xx,a(n,:),endp);
            elseif fix(a(n,2)/unit)<fix(linex(xx,a(n,:),endp)/unit)
               y0=fix(a(n,2)+1)*unit;x0=liney(y0,a(n,:),endp);
            end
           z0=griddata(X,Y,z,x0,y0,'cubic');
           if isnan(z0)
            z0=griddata(xi,yi,zi,x0,y0,'cubic');
        end
        za=griddata(X,Y,z,a(n,1),a(n,2),'cubic');
        if isnan(za)
               za=griddata(xi,yi,zi,a(n,1),a(n,2),'cubic');
           end
            k=(z0-za)/sqrt((x0-a(n,1)).^2+(y0-a(n,2)).^2);
            if abs(k)<=bb
                n=n+1;a(n,:)=[x0,y0];
            else
                p=zeros(21,2);xl=unit*fix(a(n,1)/unit);xr=xl+unit;
                p(1,:)=[xl,a(n,2)+unit];
                for i=1:10
                    p(1+i,:)=[xl+i*unit/10,a(n,2)+unit];
                end
                for i=1:10
                    p(11+i,:)=[xr,a(n,2)+unit-i*unit/10];
                end
                xp=p(:,1);yp=p(:,2);
                
                
                zp=griddata(X,Y,z,xp,yp,'cubic');
                
                
                kp=(zp-za)./sqrt((xp-a(n,1)).^2+(yp-a(n,2)).^2);
                kap=[];kn=0;%kap存放坡度小于bb的点，kn为kap的大小
                for i=1:21
                    if n==1
                        if abs(kp(i))<=bb
                            kn=kn+1;kap(kn,1)=kp(i);kap(kn,2)=xp(i);kap(kn,3)=yp(i);
                        end
                    else
                        if abs(kp(i))<=bb&(xp(i)~=a(n-1,1)|yp(i)~=a(n-1,2))
                            kn=kn+1;kap(kn,1)=kp(i);kap(kn,2)=xp(i);kap(kn,3)=yp(i);
                        end
                    end
                end
                if kn==0
                   break;
                else
                    bk=inf;
                    kap0=[x0,y0];
                    for i=1:kn
                        if bk==inf
                           bk=kap(i,1);
                        end
                        if kap(i,1)>=0&bk>=0
                          bk=min(kap(i,1),bk);
                        elseif kap(i,1)>=0&bk<0
                                bk=kap(i,1);
                        elseif bk>=0&kap(i,1)<0
                             bk=bk;
                        else 
                          bk=max(kap(i,1),bk);
                        end
                    end
                end
                for i=1:21
                    if bk==kp(i)
                       break;
                    end
                end
                n=n+1;a(n,:)=p(i,:);
            end
        else
            if fix(a(n,2)/unit)==fix(linex(xx,a(n,:),endp)/unit)
               x0=xx;y0=linex(xx,a(n,:),endp);
            elseif fix(a(n,2)/unit)<fix(linex(xx,a(n,:),endp)/unit)
               y0=a(n,2)+unit;x0=liney(y0,a(n,:),endp);
           elseif fix(a(n,2)/unit)==fix(linex(xx,a(n,:),endp)/unit)+1
               x0=xx,;y0=linex(xx,a(n,:),endp);
           else
               y0=a(n,2)-unit;x0=liney(y0,a(n,:),endp);
           end
           z0=griddata(X,Y,z,x0,y0,'cubic');
           if isnan(z0)
               z0=griddata(xi,yi,zi,x0,y0,'cubic');
           end
           za=griddata(X,Y,z,a(n,1),a(n,2),'cubic');
           if isnan(za)
              za=griddata(xi,yi,zi,a(n,1),a(n,2),'cubic');
           end
            k=(z0-za)/sqrt((x0-a(n,1))^2+(y0-a(n,2))^2);
            if abs(k)<=bb
                n=n+1;a(n,:)=[x0,y0];
            else
                p=zeros(41,2);xl=unit*fix(a(n,1)/unit);xr=xl+unit;
                p(1,:)=[xl,a(n,2)+unit];
                for i=1:10
                    p(1+i,:)=[xl+i*unit/10,a(n,2)+unit];
                end
                for i=1:20
                    p(11+i,:)=[xr,a(n,2)+unit-i*unit/10];
                end
                for i=1:10
                    p(31+i,:)=[xr-i*unit/10,a(n,2)-unit];
                end
                xp=p(:,1);yp=p(:,2);
                
                
                zp=griddata(X,Y,z,xp,yp,'cubic');
                
                
                kp=(zp-za)./sqrt((xp-a(n,1)).^2+(yp-a(n,2)).^2);
                kap=[];kn=0;%kap存放坡度小于bb的点，kn为kap的大小
                for i=1:41
                    if n==1
                        if abs(kp(i))<=bb
                            kn=kn+1;kap(kn,1)=kp(i);kap(kn,2)=xp(i);kap(kn,3)=yp(i);
                        end
                    else
                        if abs(kp(i))<=bb&(xp(i)~=a(n-1,1)|yp(i)~=a(n-1,2))
                            kn=kn+1;kap(kn,1)=kp(i);kap(kn,2)=xp(i);kap(kn,3)=yp(i);
                        end
                    end
                end
                if kn==0
                   break;
                else
                    bk=inf;
                    kap0=[x0,y0];
                    for i=1:kn
                      if bk==inf
                        bk=kap(i,1);
                      end
                      if kap(i,1)>=0&bk>=0
                        bk=min(kap(i,1),bk);
                      elseif kap(i,1)>=0&bk<0
                        bk=kap(i,1);
                      elseif bk>=0&kap(i,1)<0
                        bk=bk;
                      else 
                        bk=max(kap(i,1),bk);
                      end
                    end
                end
                for i=1:41
                    if bk==kp(i)
                        break;
                    end
                end
                n=n+1;a(n,:)=p(i,:);
            end
        end
    end
end
disp(a);

               
       
                <i