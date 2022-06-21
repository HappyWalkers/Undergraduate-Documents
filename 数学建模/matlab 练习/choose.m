function newpop=choose(pop,fitvalue,objvalue,pm)
%构造轮盘
[px,py,c] = size(pop);
p_fitvalue = fitvalue/objvalue;
p_fitvalue = cumsum(p_fitvalue);%概率求和排序
ms = sort(rand(px,1));%从小到大排列
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