function objvalue=cal_objvalue(point,taxi)
%������·��
[a,b,c]=size(point);
distance=ones(1,b-1);
d=ones(1,a);
for i=1:a
    for j=1:b-1
        dx=abs(point(i,j+1,1)-point(i,j,1));
        dy=abs(point(i,j+1,2)-point(i,j,2));
        distance(1,j)=dx+dy;
    end
    d(1,i)=sum(distance);
end
alld=sum(d);
%�����ؿͳ���
for i=1:a
    flag=0;
    for j=1:b
        for k=1:c
            if point(i,j,k)==0
                num=i;
                flag=1;
                break
            end
        end
        if flag==1
            break
        end
    end
    if flag==1
        break
    end
end
%����һ�����⳵����һ���˿͵ľ��� 
dis=ones(1,a);
for i=1:a
    disx=abs(taxi(i,1)-point(i,1,1));
    disy=abs(taxi(i,2)-point(i,1,2));
    dis(1,i)=disx+disy;
end
di=sum(dis);
    %�������Ӧֵ
objvalue=di+alld+num*7.9;
end

