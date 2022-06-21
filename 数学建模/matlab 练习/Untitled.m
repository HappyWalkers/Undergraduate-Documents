tic
a=['I''m A STUDENT'];
k=1;
while k<=length(a)
    if a(k)<='Z' & a(k)>='A'
        a(k)=a(k)+32;
    end
    k=k+1;
end
toc