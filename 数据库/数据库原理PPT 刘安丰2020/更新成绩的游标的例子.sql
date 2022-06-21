 declare in_c1 cursor for select 
sno,cno,grade from sc for update of grade
--游标与一个查询语句相关联
--可以更新成绩列
open in_c1
--打开游标，执行对应的查询语句。
--而且游标指向了查询结果的第一条记录

declare @sno1 char(10),@cno1 char(8),
         @grade1 int --定义变量
fetch next from in_c1 into @sno1,@cno1,@grade1
--从游标中取得第一记录内容存入变量
while @@fetch_status=0
--如果最近的一次fetch 语句有结果返回则
-- @@fetch_status=0，否则不为0
--判断获取是否成功，即记录是否取得完成
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
---根据成绩来更新成绩
fetch next from in_c1 into @sno1,@cno1,@grade1
--再次取数据，这条语句不可少，否则无法循环。
end
go
close in_c1
go
select * from sc