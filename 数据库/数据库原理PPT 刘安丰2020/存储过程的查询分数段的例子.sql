create table countsc (
fengshu int,
geishu  int
) 
drop proc fenshusc
CREATE procedure fenshusc --��������5��һ��ͳ��
AS 
begin
declare  @counter int
declare  @i int
declare  @j int
declare  @returnvalue int
set @i=5;
delete from countsc
while(@i<=100) --ͳ�Ʒ�����ͳ���ж��ٸ��ɼ�
 begin 
   insert into countsc(fengshu,geishu) 
   select @i ,count(*)from sc where grade<=@i
  set  @i=@i+5
 end
end
insert into sc values('111','003',4)
insert into sc values('111','005',12)
insert into sc values('111','006',7)

execute fenshusc

select * from countsc 