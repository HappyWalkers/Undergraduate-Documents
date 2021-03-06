clear
close all
clc

data_from_attribute=xlsread("C:\Users\mashed potato\Desktop\国赛\ABC与数据\A\附件.xlsx");
data_time=data_from_attribute(:,1);
data_temperature=data_from_attribute(:,2);

figure
plot(data_time,data_temperature)
title("附件温度数据")


% 某回焊炉内有11个小温区及炉前区域和炉后区域（如图1），每个小温区长度为30.5 cm，相邻小温区之间有5 cm的间隙，炉前区域和炉后区域长度均为25 cm。
% 另外，生产车间的温度保持在25ºC。
% 附件是某次实验中炉温曲线的数据，各温区设定的温度分别为175ºC（小温区1~5）、195ºC（小温区6）、235ºC（小温区7）、255ºC（小温区8~9）及25ºC（小温区10~11）；
% 传送带的过炉速度为70 cm/min；焊接区域的厚度为0.15 mm。温度传感器在焊接区域中心的温度达到30ºC时开始工作，电路板进入回焊炉开始计时。

% 假设传送带过炉速度为78 cm/min，各温区温度的设定值分别为173ºC（小温区1~5）、198ºC（小温区6）、230ºC（小温区7）和257ºC（小温区8~9）

% 根据美国 ACI 研 究院 EMPF 中心的研究结果, 回流焊接的加热模型 可以简化为[ 1] : Tt -Ti =(Ts -Ti)(1 -e -t RC) (1) 式中:
% Tt —当时间为 t 时, PCB 的温度 ; Ti —PCB 的初始温度; Ts —加热环境的温度; R —传热的热阻; C —PCB 的热容。
% 其中 ,热阻 R 与回流焊炉的传热效率及 PCB 的 结构特征有关 ,热容与 PCB 的材料特性有关 。
temperature15=175;%单位：度
temperature6=195;
temperature7=235;
temperature89=255;
temperature1011=25;
temperature_environment=25;

t=0.5;%s
RC=60;%瞎猜的
v_attribute=70;%cm/min
v_attribute=70/60;%cm/s
length_little_area=30.5;%cm
length_gap=5;%cm
length_front_back=25;%cm
length_all=length_little_area*11+length_gap*10+length_front_back*2;
temperature_t=temperature_environment*ones(38,1);%0-18.5s
temperature_t(39)=data_temperature(1);

length_temp=[length_front_back,length_little_area,length_gap,length_little_area,length_gap,length_little_area,length_gap,...
    length_little_area,length_gap,length_little_area,length_gap,length_little_area,length_gap,length_little_area,length_gap,...
    length_little_area,length_gap,length_little_area,length_gap,length_little_area,length_gap,length_little_area,length_front_back];
length_temp=cumsum(length_temp);
for t=data_time(2):0.5:length_all/v_attribute
    if t>0 && t<=length_temp(1)/v_attribute
        temperature_s=100;%瞎猜的炉前温度
    else if t<=length_temp(10)/v_attribute
            temperature_s=temperature15;
        else if t<=length_temp(12)/v_attribute
                temperature_s=temperature6;
            else if t<=length_temp(14)/v_attribute
                    temperature_s=temperature7;
                else if t<=length_temp(18)/v_attribute
                        temperature_s=temperature89;
                    else if t<=length_temp(22)/v_attribute
                            temperature_s=temperature1011;
                        else if t<=length_temp(23)/v_attribute
                                temperature_s=100;
                            end
                        end
                    end
                end
            end
        end
    end
    temperature_t(t*2+1)=temperature_t(t*2)+(temperature_s-temperature_t(t*2))*(1-exp(-0.5/RC));
end
figure
plot([0:0.5:size(temperature_t,1)/2-0.5], temperature_t)
title("拟合数据")