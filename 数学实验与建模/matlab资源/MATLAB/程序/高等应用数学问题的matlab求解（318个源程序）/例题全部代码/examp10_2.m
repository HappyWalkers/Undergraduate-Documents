A={'skhsak','ssd','ssfa'}; B={'sdsd','ssd','sssf'}; F=union(A,B)  % ����

D=intersect(A,B)   % ����

C={'jsg','sjjfs','ssd'};  % ����������ļ���������֤�����
E=setdiff(union(intersect(A,B),intersect(C,B)),intersect(union(A,C),B))
