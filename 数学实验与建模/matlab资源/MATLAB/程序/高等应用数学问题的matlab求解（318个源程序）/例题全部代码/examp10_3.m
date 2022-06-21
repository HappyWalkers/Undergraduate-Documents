A={'skhsak','ssd','ssfa'}; B={'sdsd','ssd','sssf'}; F=union(A,B)  % ²¢¼¯

E=union(A,B); F=intersect(A,B); key=all(ismember(F,E))
key=all(ismember(A,A)) & (length(setdiff(A,A))>0);
key1=all(ismember(A,A)); [key,key1]