 
declare @w char(20)
declare @ss char(4)
select  @w=sname,@ss=ssex 
      from student  where sno='101'

if (@ss='��')
  begin
         print @w+'�Ǹ���ͬ־'
   end
else
   begin
         print @w+'�Ǹ�Ůͬ־'
   end


declare @w char(20)
declare @ss char(4)
select  @w=sname,@ss=ssex 
      from student  where sno='101'

if (@ss='��')
  begin
        update sc set grade=grade+5 where sno='101'
   end
else
   begin
        update sc set grade=grade+10 where sno='101'
   end

---��һ��100ͬѧ����С�ɼ�>=60.���>=60�Ļ�
--�ʹ�ӡ�������Ǹ���ͬ־'�������ӡ��'��ҪŬ��'.
declare @cc int
select @cc=min(grade) from sc where sno='100'
if (@cc<60)
  print '��ҪŬ��!'
else
 print '���Ǹ���ͬ־!'
---��һ��100ͬѧ����С�ɼ�>=60.���>=60�Ļ�
--�ʹ�ӡ�������Ǹ���ͬ־'��
--�����ӡ��'��ҪŬ��'��
--Ȼ������ͬѧ������ĳɼ���Ϊ60��.
declare @cc int
select @cc=min(grade) from sc where sno='100'
if (@cc<60)
 begin
   print '��ҪŬ��!'
   update sc set grade=60 where sno='100' and grade<60
 end
else
  print '���Ǹ���ͬ־!'



--����1+2+3+...+100�ĺ�
declare @i int,@sum int  --�����������@i��@sum
set @i=1                           --�ñ���@i=1
set @sum=0                     --�͵Ľ����ʼֵΪ0
while (@i<=100)         --ֻҪ����@i<=100,�ͽ��������ѭ��
   begin
       set @sum=@sum+@i  --ÿ�μ�һ��@i
       print 'i��ֵ='+ cast(@i as char(4))
       print '�м�͵�ֵ=' + cast(@sum as char(4))
       set @i=@i+1                --ÿ��@i����1
   end
print @sum          --��ӡ���ĺ�

 
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

declare in_c1? cursor for select ��ʦ����,ְ��,���� from ��ʦ�� order by ���� for update of? ����
open in_c? ��������һ��ֻ���α꣬�����Ը��¹����С�
declare @nin money ,@name char(8),@zc char(10)? --�������
fetch next from in_c? into @name,@zc,@nin?? --���α���ȡ�õ�һ��¼���ݴ������
while @@fetch_status=0? --�жϻ�ȡ�Ƿ�ɹ�������¼�Ƿ�ȡ�����
begin
if @zc='����'or @zc=�������ڡ�
?? update ��ʦ�� set ����=����+200 where current of in_c
else 
update ��ʦ�� set ����=����+100 where current of in_c
fetch next from in_c? into @name,@zc,@nin?? --�ٴ�ȡ���ݣ�������䲻���٣�����? �޷�ѭ����end????????????????????????????????????
Go
Close in_c1? �����ر��α�


---�Գɼ�����ͬ�ķ����μӲ�ͬ�ĳɼ�
--delare �α��� cursor for select ���
declare @xuehao char(10),@kechenghao char(10)
declare @chenji int
declare cc1 cursor for 
     select sno,cno,grade  from sc  --�����α�cc1
 open cc1     --���α�;ִ�����α�������Ĳ�ѯ��
fetch next from cc1 into @xuehao,@kechenghao,@chenji
--���α���ȡ�õ�һ��¼���ݴ������
while @@fetch_status=0  --�жϻ�ȡ�Ƿ�ɹ�������¼�Ƿ�ȡ�����
   begin
  if @chenji<60
         print @xuehao+@kechenghao+'������'
    else
          print @xuehao+@kechenghao+'����'
fetch next from cc1 into @xuehao,@kechenghao,@chenji
  end
close cc1
go


---�Գɼ�����ͬ�ķ����μӲ�ͬ�ĳɼ�
--delare �α��� cursor for select ���
declare @xuehao char(10),@kechenghao char(10)
declare @chenji int
declare cc2 cursor for 
      select sno,cno,grade  from sc 
                 for update of grade
     --�����α�cc2
 open cc2     --���α�;ִ�����α�������Ĳ�ѯ��
fetch next from cc2 into @xuehao,@kechenghao,@chenji
--���α���ȡ�õ�һ��¼���ݴ������
while @@fetch_status=0  --�жϻ�ȡ�Ƿ�ɹ�������¼�Ƿ�ȡ�����
   begin
   if @chenji>100
         update sc set grade=100
                   where current of cc2
 fetch next from cc2 into @xuehao,@kechenghao,@chenji
 end
close cc2
go




---�Գɼ�����ͬ�ķ����μӲ�ͬ�ĳɼ�
--delare �α��� cursor for select ���
declare @xuehao char(10),@kechenghao char(10)
declare @chenji int
declare cc3 cursor for 
      select sno,cno,grade  from sc 
                 for update of grade
     --�����α�cc2
 open cc3     --���α�;ִ�����α�������Ĳ�ѯ��
fetch next from cc3 into @xuehao,@kechenghao,@chenji
--���α���ȡ�õ�һ��¼���ݴ������
while @@fetch_status=0  --�жϻ�ȡ�Ƿ�ɹ�������¼�Ƿ�ȡ�����
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
  @course_name char(20)='���ݿ�'
as 
  select sname,cname,grade
    from student s inner join sc on s.sno=sc.sno 
    inner join course c on c.cno=sc.cno
    where sname= @student_name
       and cname= @course_name

exec student_grade3 '����' 
exec student_grade3 '����','���ѧ'
exec student_grade3 
   @student_name ='����', @course_name='���ݿ�ԭ��'
create proc p_student
  @dept char(20)='�����ϵ',
  @sex  char(2)='��',
  @age  int =10
as 
 select * from student
        where sdept=@dept
        and ssex=@sex
        and sage>=@age

exec p_student 
exec p_student '�����ϵ','��',2
exec p_student @sex='Ů'

create proc proc1
  @var1 int,
  @var2  int ,
  @var3  int output
as 
  set @var3=@var2*@var1
-----����

declare @result int 
exec   proc1 5,7, @result output
print @result 

---����һ���洢���̣���ÿһ��ͬѧ��ƽ���ɼ�
create proc avg_grade
  as
     select sno,avg(grade) from sc group by sno
---�洢���̽���
exec avg_grade  --ִ�д洢����
---����һ���洢���̣������һ��ѧ�ŵ�ƽ���ɼ�
create proc avg_grade1 @sno char(10)
  as
     select avg(grade) from sc where sno=@sno
 
exec avg_grade1 '100'     
---��һ����ѯ��佫����ͬѧ��
--ѧ�ź�ƽ���ɼ��ŵ�һ���±���
drop table sc1

select  sno,avg(grade) gra into sc1
        from sc group by sno
---����һ���洢����
--��ÿһ��ͬѧ��ƽ���ɼ��ŵ��ոմ����������
--�Ȱ����гɼ���ɾ��
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

---ͳ��ÿ5��һ�ε������ж��ٸ�.
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
  (ϵ  char(20),
   cno char(10),
   ����  int,
   ������ char(20)
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
----����
exec ttota