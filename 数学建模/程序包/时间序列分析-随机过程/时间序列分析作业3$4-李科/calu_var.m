function [error,residual_var] = calu_var(p,q,fine,seta,N,processed_data)
error = zeros(1,N);
for ii = max(p,q)+1:N
    error(ii) = [1,-fine]*processed_data(ii:-1:ii-p)+seta'*error(ii-1:-1:ii-q)';
end
residual_var = (error*error')/N;
end
    
