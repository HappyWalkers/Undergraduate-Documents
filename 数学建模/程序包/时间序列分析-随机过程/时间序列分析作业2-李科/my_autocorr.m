function [unbiased_autocorr,biased_autocorr] = my_autocorr(time_vector)
%% 函数定义,计算无偏和有偏两种自相关系数
n = length(time_vector);
unbiased_autocorr = zeros(n,1);
biased_autocorr = zeros(n,1);
% 延迟期数从0到n
for h = 0:n
    omega = 0;
    % 累加从t=1到n-h
    for t = 1:n-h
        omega = omega+time_vector(t)*time_vector(t+h);
    end
    unbiased_autocorr(h+1) = omega/(n-h);
    biased_autocorr(h+1) = omega/n;
end
% 自相关函数转换为自相关系数
unbiased_autocorr = unbiased_autocorr/unbiased_autocorr(1);
biased_autocorr = biased_autocorr/biased_autocorr(1);
%% 绘图比较
n_compare = 30;
figure()
subplot(311) 
plot(0:n_compare-1,unbiased_autocorr(1:n_compare),'ro','MarkerFaceColor','r','markersize',4)
hold on,plot(0:n_compare-1,zeros(1,n_compare),'b')
title('无偏自相关系数变化'),xlabel('延迟天数'),ylabel('自相关系数')
subplot(312) 
plot(0:n_compare-1,biased_autocorr(1:n_compare),'ro','MarkerFaceColor','r','markersize',4)
hold on,plot(0:n_compare-1,zeros(1,n_compare),'b')
title('有偏自相关系数变化'),xlabel('延迟天数'),ylabel('自相关系数')
subplot(313) 
autocorr(time_vector,n_compare),title('内置autocorr结果')
