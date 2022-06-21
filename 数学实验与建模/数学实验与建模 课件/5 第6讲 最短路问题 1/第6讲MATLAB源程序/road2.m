clear all
close all
clc

a = [0   9   inf 3   inf;
     9   0   2   inf 7;
     inf 2   0   2   4;
     3   inf 2   0   inf;
     inf 7   4   inf 0];
  
[D,R]=floyd(a)