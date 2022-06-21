function point=mereflect(pop,request)
[a,b,c]=size(pop);
point=ones(a,b,2);
for i=1:a
    for j=1:b
        if j==1||j==2
            x=1;
        elseif j==3||j==4
            x=2;
        elseif j==5||j==6
            x=3;
        elseif j==7||j==8
            x=4;
        end
        m=(i-1)*4+x;
        if j==1||j==3||j==5||j==7
                n1=1;
                n2=2;
        else
                n1=3;
                n2=4;
        end
        n=size(request,1);
        if m>n
            point(i,j,1)=0;
            point(i,j,2)=0;
            continue
        else
            point(i,j,1)=request(m,n1);
            point(i,j,2)=request(m,n2);
        end
    end
end
end

