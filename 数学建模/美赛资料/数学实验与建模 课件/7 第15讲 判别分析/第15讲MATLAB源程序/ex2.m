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
  %���ڹ����б�����ѵ���������ݾ���
        group=[1;3 ; 3 ; 1; 3; 3;  2; 2; 3; 2;  1;  3; 1; 1; 2; 3 ; 2;  1 ; 1];
%����group����training��Ӧ�ķ������
sample=[64	28	56	21
51	38	19	4
49	   30	 14      2];
%[class,err]=classify(sample,training,group,'mahalanobis')
                    %ʹ�����Ͼ����б𷨷���
%[class,err]=classify(sample,training,group,'linear')
                    %ʹ�������б𷨷���
[class,err]=classify(sample,training,group,'quadratic')
                    %ʹ�ö����б𷨷���
