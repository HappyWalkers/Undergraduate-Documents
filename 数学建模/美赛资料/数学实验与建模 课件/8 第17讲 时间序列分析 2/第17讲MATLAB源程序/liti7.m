spec= garchset('R',1,'M',3);           %ָ��ģ�͵Ľṹ
[coeff,errors,LLF,innovations,sigmas,summary] = garchfit(spec,w) %��ϲ���
h=lbqtest(innovations)                %ģ�ͼ���
[sigmaForecast,x_Forecast] = garchpred(coeff,w,3)   %Ԥ��
