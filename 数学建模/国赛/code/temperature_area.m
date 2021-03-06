clear
close all
clc

temperature15=175;%单位：度
temperature6=195;
temperature7=235;
temperature89=255;
temperature1011=25;
temperature_environment=25;

length_little_area=30.5;%cm
length_gap=5;%cm
length_front_back=25;%cm
length_all=length_little_area*11+length_gap*10+length_front_back*2;

t=0.5;%s
v_attribute=70;%cm/min
v_attribute=v_attribute/60;%cm/s

size_air=0.01;%粒度：个/cm
% temperature_stove=zeros(length_all/size_air,1);

temperature_front=heat(temperature_environment,temperature15,length_front_back-17,size_air);
temperature_56=heat(temperature15,temperature6,length_gap+0,size_air);
temperature_67=heat(temperature6,temperature7,length_gap+0,size_air);
temperature_78=heat(temperature7,temperature89,length_gap+0,size_air);
temperature_910_1011=heat(temperature89,temperature_environment,2*(length_little_area+length_gap)+25,size_air);
% temperature_back=heat(temperature1011,temperature_environment,length_front_back,size_air);
temperature_back=temperature_environment;

temperature_stove=[25*ones(17/size_air,1);temperature_front;temperature15*ones(5*length_little_area/size_air+4*length_gap/size_air-0,1);temperature_56;...
    temperature6*ones(length_little_area/size_air-0,1);temperature_67;...
    temperature7*ones(length_little_area/size_air-0,1);temperature_78;...
    temperature89*ones(2*length_little_area/size_air+length_gap/size_air-0,1);temperature_910_1011;...
    temperature_back*ones((length_front_back-25)/size_air,1)];
figure
plot([0.01:0.01:length_all],temperature_stove)
title("炉内环境温度");
xlabel('距离/cm');
ylabel('温度/°C');

data_from_attribute=xlsread("C:\Users\mashed potato\Desktop\国赛\ABC与数据\A\附件.xlsx");
data_time=data_from_attribute(:,1);
data_temperature=data_from_attribute(:,2);

% figure
% plot(data_time,data_temperature)
% title("附件温度数据")

RC=53;%瞎猜的
% temperature_t(t*2+1)=temperature_t(t*2)+(temperature_s-temperature_t(t*2))*(1-exp(-0.5/RC));
temperature_t(1)=temperature_environment;
% for RC=50:1:58
for t=0.5:0.5:length_all/v_attribute
    temperature_t(2*t+1)=temperature_t(2*t)+(temperature_stove(round(t*v_attribute/size_air))-temperature_t(2*t))*(1-exp(-0.5/RC));
end
% figure
% plot([0:0.5:length_all/v_attribute],temperature_t);
% title("拟合温度");

figure
plot(data_time,data_temperature,[0:0.5:length_all/v_attribute],temperature_t);
title("附件与模型炉温曲线的对比");
xlabel('时间/s');
ylabel('温度/°C');
legend('附件曲线','模型曲线');
% end

% temperature_t(1)=temperature_environment;
% h=1;
% c=1;
% m=1;
% for t=0.5:0.5:length_all/v_attribute
%     temperature_t(2*t+1)=temperature_t(2*t)+(h*(temperature_stove(round(t*v_attribute/size_air))-temperature_t(2*t))*0.5)/(c*m);
% end
% figure
% plot(temperature_t);
% title("拟合温度");
