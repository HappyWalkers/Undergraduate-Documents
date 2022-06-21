clear
close all
clc

rico=imread('²¨¶àÀè¸÷.jpg');
a=rico(:,1);
b=rico(:,2);
c=rico(:,3);

m=size(a,1);
n=size(a,2);

for i=1:m
    for j=1:n
        if a(i,j)>=0 && a(i,j)<100