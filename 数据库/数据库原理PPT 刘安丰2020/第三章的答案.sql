 --12、显示score表中至少有5名学生
--选修的并以3开头的课程 
  --号的平均分数
select * from score
select cno,count(*) from score 
group by cno;
select cno,avg(degree) from score where
cno like '3%' group by cno having
count(*)>=5;
--13、显示最低分大于70，
--最高分小于90 的sno列。
select sno from score group by sno
having min(degree)>70 and max(degree)<99

select * from score where 
degree between 70 and 90
--14、显示所有学生的 sname、 cno和degree列。
select sname,cno,degree from student
join score on student.sno=score.sno
--15、显示所有学生的 sname、 
---cname和degree列。
select sname,cname,degree from student
join score on student.sno=score.sno join
course on course.cno=score.cno
--16、列出“95033”班所选课程的平均分。
select class,avg(degree) from student
join score on student.sno=score.sno
where class='95033'
group by class having avg(degree)>=60
--17、显示选修“3-105”课程的
--成绩高于“109”号同学成绩的
  --      所有同学的记录。
select * from score where cno='3_105'
and degree>
(select degree from score where cno='3_105'
and sno=109)
--18、显示score中选修多门课程的同学
--中分数为非最高分成
--绩的记录。
select sno from score where degree<
(select max(degree) from score)
group by sno having count(*)>1;
----------

Select a.sno, a.degree, a.cno from 
score  a, score b
Where a.sno=b.sno and a.degree<b.degree
select * from student
---20、显示出和学号为“108”
--的同学同年出生的所有学生的
  --sno、sname和 birthday列。
select sno,sname,birthday from student
where year(birthday)=
(select year(birthday) from student where 
sno='108')
--21、显示“张化”老师任课的学生成绩。
select * from teacher;
select * from course;
select * from score;
select * from score where cno=
(select cno from course where tno=
(select tno from teacher where tname='张化'))
--22、显示选修某课程的同学
--人数多于5人的老师姓名。
--1score选取选课多5人的是哪些课，得到cno
--2course看这些课都是哪些老师来上，得到教师的tno
--3在teacher看这些tno的姓名是什么？
select tname from teacher where tno in
(select tno from course where cno in
(select cno from score group by cno
having count(*)>=5))
--23、显示“95033”班
--和“95031”班全体学生的记录
select * from student where 
class ='95033' or class='95031';
--24、显示存在有85分以上成绩的课程cno
select distinct cno from score
 where degree>85;
select cno from score where degree>85 
group by cno

select distinct cno from score where cno in
(select cno from score where degree>85)
--25、显示“计算机系”老师所教课程的成绩表。
select * from score where cno in
(select cno from course where tno in
(select tno from teacher where 
depart='计算机系'))
--26、显示“计算机系”和“
--电子工程系”不同职称的老师的
  --       tname和prof。
--显示计算机系有的职称，而电子工程系没有职称
--的计算机系的老师的姓名和职称

select * from teacher

select * from teacher where proff not in 
(select proff from teacher 
where depart='电子工程系')
and depart='计算机系'
--27、显示选修编号为“3-105”课程且成绩至少
--高于“3-245”课程的同学的cno、sno和degree，
--并按degree从高到低次序排列。
select * from score where cno='3_105'
and degree>(select min(degree) from score 
                where cno='3_245')
order by degree desc;
--28、显示选修编号为“3-105”
--课程且成绩高于“3-245”课程的同
  --       学的cno、sno和degree。

select * from score where cno='3_105'
and degree>(select max(degree) from score 
                where cno='3_245')
order by degree desc;

--29、列出所有任课老师的tname和depart。
select tname,depart from teacher where tno in
(select tno from course)
--30、列出所有未讲课老师的tname和depart。
select tname,depart from teacher 
where tno not in (select tno from course)
--31、列出所有老师和同学的 姓名、性别和生日。
select * from teacher;
select * from student;
select tname,sex,birthday from teacher
union
select sname,sex,birthday from student
--*32、检索所学课程包含学生“103”所学课程的
--学生学号。











