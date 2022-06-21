function [min,path]=dijkstra(w,start,terminal)
n=size(w,1);
label(start)=0;%labelΪ�ɸ��ı�ż��ϣ�T��
f(start)=start;%fΪ���ڵ㼯�ϣ���һ�����ڵ㼴Ϊstart
for i=1:n%start֮���label����ֵΪinf
    if i~=start
        label(i)=inf;
    end
end

s(1)=start;%sΪ�̶���ż�
u=start;%u��ʼ��Ϊstart  %u��Ϊ���������Ľڵ�

while length(s)<n%�����еĽڵ����̶���ż�����������е�����·��
    
    for i=1:n%���ݵ�ǰ�ڵ㣬��������T���
        ins=0;
        
        for j=1:length(s)%����s��Ԫ��
            if i==s(j)%���s����Ԫ�غ͵�ǰi���
                ins=1;
            end
        end%�Ѿ��ڹ̶���ż��еĽڵ� �����ӵĽڵ� �������T���
        
        if ins==0%�ǹ̶���ż�
            v=i;%��v����i
            if label(v)>(label(u)+w(u,v))%ȡ��С����Ϊ�µ�T���
                label(v)=(label(u)+w(u,v));
                f(v)=u;%��f��¼ ���±�Žڵ� �ĸ��ڵ㣬f��Ӧ��ż�¼�ļ�Ϊ ����Žڵ�� ���ڵ�
            end
        end
    end%������֦�������²����Ľڵ��ڽӵĽڵ���Ҫ����T���
    
    v1=0;
    k=inf;
    
    for i=1:n%ѡ����ǰ���� �ɼ� T��ż��е���Сֵ ��Ϊ k�������´˽ڵ�
        ins=0;
        for j=1:length(s)%�̶���ż��е��������
            if i==s(j)
                ins=1;
            end
        end
        if ins==0%�ǹ̶���ż�
            v=i;%��v�洢i
            if k>label(v)%��С�߼�Ϊk
                k=label(v);
                v1=v;%��v1���´�ʱ��v���㣩
            end
        end
    end
    
    s(length(s)+1)=v1;  %sΪ�̶���ż����̶���ż�����������v1���µ�����ڵ㣩
    u=v1;%u��Ϊ���������Ľڵ�
end

min=label(terminal); 
path(1)=terminal;%���յ��Ŵ���path
i=1;
while path(i)~=start%��terminal��ǰ�ҽڵ�� ���ڵ� ��һֱ�ҵ�ĳ�ڵ�ĸ��ڵ�ΪstartΪֹ
    path(i+1)=f(path(i));%����ǰ�ڵ�ĸ��ڵ���Ϊ·������һ�����ҵ�start���ɹ�
    i=i+1 ;
end
path(i)=start;
L=length(path);
path=path(L:-1:1);%��path�ߵ���ʹ�����ǰ�������
