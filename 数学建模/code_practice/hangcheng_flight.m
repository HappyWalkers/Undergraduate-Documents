clear
close all
clc

speed=[40 79 64 60 60 79 64];%��λ��km/h
time= [35 40 35 18 15 24 16]./60;%��λ��h
flight_dis=speed.*time

save('flight_dis','flight_dis');
