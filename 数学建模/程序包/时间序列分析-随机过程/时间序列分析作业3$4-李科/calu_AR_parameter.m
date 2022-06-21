function [fine] = calu_AR_parameter(seta,I,p,q)
fine = ones(1,p);
for ii = 1:p
    if ii>q
        seta(ii) = 0;
    end
    fine(ii) = seta(ii)+I(ii);
    for jj = 1:ii-1
        if (ii-jj)>0
            fine(ii) = fine(ii)-seta(jj)*I(ii-jj);
        end
    end
end



