clear
close all
clc

speed=[40 79 64 60 60 79 64];%单位：km/h
time= [35 40 35 18 15 24 16]./60;%单位：h
flight_dis=speed.*time

save('flight_dis','flight_dis');
