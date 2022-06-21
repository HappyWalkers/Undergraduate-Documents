clear
close all
clc

load('lamda_line');
hos4=[78,1151];
hos4w=18.40;
hos4j=-66.16;
container=[78 1209];
R=6371;%km

con_j=hos4j-((1151-1209)*lamda_line/R)*180/pi;
con_w=hos4w;
con=[con_j,con_w]


