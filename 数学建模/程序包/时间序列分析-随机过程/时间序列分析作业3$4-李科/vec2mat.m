function [autocorr_matrix] = vec2mat(autocorr_vector)
n = length(autocorr_vector);
autocorr_matrix = zeros(n);
for ii = 1:n
    autocorr_matrix(ii,ii:n) = autocorr_vector(1:n-ii+1);
end
autocorr_matrix = triu(autocorr_matrix)+tril(autocorr_matrix',-1);
end
