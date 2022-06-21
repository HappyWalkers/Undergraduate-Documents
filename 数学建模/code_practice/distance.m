clear
clc
close all
R=6371;%kilometer
latitude=[18.33 18.22 18.44 18.40 18.47];
longitude=[-65.65 -66.03 -66.07 -66.16 -66.73];
%½Ç¶È×ª»¡¶È
latitude=latitude*pi/180;
longitude=longitude*pi/180;
dist=[];
for i=1:5
    for j=(i+1):5
        jiao=acos( cos(latitude(j)) * cos(latitude(i)) * cos(longitude(i) - longitude(j) ) + sin( latitude(i)) * sin( latitude(j) ));
        dis=R* jiao;
        fprintf("the distance between city %d and city %d is: %d kilometers\n",i,j,dis);
        dist=[dist dis];
    end
end
save('hos_dis','dist');