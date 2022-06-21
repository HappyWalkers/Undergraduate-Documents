%% 计算月平均，季度平均，年平均意图找寻周期规律
function [months_mean,seasons_mean,years_mean,month_starts,month_ends,season_starts,season_ends] = Calu_mean(open_nums)
t = 1:length(open_nums);
nums = open_nums;
month_days = [0,31,29,31,30,31,30,31,31,30,31,30,31,31,28,31,30,31,30,31,31,30,31,30,31]; 
season_days = [0,sum(month_days(2:4)),sum(month_days(5:7)),sum(month_days(8:10)),sum(month_days(11:13))...
    ,sum(month_days(14:16)),sum(month_days(17:19)),sum(month_days(20:22)),sum(month_days(23:25))];
% calu the month_mean nums
months_mean = zeros(1,24);
month_starts = zeros(1,24);
month_ends = zeros(1,24);
for ii = 1:length(month_days)-1
    start_day = sum(month_days(1:ii))+1;
    end_day = sum(month_days(1:ii+1));
    month_starts(ii) = start_day;
    month_ends(ii) = end_day;
    months_mean(ii) = mean(nums(start_day:end_day));
end
% calu the season_mean nums
seasons_mean = zeros(1,8);
season_starts = zeros(1,8);
season_ends = zeros(1,8);
for ii = 1:8
    season_start = sum(season_days(1:ii))+1;
    season_end = sum(season_days(1:ii+1));
    seasons_mean(ii) = mean(nums(season_start:season_end));
    season_starts(ii) = season_start;
    season_ends(ii) = season_end;
end
%calu the mean_year nums
years_mean = zeros(1,2);
years_mean(1) = mean(nums(1:366));
years_mean(2) = mean(nums(367:731));
%% Plot
steps = 30;
subplot(2,2,1)
plot(t(1:366),smooth(nums(1:366),steps),'r',t(367:731),smooth(nums(367:731),steps),'b'),title('原始开户数滑动平均【窗口30】')
grid on
subplot(2,2,2)
for ii=1:24
    if ii<=12
        plot(month_starts(ii):month_ends(ii),months_mean(ii)*ones(1,(length(month_starts(ii):month_ends(ii)))),'r')
        hold on
    else
        plot(month_starts(ii):month_ends(ii),months_mean(ii)*ones(1,(length(month_starts(ii):month_ends(ii)))),'b')
    end
end
grid on,title('月平均开户数变化')
subplot(2,2,3)
for ii=1:8
    if ii<=4
        plot(season_starts(ii):season_ends(ii),seasons_mean(ii)*ones(1,length((season_starts(ii):season_ends(ii)))),'r','linewidth',8)
        hold on
    else
        plot(season_starts(ii):season_ends(ii),seasons_mean(ii)*ones(1,length((season_starts(ii):season_ends(ii)))),'b','linewidth',8)
    end
end
grid on,title('季度平均开户数变化')
subplot(2,2,4)
plot(1:366,ones(1,366)*years_mean(1),'r',367:731,ones(1,365)*years_mean(2),'b','linewidth',4)
grid on,title('年平均开户数变化')
end