clear all
close all
% clc

x0=[1;1];
A=[2 3 ;1 4];
b=[6;5];
Aeq=[];
beq=[];
VLB=[0;0]; 
VUB=[];

[x,fval]=fmincon(@fun3,x0,A,b,Aeq,beq,VLB,VUB)
