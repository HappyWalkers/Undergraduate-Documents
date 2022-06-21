%function lightpoint=beam(l)
function lightpoint=beam(l)
step=0.5;
lightpoint=[];nlp=0;
z0=0;
while z0<=21.6
    x0=-sqrt(60*z0);
    while x0<=sqrt(60*z0)
        y0=sqrt(60*z0-x0^2)
        b=-l/2;
        while b<=l/2
            [x,y]=pannel(x0,y0,z0,b);
            nlp=nlp+1;
            lightpoint(nlp,1:2)=[x,y];
            b=b+step;
        end
        y0=-sqrt(60*z0-x0^2)
        b=-l/2;
        while b<=l/2
            [x,y]=pannel(x0,y0,z0,b);
            nlp=nlp+1;
            lightpoint(nlp,1:2)=[x,y];
            b=b+step;
        end
        x0=x0+step;
    end
    z0=z0+step;
end
<i