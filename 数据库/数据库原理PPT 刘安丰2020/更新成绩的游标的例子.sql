 declare in_c1 cursor for select 
sno,cno,grade from sc for update of grade
--�α���һ����ѯ��������
--���Ը��³ɼ���
open in_c1
--���αִ꣬�ж�Ӧ�Ĳ�ѯ��䡣
--�����α�ָ���˲�ѯ����ĵ�һ����¼

declare @sno1 char(10),@cno1 char(8),
         @grade1 int --�������
fetch next from in_c1 into @sno1,@cno1,@grade1
--���α���ȡ�õ�һ��¼���ݴ������
while @@fetch_status=0
--��������һ��fetch ����н��������
-- @@fetch_status=0������Ϊ0
--�жϻ�ȡ�Ƿ�ɹ�������¼�Ƿ�ȡ�����
begin
update sc set grade =case
 when grade>=100 then 100
 when grade between 95 and 100 then 100
 when grade between 90 and 94 then grade+5
 when grade between 85 and 89 then grade+6
 when grade between 80 and 84 then grade+7
 when grade between 75 and 89 then grade+8
 when grade between 70 and 74 then grade+9
 when grade between 65 and 69 then grade+10
 when grade between 60 and 64 then grade+11
 else 65
end  where current of in_c1
---���ݳɼ������³ɼ�
fetch next from in_c1 into @sno1,@cno1,@grade1
--�ٴ�ȡ���ݣ�������䲻���٣������޷�ѭ����
end
go
close in_c1
go
select * from sc