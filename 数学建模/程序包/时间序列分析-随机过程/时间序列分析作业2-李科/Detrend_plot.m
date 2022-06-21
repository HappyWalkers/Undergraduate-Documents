function [detrend_data,detrend_deT_data] = Detrend_plot(vector,T)
    subplot(3,1,1)
    plot(1:length(vector),vector,'k')
    hold on
    plot(0:length(vector),mean(vector)*ones(1,length(0:length(vector))),'r')
    text(1,mean(vector),'��ֵ')
    legend('����','��ֵ')
    title('ԭ������������')
    % ȥ������
    detrend_data = diff(vector,1);
    subplot(3,1,2)
    plot(1:length(detrend_data),detrend_data,'k')
    hold on
    plot(0:length(detrend_data),mean(detrend_data)*ones(1,length(0:length(detrend_data))),'r')
    legend('����','��ֵ')
    title('ȥ�������������')
    % ȥ������
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
    legend('����','��ֵ')
    title('ȥ���������ͼ����������')
end
