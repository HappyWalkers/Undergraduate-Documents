clear
close all

%% data
load('C:\Users\mashed potato\Desktop\MCM_data\scdata1870_1900');
load('C:\Users\mashed potato\Desktop\MCM_data\scdata1901_1930');
load('C:\Users\mashed potato\Desktop\MCM_data\scdata1931_1960');
load('C:\Users\mashed potato\Desktop\MCM_data\scdata1961_1990');
load('C:\Users\mashed potato\Desktop\MCM_data\scdata1991_2003');
load('C:\Users\mashed potato\Desktop\MCM_data\scdata2004');
load('C:\Users\mashed potato\Desktop\MCM_data\scdata2005');
load('C:\Users\mashed potato\Desktop\MCM_data\scdata2006');
load('C:\Users\mashed potato\Desktop\MCM_data\scdata2007');
load('C:\Users\mashed potato\Desktop\MCM_data\scdata2008');
load('C:\Users\mashed potato\Desktop\MCM_data\scdata2009');
load('C:\Users\mashed potato\Desktop\MCM_data\scdata2010');
load('C:\Users\mashed potato\Desktop\MCM_data\scdata2011');
load('C:\Users\mashed potato\Desktop\MCM_data\scdata2012');
load('C:\Users\mashed potato\Desktop\MCM_data\scdata2013');
load('C:\Users\mashed potato\Desktop\MCM_data\scdata2014');
load('C:\Users\mashed potato\Desktop\MCM_data\scdata2015');
load('C:\Users\mashed potato\Desktop\MCM_data\scdata2016');
load('C:\Users\mashed potato\Desktop\MCM_data\scdata2017');
load('C:\Users\mashed potato\Desktop\MCM_data\scdata2018');
load('C:\Users\mashed potato\Desktop\MCM_data\scdata2019');
scdata=cat(3,scdata1870,scdata1901,scdata1931,scdata1961,scdata1991,...
    scdata2004,scdata2005,scdata2006,scdata2007,scdata2008,scdata2009,...
    scdata2010,scdata2011,scdata2012,scdata2013,scdata2014,scdata2015,...
    scdata2016,scdata2017,scdata2018,scdata2019);
scdata=scdata./100;
save('C:\Users\mashed potato\Desktop\MCM_data\scdata','scdata');
%% train exp
% time=([1870:2015]-1870)./(2015-1870);%归一化
time=1870:2019;
[time,ps_t]=mapminmax(time,0,1);
degree=zeros(1,length(time));
for i=1:length(time)
    degree(i)=scdata(1,1,12*(i-1)+1);
end

time_train=1870:2000;
time_train=mapminmax('apply',time_train,ps_t);
degree_train=zeros(1,length(time_train));
for i=1:length(time_train)
    degree_train(i)=scdata(1,1,12*(i-1)+1);
end

time_guess=2001:2019;
time_guess=mapminmax('apply',time_guess,ps_t);

% degree=(degree-min(degree))/(max(degree)-min(degree));
[degree_train,ps_d]=mapminmax(degree_train,-1,1);
net=newff(minmax(degree_train),[200,1],{'tansig','purelin'});
net.trainParam.epochs=1000;   %最大训练次数
net.trainParam.goal=0;       %训练目标
net.trainParam.show=10;      %两次显示之间的训练次数
% net.trainParam.time=inf;
% net.trainParam.max_fail=15;
 net.trainParam.min_grad=1e-10;
% net.trainParam.lr=0.2;
% net.trainParam.mu=0.8;
[net,tr]=train(net,time_train,degree_train);           %网络训练函数，train中的net为创建的初始网络

guess=sim(net,time);
time=mapminmax('reverse',time,ps_t);
time_train=mapminmax('reverse',time_train,ps_t);
time_guess=mapminmax('reverse',time_guess,ps_t);
degree_train=mapminmax('reverse',degree_train,ps_d);
guess=mapminmax('reverse',guess,ps_d);

% figure
% plot(time_train,degree_train);
% hold on
% plot(time_guess,guess);
% legend('reality','guess');
% title('Real and predicted water temperatures');
% xlabel('time(year)');
% ylabel('temperature(℃)');



%% plot
% time50=2021:2070;
% [time50,ps_t50]=mapminmax(time50,0,1);
% guess50=sim(net,time50);
% time50=mapminmax('reverse',time50,ps_t50);
% guess50=mapminmax('reverse',guess50,ps_d);

% time4=2016:2019;
% [time4,ps_t4]=mapminmax(time4,0,1);
% guess4=sim(net,time4);
% time4=mapminmax('reverse',time4,ps_t4);
% guess4=mapminmax('reverse',guess4,ps_d);



figure
plot(time,degree);

% hold on
% plot(time_r4,degree4);

% hold on
% plot(time4,guess4);

hold on
plot(time,guess);
legend('reality:1870-2019','prediction:1870-2019');
title('The water temperature of the past and the future');
xlabel('time(year)');
ylabel('temperature(℃）');