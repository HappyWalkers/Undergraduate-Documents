data=xlsread("C:\Users\mashed potato\Desktop\校赛\附件2.xlsx");
v=data(2:end,3);
% index=zeros(resultStruct.nSalesmen);
% v_hao=zeros(resultStruct.nSalesmen);
break_point=[0,resultStruct.optBreak,length(resultStruct.optRoute)];
for i=1:resultStruct.nSalesmen
    index=resultStruct.optRoute(break_point(i)+1:break_point(i+1))-1;
    v_hao=v(index(1,:))
end



