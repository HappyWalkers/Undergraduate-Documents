clear
close all
clc

hos4=[78,1151];
hos3=[30,1237];
hos2=[239,1302];

b=dis(hos3,hos4);
c=dis(hos2,hos4);
d=dis(hos2,hos3);

B=acos( (c*c + d*d - b*b)/(2*c*d) );
C=acos( (b*b + d*d - c*c)/(2*b*d) );
D=acos( (b*b + c*c - d*d)/(2*b*c) );

B=B*180/pi
C=C*180/pi
D=D*180/pi
