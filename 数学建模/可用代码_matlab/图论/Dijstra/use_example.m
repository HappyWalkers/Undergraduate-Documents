%输入带权邻接矩阵，起点，重点，输出最短距离和路径编号
clear 
clc
close all
weight=    [0     2     8     1   Inf   Inf   Inf   Inf   Inf   Inf   Inf;
            2     0     6   Inf     1   Inf   Inf   Inf   Inf   Inf   Inf;
            8     6     0     7     5     1     2   Inf   Inf   Inf   Inf;
            1   Inf     7     0   Inf   Inf     9   Inf   Inf   Inf   Inf;
          Inf     1     5   Inf     0     3   Inf     2     9   Inf   Inf;
          Inf   Inf     1   Inf     3     0     4   Inf     6   Inf   Inf;
          Inf   Inf     2     9   Inf     4     0   Inf     3     1   Inf;
          Inf   Inf   Inf   Inf     2   Inf   Inf     0     7   Inf     9;
          Inf   Inf   Inf   Inf     9     6     3     7     0     1     2;
          Inf   Inf   Inf   Inf   Inf   Inf     1   Inf     1     0     4;
          Inf   Inf   Inf   Inf   Inf   Inf   Inf     9     2     4     0;];
[dis, path]=dijkstra(weight,1, 11)