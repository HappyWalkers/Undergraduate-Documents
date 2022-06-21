function [min,path]=dijkstra(w,start,terminal)
n=size(w,1);
label(start)=0;%label为可更改标号集合（T）
f(start)=start;%f为父节点集合，第一个父节点即为start
for i=1:n%start之外的label均赋值为inf
    if i~=start
        label(i)=inf;
    end
end

s(1)=start;%s为固定标号集
u=start;%u初始化为start  %u即为新生长出的节点

while length(s)<n%将所有的节点加入固定标号集，即算出所有点间最短路径
    
    for i=1:n%根据当前节点，遍历更新T标号
        ins=0;
        
        for j=1:length(s)%遍历s中元素
            if i==s(j)%如果s中有元素和当前i相等
                ins=1;
            end
        end%已经在固定标号集中的节点 所连接的节点 无需更新T标号
        
        if ins==0%非固定标号集
            v=i;%用v储存i
            if label(v)>(label(u)+w(u,v))%取更小的作为新的T标号
                label(v)=(label(u)+w(u,v));
                f(v)=u;%用f记录 更新标号节点 的父节点，f对应序号记录的即为 该序号节点的 父节点
            end
        end
    end%由于树枝生长，新产生的节点邻接的节点需要更新T标号
    
    v1=0;
    k=inf;
    
    for i=1:n%选出当前所有 可见 T标号集中的最小值 记为 k，并记下此节点
        ins=0;
        for j=1:length(s)%固定标号集中的无需计算
            if i==s(j)
                ins=1;
            end
        end
        if ins==0%非固定标号集
            v=i;%用v存储i
            if k>label(v)%更小者记为k
                k=label(v);
                v1=v;%用v1存下此时的v（点）
            end
        end
    end
    
    s(length(s)+1)=v1;  %s为固定标号集，固定标号集生长，加入v1（新的最近节点）
    u=v1;%u即为新生长出的节点
end

min=label(terminal); 
path(1)=terminal;%将终点编号存入path
i=1;
while path(i)~=start%从terminal往前找节点的 父节点 ，一直找到某节点的父节点为start为止
    path(i+1)=f(path(i));%将当前节点的父节点作为路径的上一步，找到start即成功
    i=i+1 ;
end
path(i)=start;
L=length(path);
path=path(L:-1:1);%将path颠倒，使起点在前，再输出
