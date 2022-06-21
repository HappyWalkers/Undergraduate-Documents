function [seta]= calu_MA_parameter(I,p,q)
P = max(p,q);
I_matrix = zeros(q,q);
for ii = 1:q
    I_matrix(ii,:) = I(P+ii-1:-1:P+ii-q);
end
seta = I_matrix\I(P+1:P+q);
end


