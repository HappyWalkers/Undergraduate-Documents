clearvars
%% ��ȡ���ݲ�Ԥ����
open_nums = xlsread('�ƶ�֪ͨ��������.xlsx',1,'B2:B732');
%% ������ƽ��������ƽ������ƽ������ͼ�����ڹ���,�������쳣ֵ
figure(1),[months_mean,seasons_mean,years_mean,month_starts,month_ends,season_starts,season_ends] = Calu_mean(open_nums);
[m,n] = find(abs(open_nums-mean(open_nums))>2*std(open_nums));
open_nums(m) = mean(open_nums);
%% ���Խ���ȥ���ƺ�ȥ����,���ǵ����ڶ������ڣ�����ݷֿ�������Ϊ����ȥ�����ڣ�����ÿ��Ϊ�������������ֱ�ͬ��
data_2012 = open_nums(1:366);
data_2013 = open_nums(367:end);
figure(2),[detrend_data2012,detrend_deT_data2012] = Detrend_plot(data_2012,30);% 2012�������仯����
figure(3),[detrend_data2013,detrend_deT_data2013] = Detrend_plot(data_2013,31);% 2013�������仯����
figure(4),[detrend_data,detrend_deT_data] = Detrend_plot(open_nums,30);% 2012-2013�������仯����
figure(5),subplot(411),autocorr(open_nums),title('ԭ���������ͼ')% �����ͼ����
subplot(412),autocorr(detrend_data),title('2012������������ͼ')
subplot(413),autocorr(detrend_deT_data2013),title('2013������������ͼ')
subplot(414),autocorr(detrend_deT_data),title('2012-2013������������ͼ')
clearvars month_starts month_ends season_starts season_ends data_2012 data2013
%% ƽ������ȥ��ֵ��Ϊ���ֵƽ������
zeromean_detrend_deT_data = detrend_deT_data-mean(detrend_deT_data);
[unbiased_autocorr,biased_autocorr] = my_autocorr(zeromean_detrend_deT_data);
%% ����ƫ��غ���
[customed_parcorr] = my_parcorr(zeromean_detrend_deT_data,biased_autocorr);