clear
training=[50	33	14	2
67	31	56	24
89	31	51	23
46	36	10	2
65	30	52	20
58	27	51	19
57	28	45	13
63	33	47	16
49	25	45	17
70	32	47	14
48	31	16	2
63	25	50	19
49	36	14	1
44	32	13	2
58	26	40	12
63	27	49	18
50	23	33	10
51	38	16	2
50	30	16	2];
  %用于构造判别函数的训练样本数据矩阵
        group=[1;3 ; 3 ; 1; 3; 3;  2; 2; 3; 2;  1;  3; 1; 1; 2; 3 ; 2;  1 ; 1];
%参数group是与training相应的分组变量
sample=[64	28	56	21
51	38	19	4
49	   30	 14      2];
%[class,err]=classify(sample,training,group,'mahalanobis')
                    %使用马氏距离判别法分类
%[class,err]=classify(sample,training,group,'linear')
                    %使用线性判别法分类
[class,err]=classify(sample,training,group,'quadratic')
                    %使用二次判别法分类
