function newpop=choose(pop,fitvalue,objvalue,pm)
%��������
[px,py,c] = size(pop);
p_fitvalue = fitvalue/objvalue;
p_fitvalue = cumsum(p_fitvalue);%�����������
ms = sort(rand(px,1));%��С��������
fitin = 1;
newin = 1;
while newin<=px
    if(ms(newin))<p_fitvalue(fitin)
        mutation(pop,pm);
         fitin=fitin+1;
         if fitin>px
             break
         end
    else
        newpop(newin,:)=pop(fitin,:);
        newin = newin+1;
    end
end