 --1��
select  * from student;
select * from sc;
--2��
select sname,sage from student where sdept='�����ϵ';
--3��
select sno,grade from sc where cno='001';
--4��
select sno,cno,grade from sc where grade
between 70 and 80; 
--����
select sno,cno,grade from sc where grade>=70 
and grade<=80;
--5��
select sname,sage from student where sdept='�����ϵ'
and sage between 18 and 20 and ssex='��'
--6��
select sno,sc.cno,cname,grade from sc join course on
sc.cno=course.cno where sc.sno='101'
--7��
select max(grade) from sc where cno='001'
--8��
select distinct cno from  sc
--9��
use northwind
select orderdate,orderid,customerid from orders;
--10��
select orderid,customerid,shipcountry from orders
where shipcountry like '[BCDEF]_a%'
--11��
select orderid,customerid,shipcountry from orders
where shipcountry like '[^BCDEF]%a'
--12��
use master
select max(sage),MIN(sage) from student;
--13��
select avg(grade),max(grade),min(grade) from sc
where cno='002';
--14��
select sdept,count(*) from student group by sdept;
--15��
select cno,count(*),max(grade) from sc group by cno;
--16��
select sno,count(*) as total from sc group by sno 
order by  total
--17��
select sdept,count(*),avg(grade) from student join sc 
on student.sno=sc.sno group by sdept; 
--18��
select sno,avg(grade),count(*) from sc group by sno
having count(*)>2;
--19��
select sno,sum(grade) from sc group by sno
 having sum(grade)>200;
--20��
use pubs;
select type,avg(price),max(price) from titles
group by type having avg(price)>$12;
--21��
select type,count(*),avg(price) from titles
where royalty=10 group by type;
--22��
select type,sum(price) from titles
group by type having count(*)>3;
--23��
use master;
select sname,sdept from student join sc 
on student.sno=sc.sno where cno='002';
--����
select snamE,sdept from student where sno in
(SELECT SNO FROM SC WHERE CNO='002')
--24��
select sname,cno,grade from student join sc
on student.sno=sc.sno where grade>80 
order by grade desc;
--25��
select sname,ssex,grade from student join sc on
sc.sno=student.sno join course
on course.cno=sc.cno where sdept='�����ϵ'
and cname='���ݿ�ԭ��'
--26��
select sc.sno,sname,cno,grade from student
left outer join sc on sc.sno=student.sno;
--27��
--δѧ
