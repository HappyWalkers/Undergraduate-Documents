clear
close all
clc

hua1=load('hua_left');
hua2=load('hua_right');
hua4=load('hua_ml');
hua5=load('hua_mr');
hua6=load('hua_down');
load('a');
load('hos_x');
load('hos_y');

imshow(a);
text(hos_x,hos_y,'O','color','r');
text(1209,78,'O','color','g');
text(hua1.hua(1,:),hua1.hua(2,:),'*','color','g');
text(hua2.hua(1,:),hua2.hua(2,:),'*','color','b');
text(hua4.hua(1,:),hua4.hua(2,:),'*','color','c');
text(hua5.hua(1,:),hua5.hua(2,:),'*','color','m');
text(hua6.hua(1,:),hua6.hua(2,:),'*','color','y');