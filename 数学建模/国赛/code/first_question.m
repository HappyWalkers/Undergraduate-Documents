clear
close all
clc

% 假设传送带过炉速度为78 cm/min，各温区温度的设定值分别为173ºC（小温区1~5）、198ºC（小温区6）、230ºC（小温区7）和257ºC（小温区8~9）

temperature15=173;%单位：度
temperature6=198;
temperature7=230;
temperature89=257;
temperature1011=25;
temperature_environment=25;

length_little_area=30.5;%cm
length_gap=5;%cm
length_front_back=25;%cm
length_all=length_little_area*11+length_gap*10+length_front_back*2;

t=0.5;%s
v_attribute=78;%cm/min
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

RC=44;%瞎猜的
% temperature_t(t*2+1)=temperature_t(t*2)+(temperature_s-temperature_t(t*2))*(1-exp(-0.5/RC));
temperature_t(1)=temperature_environment;
for t=0.5:0.5:length_all/v_attribute
    temperature_t(2*t+1)=temperature_t(2*t)+(temperature_stove(round(t*v_attribute/size_air))-temperature_t(2*t))*(1-exp(-0.5/RC));
    temp_val(2*t)=round(t*v_attribute/size_air);
    if round(t*v_attribute/size_air)==(length_front_back+2*length_little_area+2*length_gap+1/2*length_little_area)/size_air-10%11125->11115
        temperature_result_3=temperature_t(2*t+1);%小温区3中点处的温度
    end
    if round(t*v_attribute/size_air)==(length_front_back+5*length_little_area+5*length_gap+1/2*length_little_area)/size_air%21775
        temperature_result_6=temperature_t(2*t+1);
    end
    if round(t*v_attribute/size_air)==(length_front_back+6*length_little_area+6*length_gap+1/2*length_little_area)/size_air+25%25325->25350
        temperature_result_7=temperature_t(2*t+1);
    end
    if round(t*v_attribute/size_air)==(length_front_back+7*length_little_area+5*length_gap+length_little_area)/size_air-20%29400->29380
        temperature_result_8=temperature_t(2*t+1);
    end
end
figure
plot(temperature_t);
title("模型温度");
xlabel('时间/s');
ylabel('温度/°C');

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

% 请给出焊接区域中心的温度变化情况，列出小温区3、6、7中点及小温区8结束处焊接区域中心的温度，画出相应的炉温曲线，
% 并将每隔0.5 s焊接区域中心的温度存放在提供的result.csv中。
disp(['小温区3中点温度为：',num2str(temperature_result_3)]);
disp(['小温区6中点温度为：',num2str(temperature_result_6)]);
disp(['小温区7中点温度为：',num2str(temperature_result_7)]);
disp(['小温区8结束温度为：',num2str(temperature_result_8)]);

temperature_t=temperature_t';
t_result=[0:0.5:size(temperature_t,1)/2-0.5]';
varNames={'时间(s)','温度(摄氏度)'};
t_result=t_result*100;
t_result=round(t_result);
t_result=t_result/100;
temperature_t=temperature_t*100;
temperature_t=round(temperature_t);
temperature_t=temperature_t/100;
result=table(t_result,temperature_t,'VariableNames',varNames);
writetable(result,'C:\Users\mashed potato\Desktop\国赛\ABC与数据\A\result.csv');