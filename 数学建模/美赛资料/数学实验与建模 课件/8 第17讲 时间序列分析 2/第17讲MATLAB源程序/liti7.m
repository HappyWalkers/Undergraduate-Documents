spec= garchset('R',1,'M',3);           %指定模型的结构
[coeff,errors,LLF,innovations,sigmas,summary] = garchfit(spec,w) %拟合参数
h=lbqtest(innovations)                %模型检验
[sigmaForecast,x_Forecast] = garchpred(coeff,w,3)   %预测
