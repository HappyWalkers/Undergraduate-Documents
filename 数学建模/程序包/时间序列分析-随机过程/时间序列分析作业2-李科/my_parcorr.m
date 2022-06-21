function [customed_parcorr] = my_parcorr(time_vector,auto_corr)
%% 函数定义
n = length(auto_corr);
customed_parcorr = zeros(n,n);
customed_parcorr(1,1) = auto_corr(2);
for k = 1:n-2
    sum1 = 0;
    sum2 = 0;
    for j = 1:k
        sum1 = sum1 + auto_corr(k+2-j)*customed_parcorr(k,j);
        sum2 = sum2 + auto_corr(j+1)*customed_parcorr(k,j);
    end
    customed_parcorr(k+1,k+1) = (auto_corr(k+2)-sum1)/(1-sum2);
    for j = 1:k
        customed_parcorr(k+1,j) = customed_parcorr(k,j) - customed_parcorr(k+1,k+1)*customed_parcorr(k,k+1-j);
    end
end
%% 绘图比较
a = diag(customed_parcorr);
subplot(211)
compare_n = 30;
parcorr(time_vector,compare_n)
subplot(212)
plot(1:compare_n,a(1:compare_n),'ro','markerfacecolor','r','markersize',4)
hold on,plot(1:compare_n,zeros(1,compare_n),'b')
ylim([-0.5,1])
title('自定义偏相关计算值')
xlabel('延迟天数'),ylabel('偏相关系数')
