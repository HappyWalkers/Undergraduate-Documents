function [detrend_data,detrend_deT_data] = Detrend_plot(vector,T)
    subplot(3,1,1)
    plot(1:length(vector),vector,'k')
    hold on
    plot(0:length(vector),mean(vector)*ones(1,length(0:length(vector))),'r')
    text(1,mean(vector),'均值')
    legend('趋势','均值')
    title('原开户数据趋势')
    % 去趋势项
    detrend_data = diff(vector,1);
    subplot(3,1,2)
    plot(1:length(detrend_data),detrend_data,'k')
    hold on
    plot(0:length(detrend_data),mean(detrend_data)*ones(1,length(0:length(detrend_data))),'r')
    legend('趋势','均值')
    title('去除趋势项后趋势')
    % 去季节项
    detrend_deT_data = zeros(length(detrend_data),1);
    for i=1:length(detrend_data)
        if(i<=T)
            detrend_deT_data(i) = [];
        else
            detrend_deT_data(i) = detrend_data(i)-detrend_data(i-T);
        end
    end
    subplot(3,1,3)
    plot(1:length(detrend_deT_data),detrend_deT_data,'k')
    hold on
    plot(0:length(detrend_deT_data),mean(detrend_deT_data)*ones(1,length(0:length(detrend_deT_data))),'r')
    legend('趋势','均值')
    title('去除趋势项后和季节项后趋势')
end
