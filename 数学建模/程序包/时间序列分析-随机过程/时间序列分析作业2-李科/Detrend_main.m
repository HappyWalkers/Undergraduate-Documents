clearvars
%% 读取数据并预处理
open_nums = xlsread('移动通知户开户数.xlsx',1,'B2:B732');
%% 计算月平均，季度平均，年平均并绘图找周期规律,并处理异常值
figure(1),[months_mean,seasons_mean,years_mean,month_starts,month_ends,season_starts,season_ends] = Calu_mean(open_nums);
[m,n] = find(abs(open_nums-mean(open_nums))>2*std(open_nums));
open_nums(m) = mean(open_nums);
%% 尝试进行去趋势和去周期,考虑到存在多重周期，将年份分开按照月为周期去除周期（其中每月为多少天根据两年分别不同）
data_2012 = open_nums(1:366);
data_2013 = open_nums(367:end);
figure(2),[detrend_data2012,detrend_deT_data2012] = Detrend_plot(data_2012,30);% 2012开户数变化趋势
figure(3),[detrend_data2013,detrend_deT_data2013] = Detrend_plot(data_2013,31);% 2013开户数变化趋势
figure(4),[detrend_data,detrend_deT_data] = Detrend_plot(open_nums,30);% 2012-2013开户数变化趋势
figure(5),subplot(411),autocorr(open_nums),title('原数据自相关图')% 自相关图分析
subplot(412),autocorr(detrend_data),title('2012年随机项自相关图')
subplot(413),autocorr(detrend_deT_data2013),title('2013年随机项自相关图')
subplot(414),autocorr(detrend_deT_data),title('2012-2013年随机项自相关图')
clearvars month_starts month_ends season_starts season_ends data_2012 data2013
%% 平稳序列去均值变为零均值平稳序列
zeromean_detrend_deT_data = detrend_deT_data-mean(detrend_deT_data);
[unbiased_autocorr,biased_autocorr] = my_autocorr(zeromean_detrend_deT_data);
%% 计算偏相关函数
[customed_parcorr] = my_parcorr(zeromean_detrend_deT_data,biased_autocorr);