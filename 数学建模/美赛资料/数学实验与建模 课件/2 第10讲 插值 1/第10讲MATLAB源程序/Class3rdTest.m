clear all
close all
clc

x=1:5;
y=1:3;
temps=[82 81 80 82 84;
    79 63 61 65 81;
    84 84 82 85 86];

xi=1:0.2:5;
yi=1:0.2:3;
zi=interp2(x,y,temps,xi',yi,'cubic');


figure;
mesh(x,y,temps);
hold on;
mesh(xi,yi,zi);

















