function [p2]=ChangePath2(p1,CityNum)
global p2;
while(1)
     R=unidrnd(CityNum,1,2);
     if abs(R(1)-R(2))>1
         break;
     end
end
R=unidrnd(CityNum,1,2);
I=R(1);J=R(2);
%len1=D(p(I),p(J))+D(p(I+1),p(J+1));
%len2=D(p(I),p(I+1))+D(p(J),p(J+1));
if I<J
   p2(1:I)=p1(1:I);
   p2(I+1:J)=p1(J:-1:I+1);
   p2(J+1:CityNum)=p1(J+1:CityNum);
else
   p2(1:J)=p1(1:J);
   p2(J+1:I)=p1(I:-1:J+1);
   p2(I+1:CityNum)=p1(I+1:CityNum);
end
