 --39��
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
--40��
--(1)
select sc.sno,cno,grade into cs_sc from sc
join student on sc.sno=student.sno 
where sdept='�����ϵ' and grade>80

create table cs_sc1(
sno char(10),
cno char(10),
grade int
);
insert into cs_sc1(sno,cno,grade)
select sc.sno,cno,grade from sc
join student on sc.sno=student.sno 
where sdept='�����ϵ' and grade>80 

select * from cs_sc1
--41��
delete from sc where grade<50
--42��
--(1)
delete from sc where grade<50 and sno in
(select sno from student where sdept='��Ϣϵ')
--(2)
delete from sc from sc join student 
on sc.sno=student.sno where grade<50
and sdept='��Ϣϵ'
--43��
update sc set grade=grade+10 where cno='001'
--44��
update sc set grade=grade+10
where cno in
(select cno from course where cname='���������')
and sno in
(select sno from student where sdept='�����ϵ')
--(2)
update sc set grade=grade+10
from sc join student on sc.sno=student.sno
join course on course.cno=sc.cno
where sdept='�����ϵ' and cname='���������'
--45��

--�����ҵ�VB���ſε�cno
--select cno from course where cname='VB'
--Ȼ�����cno �ҵ����ſ���С�ĳɼ�
--select min(grade) from sc where cno in
--(select cno from course where cname='VB')
--ɾ���ɼ�=�����С�ɼ������γ̱��=VB�Ŀγ̱��
delete from sc where grade=
( select min(grade) from sc where cno in
   (select cno from course where cname='VB')
 )
and cno=
(select cno from course where cname='VB')


select * from cs_sc 