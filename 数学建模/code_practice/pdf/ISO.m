clear,clc 
BOX=[231,92,94];% ISO container internal dimensions L ¡Á W ¡Á H 
MED1=[14 7 5];% Medical Package dimensions l¡Áw ¡Áh % BOX_L Maximum capacity
l_max=fix(BOX(1)/MED1(1));
w_max=fix(BOX(1)/MED1(2));
 M=[];
 for i=0:l_max%   
     I=fix(BOX(2)/MED1(2));% BOX_W Corresponding capacity   
     II=mod(BOX(2),MED1(2));% Remaining length  
     j=fix((BOX(1)-i*MED1(1))/MED1(2));
     J=fix(BOX(2)/MED1(1));
      JJ=mod(BOX(2),MED1(1));
     remain=BOX(1)-i*MED1(1)-j*MED1(2);
     M=[M;i,I,II,j,J,JJ,remain,i*I+j*J];
 end
 [value,index]=max(M(:,end));
 M(index,end)