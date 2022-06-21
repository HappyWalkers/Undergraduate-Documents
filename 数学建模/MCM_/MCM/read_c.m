clear

fid=fopen('E:\ÎÄµµ\MCM_\data\data.txt','r');
data_all=zeros(180,360,12*150);
for i=1:12*150%months
%     position=ftell(FI);
    fseek(fid,45,'cof');
    data=fscanf(fid,'%d',[360 180]);%°´ÁÐÌî³ä¡£¡£¡£
    data_all(:,:,i)=data';
end
fclose(fid);
scdata_all=data_all(25:40,170:180,:);
% save('C:\Users\mashed potato\Desktop\MCM_data\scdata_all','scdata_all');