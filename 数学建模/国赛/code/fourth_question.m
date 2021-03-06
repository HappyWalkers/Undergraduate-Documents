clear
close all
clc

%% 参数设定
% 各温区设定的温度分别为175ºC（小温区1~5）、195ºC（小温区6）、235ºC（小温区7）、255ºC（小温区8~9）及25ºC（小温区10~11）；
% 在上述实验设定温度的基础上，各小温区设定温度可以进行+-10ºC范围内的调整。调整时要求小温区1~5中的温度保持一致，
% 小温区8~9中的温度保持一致，小温区10~11中的温度保持25ºC。传送带的过炉速度调节范围为65~100 cm/min。

length_little_area=30.5;%cm
length_gap=5;%cm
length_front_back=25;%cm
length_all=length_little_area*11+length_gap*10+length_front_back*2;

t=0.5;%s
size_air=0.01;%粒度：个/cm
RC=44;%与附件温度曲线比较得知

temperature1011=25;
temperature_environment=25;

temperature15_results=zeros(30,1);%记录满足制程界限的结果
temperature6_results=zeros(30,1);
temperature7_results=zeros(30,1);
temperature89_results=zeros(30,1);
v_attribute_results=zeros(10000,1);
shadow_results=zeros(10000,1);
mismatch_results=zeros(10000,1);
%% 遍历温度场温度
for temperature15=165:1:185
    for temperature6=185:1:205
        for temperature7=225:1:245
            for temperature89=245:1:265
                
                %计算过渡区温度
                temperature_front=heat(temperature_environment,temperature15,length_front_back,size_air);
                temperature_56=heat(temperature15,temperature6,length_gap+10,size_air);
                temperature_67=heat(temperature6,temperature7,length_gap+10,size_air);
                temperature_78=heat(temperature7,temperature89,length_gap+10,size_air);
                temperature_910_1011=heat(temperature89,temperature_environment,2*(length_little_area+length_gap)-10,size_air);
                % temperature_back=heat(temperature1011,temperature_environment,length_front_back,size_air);
                temperature_back=temperature_environment;
                
                
                %表示炉内温度
                temperature_stove=[temperature_front;temperature15*ones(5*length_little_area/size_air+4*length_gap/size_air-5,1);temperature_56;...
                    temperature6*ones(length_little_area/size_air-10,1);temperature_67;...
                    temperature7*ones(length_little_area/size_air-10,1);temperature_78;...
                    temperature89*ones(2*length_little_area/size_air+length_gap/size_air-5,1);temperature_910_1011;...
                    temperature_back*ones((length_front_back+10)/size_air,1)];
                % plot(temperature_stove);
                
                i=1;
                %遍历过炉速度
                for v_attribute=65:1:100
                    v_attribute=v_attribute/60;
                    temperature_t=zeros(1,1);
                    temperature_t(1)=temperature_environment;
                    flag=1;
                    time_150_190=0;
                    time_217=0;
                    %计算炉温曲线，同时检查是否满足制程界限
                    for t=0.5:0.5:length_all/v_attribute
                        temperature_t(2*t+1)=temperature_t(2*t)+(temperature_stove(round(t*v_attribute/size_air))-temperature_t(2*t))*(1-exp(-0.5/RC));
                        
                        %斜率
                        slope=(temperature_t(2*t+1)-temperature_t(2*t))/0.5;
                        if abs(slope)>3
                            flag=0;
                        end
                        
                        %150-190温度间时间
                        if temperature_t(2*t+1)>=150 && temperature_t(2*t+1)<=190
                            time_150_190=time_150_190+0.5;
                        end
                        
                        %217温度以上时间
                        if temperature_t(2*t+1)>217
                            time_217=time_217+0.5;
                        end
                        
                    end
%                     plot(temperature_t);
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
                    if flag==1%若满足制程界限,计算阴影面积和不对称性，同时记录结果
                        %计算阴影面积
                        [~,index_first_217]=max(temperature_t>217);
                        [~,index_max]=max(temperature_t);
                        shadow=sum(temperature_t(index_first_217:index_max)-217)*0.5;%微积分的思想
                        %计算不对称（重合）
                        [~,index_first_217]=max(temperature_t>217);
                        [~,index_max]=max(temperature_t);
                        index_217_end=index_first_217+size(temperature_t(temperature_t>217),2);
                        area_left=temperature_t(index_first_217:index_max);
                        area_right=temperature_t(index_max:index_217_end);
                        if size(area_left,2)>size(area_right,2)
                            area_up=fliplr(area_left);
                            area_down=[area_right,217*ones(1,size(area_left,2)-size(area_right,2))];
                        else
                            area_up=fliplr(area_right);
                            area_down=[area_left,217*ones(1,size(area_right,2)-size(area_left,2))];
                        end
                        mismatch=sum(abs(area_up-area_down))/(sum(area_up)+sum(area_down));
                        %记录结果
                        temperature15_results(i)=temperature15;
                        temperature6_results(i)=temperature6;
                        temperature7_results(i)=temperature7;
                        temperature89_results(i)=temperature89;
                        v_attribute_results(i)=round(v_attribute*60);
                        shadow_results(i)=shadow;
                        mismatch_results(i)=mismatch;
                        i=i+1;
                    end
                end
            end
        end
    end
end

shadow_results=shadow_results(shadow_results>0);
mismatch_results=mismatch_results(mismatch_results>0);
%% 方案一：对称程度最高
[mismatch_results_min,mismatch_results_min_index]=min(mismatch_results);
shadow_results_min=shadow_results(mismatch_results_min_index);
temperature15_results_min=temperature15_results(mismatch_results_min_index);
temperature6_results_min=temperature6_results(mismatch_results_min_index);
temperature7_results_min=temperature7_results(mismatch_results_min_index);
temperature89_results_min=temperature89_results(mismatch_results_min_index);
v_attribute_results_min=v_attribute_results(mismatch_results_min_index);

disp('对称程度高');
disp(['阴影部分面积：',num2str(shadow_results_min)]);
disp(['不对称性（不重合度）',num2str(mismatch_results_min)]);
disp(['1-5区温度',num2str(temperature15_results_min)]);
disp(['6区温度',num2str(temperature6_results_min)]);
disp(['7区温度',num2str(temperature7_results_min)]);
disp(['89区温度',num2str(temperature89_results_min)]);
disp(['过炉速度',num2str(v_attribute_results_min)]);

%% 方案二：最小阴影面积
[shadow_results_min,shadow_results_min_index]=min(shadow_results);
mismatch_results_min=mismatch_results(shadow_results_min_index);
temperature15_results_min=temperature15_results(shadow_results_min_index);
temperature6_results_min=temperature6_results(shadow_results_min_index);
temperature7_results_min=temperature7_results(shadow_results_min_index);
temperature89_results_min=temperature89_results(shadow_results_min_index);
v_attribute_results_min=v_attribute_results(shadow_results_min_index);

disp('最小阴影面积');
disp(['阴影部分面积：',num2str(shadow_results_min)]);
disp(['不对称性（不重合度）',num2str(mismatch_results_min)]);
disp(['1-5区温度',num2str(temperature15_results_min)]);
disp(['6区温度',num2str(temperature6_results_min)]);
disp(['7区温度',num2str(temperature7_results_min)]);
disp(['89区温度',num2str(temperature89_results_min)]);
disp(['过炉速度',num2str(v_attribute_results_min)]);