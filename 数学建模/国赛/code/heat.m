function [temperature_mid]=heat(temperature_left,temperature_right,length_mid,size_air)
temperature_mid=25*ones(length_mid/size_air+1,1);
temperature_mid(1)=temperature_left;
% temperature_mid(end)=temperature_right;
% temp=zeros(10000,1);
% for t=1:length_mid/size_air*1000
%     for i=2:size(temperature_mid,1)-1
%         temperature_mid(i)=(temperature_mid(i-1)+temperature_mid(i+1))/2;
%     end
% %     temp(t)=temperature_mid(2);
% %     if t>1000
% %         if temp(t)-temp(t-1)<0.0001
% %             break
% %         end
% %     end
% end
delta=temperature_right-temperature_left;
increase=delta/(length_mid/size_air+1);
for i=2:1:length_mid/size_air+1
    temperature_mid(i)=temperature_mid(i-1)+increase;
end
temperature_mid=temperature_mid(2:end);
