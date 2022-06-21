clear
close all
clc

% 假设各温区温度的设定值分别为182ºC（小温区1~5）、203ºC（小温区6）、237ºC（小温区7）、254ºC（小温区8~9）

temperature15=182;%单位：度
temperature6=203;
temperature7=237;
temperature89=254;
temperature1011=25;
temperature_environment=25;

length_little_area=30.5;%cm
length_gap=5;%cm
length_front_back=25;%cm
length_all=length_little_area*11+length_gap*10+length_front_back*2;

t=0.5;%s
% v_attribute=78;%cm/min
% v_attribute=v_attribute/60;%cm/s

size_air=0.01;%粒度：个/cm
% temperature_stove=zeros(length_all/size_air,1);

temperature_front=heat(temperature_environment,temperature15,length_front_back,size_air);
temperature_56=heat(temperature15,temperature6,length_gap,size_air);
temperature_67=heat(temperature6,temperature7,length_gap,size_air);
temperature_78=heat(temperature7,temperature89,length_gap,size_air);
temperature_910_1011=heat(temperature89,temperature_environment,2*(length_little_area+length_gap),size_air);
% temperature_back=heat(temperature1011,temperature_environment,length_front_back,size_air);
temperature_back=temperature_environment;

temperature_stove=[temperature_front;temperature15*ones(5*length_little_area/size_air+4*length_gap/size_air,1);temperature_56;...
    temperature6*ones(length_little_area/size_air,1);temperature_67;...
    temperature7*ones(length_little_area/size_air,1);temperature_78;...
    temperature89*ones(2*length_little_area/size_air+length_gap/size_air,1);temperature_910_1011;...
    temperature_back*ones(length_front_back/size_air,1)];
% plot(temperature_stove);
RC=44;%瞎猜的
% 传送带的过炉速度调节范围为65~100 cm/min。

i=1;
v_attribute_results=zeros(50,1);
for v_attribute=65:1:100%遍历过炉速度
    v_attribute=v_attribute/60;
    temperature_t=zeros(1,1);
    temperature_t(1)=temperature_environment;
    flag=1;
    time_150_190=0;
    time_217=0;
    for t=0.5:0.5:length_all/v_attribute%计算炉温曲线
        temperature_t(2*t+1)=temperature_t(2*t)+(temperature_stove(round(t*v_attribute/size_air))-temperature_t(2*t))*(1-exp(-0.5/RC));
        
        slope=(temperature_t(2*t+1)-temperature_t(2*t))/0.5;
        if abs(slope)>3%斜率
            flag=0;
        end
        
        
        if temperature_t(2*t+1)>=150 && temperature_t(2*t+1)<=190
            time_150_190=time_150_190+0.5;
        end
        
        
        if temperature_t(2*t+1)>217
            time_217=time_217+0.5;
        end
        
    end
    if v_attribute==82/60
        figure
        plot(temperature_t);
        title("炉温曲线");
        xlabel('时间/s');
        ylabel('温度/°C');
        
        figure
        plot([0.01:0.01:length_all],temperature_stove)
        title("炉内环境温度");
        xlabel('距离/cm');
        ylabel('温度/°C');
    end
    %     disp(time_150_190);
    if time_150_190<60 || time_150_190>120
        flag=0;
    end
    %     disp(time_217);
    if time_217<40 || time_217>90
        flag=0;
    end
    %     disp(max(temperature_t));
    if max(temperature_t)<240 || max(temperature_t)>250
        flag=0;
    end
    if flag==1
        v_attribute_results(i)=round(v_attribute*60);
        i=i+1;
    end
end
disp(['最大传送带过炉速度',num2str(max(v_attribute_results))]);