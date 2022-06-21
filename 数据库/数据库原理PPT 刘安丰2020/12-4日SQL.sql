 
declare @w char(20)
declare @ss char(4)
select  @w=sname,@ss=ssex 
      from student  where sno='101'

if (@ss='男')
  begin
         print @w+'是个男同志'
   end
else
   begin
         print @w+'是个女同志'
   end


declare @w char(20)
declare @ss char(4)
select  @w=sname,@ss=ssex 
      from student  where sno='101'

if (@ss='男')
  begin
        update sc set grade=grade+5 where sno='101'
   end
else
   begin
        update sc set grade=grade+10 where sno='101'
   end

---看一看100同学的最小成绩>=60.如果>=60的话
--就打印出‘这是个好同志'，否则打印出'还要努力'.
declare @cc int
select @cc=min(grade) from sc where sno='100'
if (@cc<60)
  print '还要努力!'
else
 print '这是个好同志!'
---看一看100同学的最小成绩>=60.如果>=60的话
--就打印出‘这是个好同志'，
--否则打印出'还要努力'，
--然后把这个同学不及格的成绩变为60分.
declare @cc int
select @cc=min(grade) from sc where sno='100'
if (@cc<60)
 begin
   print '还要努力!'
   update sc set grade=60 where sno='100' and grade<60
 end
else
  print '这是个好同志!'



--计算1+2+3+...+100的和
declare @i int,@sum int  --定义二个变量@i和@sum
set @i=1                           --让变量@i=1
set @sum=0                     --和的结果初始值为0
while (@i<=100)         --只要变量@i<=100,就进行下面的循环
   begin
       set @sum=@sum+@i  --每次加一个@i
       print 'i的值='+ cast(@i as char(4))
       print '中间和的值=' + cast(@sum as char(4))
       set @i=@i+1                --每次@i增长1
   end
print @sum          --打印最后的和

 
declare @a int ,@b int ,@c int
select @a=1,@b=1,@c=20
while (@c>0)
 begin
  set @b=@b+3
  set @a=@a+@b
  if @b<10
      continue
     set @c=@c-5
    select @a,@b,@c
End

declare in_c1? cursor for select 教师姓名,职称,工资 from 教师表 order by 工资 for update of? 工资
open in_c? ——声明一个只进游标，但可以更新工资列。
declare @nin money ,@name char(8),@zc char(10)? --定义变量
fetch next from in_c? into @name,@zc,@nin?? --从游标中取得第一记录内容存入变量
while @@fetch_status=0? --判断获取是否成功，即记录是否取得完成
begin
if @zc='教授'or @zc=’副教授’
?? update 教师表 set 工资=工资+200 where current of in_c
else 
update 教师表 set 工资=工资+100 where current of in_c
fetch next from in_c? into @name,@zc,@nin?? --再次取数据，这条语句不可少，否则? 无法循环。end????????????????????????????????????
Go
Close in_c1? ——关闭游标


---对成绩表按不同的分数段加不同的成绩
--delare 游标名 cursor for select 语句
declare @xuehao char(10),@kechenghao char(10)
declare @chenji int
declare cc1 cursor for 
     select sno,cno,grade  from sc  --定义游标cc1
 open cc1     --打开游标;执行与游标相关联的查询语
fetch next from cc1 into @xuehao,@kechenghao,@chenji
--从游标中取得第一记录内容存入变量
while @@fetch_status=0  --判断获取是否成功，即记录是否取得完成
   begin
  if @chenji<60
         print @xuehao+@kechenghao+'不及格'
    else
          print @xuehao+@kechenghao+'及格'
fetch next from cc1 into @xuehao,@kechenghao,@chenji
  end
close cc1
go


---对成绩表按不同的分数段加不同的成绩
--delare 游标名 cursor for select 语句
declare @xuehao char(10),@kechenghao char(10)
declare @chenji int
declare cc2 cursor for 
      select sno,cno,grade  from sc 
                 for update of grade
     --定义游标cc2
 open cc2     --打开游标;执行与游标相关联的查询语
fetch next from cc2 into @xuehao,@kechenghao,@chenji
--从游标中取得第一记录内容存入变量
while @@fetch_status=0  --判断获取是否成功，即记录是否取得完成
   begin
   if @chenji>100
         update sc set grade=100
                   where current of cc2
 fetch next from cc2 into @xuehao,@kechenghao,@chenji
 end
close cc2
go




---对成绩表按不同的分数段加不同的成绩
--delare 游标名 cursor for select 语句
declare @xuehao char(10),@kechenghao char(10)
declare @chenji int
declare cc3 cursor for 
      select sno,cno,grade  from sc 
                 for update of grade
     --定义游标cc2
 open cc3     --打开游标;执行与游标相关联的查询语
fetch next from cc3 into @xuehao,@kechenghao,@chenji
--从游标中取得第一记录内容存入变量
while @@fetch_status=0  --判断获取是否成功，即记录是否取得完成
   begin
   if @chenji>90
         update sc set grade=grade+3
                   where current of cc3
   else
       if @chenji>80
         update sc set grade=grade+5
                   where current of cc3
   else
      if @chenji>70
         update sc set grade=grade+7
                   where current of cc3 
   else
       if @chenji>60
         update sc set grade=grade+8
                   where current of cc3
    else
       update sc set grade=grade+8
                   where current of cc3
 fetch next from cc3 into @xuehao,@kechenghao,@chenji
 end
close cc3
go


create procedure yyy  
    as 
   select * from sc

exec yyy

drop proc  yyy

create procedure student_grade3
  @student_name char(10),
  @course_name char(20)='数据库'
as 
  select sname,cname,grade
    from student s inner join sc on s.sno=sc.sno 
    inner join course c on c.cno=sc.cno
    where sname= @student_name
       and cname= @course_name

exec student_grade3 '王五' 
exec student_grade3 '王五','会计学'
exec student_grade3 
   @student_name ='王五', @course_name='数据库原理'
create proc p_student
  @dept char(20)='计算机系',
  @sex  char(2)='男',
  @age  int =10
as 
 select * from student
        where sdept=@dept
        and ssex=@sex
        and sage>=@age

exec p_student 
exec p_student '计算机系','男',2
exec p_student @sex='女'

create proc proc1
  @var1 int,
  @var2  int ,
  @var3  int output
as 
  set @var3=@var2*@var1
-----结束

declare @result int 
exec   proc1 5,7, @result output
print @result 

---创建一个存储过程，求每一个同学的平均成绩
create proc avg_grade
  as
     select sno,avg(grade) from sc group by sno
---存储过程结束
exec avg_grade  --执行存储过程
---创建一个存储过程，求给出一个学号的平均成绩
create proc avg_grade1 @sno char(10)
  as
     select avg(grade) from sc where sno=@sno
 
exec avg_grade1 '100'     
---用一条查询语句将所有同学的
--学号和平均成绩放到一个新表中
drop table sc1

select  sno,avg(grade) gra into sc1
        from sc group by sno
---创建一个存储过程
--求每一个同学的平均成绩放到刚刚创建的这个表
--先把所有成绩都删除
drop proc avg_grade2 
create proc avg_grade2 
     as
  delete from sc1
  insert into sc1 select  sno,avg(grade) gra 
      from sc group by sno
 select * from sc1

exec avg_grade2 


select  sno,avg(grade) gra into sc1
        from sc group by sno


drop proc total_gra

---统计每5分一段的人数有多少个.
create proc total_gra as
   declare @i  int
   delete from sc1 
   set @i=5
   while(@i<=120)
    begin
       insert into sc1  
            select '<'+cast(@i as char(3)), count(*)
                  from sc where grade<@i and grade>=@i-5
        set @i=@i+5
  end
exec  total_gra

create table total_grade12 
  (系  char(20),
   cno char(10),
   人数  int,
   分数段 char(20)
  )
drop proc ttota

create proc ttota as 
 delete from total_grade12
  insert into total_grade12 
      select sdept,cno,count(*),'>90' from student 
          join sc on student.sno=sc.sno
             where grade>=90    group by  sdept,cno
insert into total_grade12 
      select sdept,cno,count(*),'80-90' from student 
          join sc on student.sno=sc.sno
             where grade>=80 and grade <90 
                   group by  sdept,cno
insert into total_grade12 
      select sdept,cno,count(*),'70-80' from student 
          join sc on student.sno=sc.sno
             where grade>=70 and grade <80 
                   group by  sdept,cno
insert into total_grade12 
      select sdept,cno,count(*),'60-70' from student 
          join sc on student.sno=sc.sno
             where grade>=60 and grade <70 
                   group by  sdept,cno
insert into total_grade12 
      select sdept,cno,count(*),'<60' from student 
          join sc on student.sno=sc.sno
             where grade<60 
                   group by  sdept,cno
----结束
exec ttota