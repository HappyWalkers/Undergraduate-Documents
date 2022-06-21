function [AIC,BIC] = calu_AIC_BIC(p,q,N,residual_var)
AIC = log(residual_var)+2*(p+q+1)/N;
BIC = log(residual_var)+log(N)*(p+q+1)/N;
end
