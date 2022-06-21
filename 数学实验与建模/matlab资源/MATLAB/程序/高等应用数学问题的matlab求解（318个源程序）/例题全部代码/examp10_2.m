A={'skhsak','ssd','ssfa'}; B={'sdsd','ssd','sssf'}; F=union(A,B)  % 并集

D=intersect(A,B)   % 交集

C={'jsg','sjjfs','ssd'};  % 可以由下面的集合运算验证结合律
E=setdiff(union(intersect(A,B),intersect(C,B)),intersect(union(A,C),B))
