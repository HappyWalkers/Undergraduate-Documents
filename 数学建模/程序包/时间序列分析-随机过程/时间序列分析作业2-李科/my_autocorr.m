function [unbiased_autocorr,biased_autocorr] = my_autocorr(time_vector)
%% ��������,������ƫ����ƫ���������ϵ��
n = length(time_vector);
unbiased_autocorr = zeros(n,1);
biased_autocorr = zeros(n,1);
% �ӳ�������0��n
for h = 0:n
    omega = 0;
    % �ۼӴ�t=1��n-h
    for t = 1:n-h
        omega = omega+time_vector(t)*time_vector(t+h);
    end
    unbiased_autocorr(h+1) = omega/(n-h);
    biased_autocorr(h+1) = omega/n;
end
% ����غ���ת��Ϊ�����ϵ��
unbiased_autocorr = unbiased_autocorr/unbiased_autocorr(1);
biased_autocorr = biased_autocorr/biased_autocorr(1);
%% ��ͼ�Ƚ�
n_compare = 30;
figure()
subplot(311) 
plot(0:n_compare-1,unbiased_autocorr(1:n_compare),'ro','MarkerFaceColor','r','markersize',4)
hold on,plot(0:n_compare-1,zeros(1,n_compare),'b')
title('��ƫ�����ϵ���仯'),xlabel('�ӳ�����'),ylabel('�����ϵ��')
subplot(312) 
plot(0:n_compare-1,biased_autocorr(1:n_compare),'ro','MarkerFaceColor','r','markersize',4)
hold on,plot(0:n_compare-1,zeros(1,n_compare),'b')
title('��ƫ�����ϵ���仯'),xlabel('�ӳ�����'),ylabel('�����ϵ��')
subplot(313) 
autocorr(time_vector,n_compare),title('����autocorr���')
