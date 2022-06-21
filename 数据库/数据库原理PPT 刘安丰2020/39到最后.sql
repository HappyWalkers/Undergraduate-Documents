 --39题
create table test_t (
col1 int,
col2 char(10) not null,
col3 char(10)
)
go
insert into test_t values(null,'b1',null);
insert into test_t(col2) values('b1');

insert into test_t(col1,col2,col3)
values(1,'b2','C2');
insert into test_t
values(1,'b2','C2');

insert into test_t values(2,'b3',null);
insert into test_t(col1,col2)
values(2,'b3');

insert into test_t values(null,'b4','C4');
go
select * from test_t
--40题
--(1)
select sc.sno,cno,grade into cs_sc from sc
join student on sc.sno=student.sno 
where sdept='计算机系' and grade>80

create table cs_sc1(
sno char(10),
cno char(10),
grade int
);
insert into cs_sc1(sno,cno,grade)
select sc.sno,cno,grade from sc
join student on sc.sno=student.sno 
where sdept='计算机系' and grade>80 

select * from cs_sc1
--41题
delete from sc where grade<50
--42题
--(1)
delete from sc where grade<50 and sno in
(select sno from student where sdept='信息系')
--(2)
delete from sc from sc join student 
on sc.sno=student.sno where grade<50
and sdept='信息系'
--43题
update sc set grade=grade+10 where cno='001'
--44题
update sc set grade=grade+10
where cno in
(select cno from course where cname='计算机网络')
and sno in
(select sno from student where sdept='计算机系')
--(2)
update sc set grade=grade+10
from sc join student on sc.sno=student.sno
join course on course.cno=sc.cno
where sdept='计算机系' and cname='计算机网络'
--45题

--首先找到VB这门课的cno
--select cno from course where cname='VB'
--然后根据cno 找到这门课最小的成绩
--select min(grade) from sc where cno in
--(select cno from course where cname='VB')
--删除成绩=这个最小成绩，而课程编号=VB的课程编号
delete from sc where grade=
( select min(grade) from sc where cno in
   (select cno from course where cname='VB')
 )
and cno=
(select cno from course where cname='VB')


select * from cs_sc 