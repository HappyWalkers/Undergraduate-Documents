function lb = calu_LB(data, m)
N = 120;
power_autocorr = 0;
data_autocorr = autocorr(data,N);
for k=1:m
    power_autocorr = power_autocorr+data_autocorr(k+1)^2/(N-k);
end
lb = N*(N+2)*power_autocorr;
end