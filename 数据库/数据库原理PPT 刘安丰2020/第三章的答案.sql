 --12����ʾscore����������5��ѧ��
--ѡ�޵Ĳ���3��ͷ�Ŀγ� 
  --�ŵ�ƽ������
select * from score
select cno,count(*) from score 
group by cno;
select cno,avg(degree) from score where
cno like '3%' group by cno having
count(*)>=5;
--13����ʾ��ͷִ���70��
--��߷�С��90 ��sno�С�
select sno from score group by sno
having min(degree)>70 and max(degree)<99

select * from score where 
degree between 70 and 90
--14����ʾ����ѧ���� sname�� cno��degree�С�
select sname,cno,degree from student
join score on student.sno=score.sno
--15����ʾ����ѧ���� sname�� 
---cname��degree�С�
select sname,cname,degree from student
join score on student.sno=score.sno join
course on course.cno=score.cno
--16���г���95033������ѡ�γ̵�ƽ���֡�
select class,avg(degree) from student
join score on student.sno=score.sno
where class='95033'
group by class having avg(degree)>=60
--17����ʾѡ�ޡ�3-105���γ̵�
--�ɼ����ڡ�109����ͬѧ�ɼ���
  --      ����ͬѧ�ļ�¼��
select * from score where cno='3_105'
and degree>
(select degree from score where cno='3_105'
and sno=109)
--18����ʾscore��ѡ�޶��ſγ̵�ͬѧ
--�з���Ϊ����߷ֳ�
--���ļ�¼��
select sno from score where degree<
(select max(degree) from score)
group by sno having count(*)>1;
----------

Select a.sno, a.degree, a.cno from 
score  a, score b
Where a.sno=b.sno and a.degree<b.degree
select * from student
---20����ʾ����ѧ��Ϊ��108��
--��ͬѧͬ�����������ѧ����
  --sno��sname�� birthday�С�
select sno,sname,birthday from student
where year(birthday)=
(select year(birthday) from student where 
sno='108')
--21����ʾ���Ż�����ʦ�οε�ѧ���ɼ���
select * from teacher;
select * from course;
select * from score;
select * from score where cno=
(select cno from course where tno=
(select tno from teacher where tname='�Ż�'))
--22����ʾѡ��ĳ�γ̵�ͬѧ
--��������5�˵���ʦ������
--1scoreѡȡѡ�ζ�5�˵�����Щ�Σ��õ�cno
--2course����Щ�ζ�����Щ��ʦ���ϣ��õ���ʦ��tno
--3��teacher����Щtno��������ʲô��
select tname from teacher where tno in
(select tno from course where cno in
(select cno from score group by cno
having count(*)>=5))
--23����ʾ��95033����
--�͡�95031����ȫ��ѧ���ļ�¼
select * from student where 
class ='95033' or class='95031';
--24����ʾ������85�����ϳɼ��Ŀγ�cno
select distinct cno from score
 where degree>85;
select cno from score where degree>85 
group by cno

select distinct cno from score where cno in
(select cno from score where degree>85)
--25����ʾ�������ϵ����ʦ���̿γ̵ĳɼ���
select * from score where cno in
(select cno from course where tno in
(select tno from teacher where 
depart='�����ϵ'))
--26����ʾ�������ϵ���͡�
--���ӹ���ϵ����ְͬ�Ƶ���ʦ��
  --       tname��prof��
--��ʾ�����ϵ�е�ְ�ƣ������ӹ���ϵû��ְ��
--�ļ����ϵ����ʦ��������ְ��

select * from teacher

select * from teacher where proff not in 
(select proff from teacher 
where depart='���ӹ���ϵ')
and depart='�����ϵ'
--27����ʾѡ�ޱ��Ϊ��3-105���γ��ҳɼ�����
--���ڡ�3-245���γ̵�ͬѧ��cno��sno��degree��
--����degree�Ӹߵ��ʹ������С�
select * from score where cno='3_105'
and degree>(select min(degree) from score 
                where cno='3_245')
order by degree desc;
--28����ʾѡ�ޱ��Ϊ��3-105��
--�γ��ҳɼ����ڡ�3-245���γ̵�ͬ
  --       ѧ��cno��sno��degree��

select * from score where cno='3_105'
and degree>(select max(degree) from score 
                where cno='3_245')
order by degree desc;

--29���г������ο���ʦ��tname��depart��
select tname,depart from teacher where tno in
(select tno from course)
--30���г�����δ������ʦ��tname��depart��
select tname,depart from teacher 
where tno not in (select tno from course)
--31���г�������ʦ��ͬѧ�� �������Ա�����ա�
select * from teacher;
select * from student;
select tname,sex,birthday from teacher
union
select sname,sex,birthday from student
--*32��������ѧ�γ̰���ѧ����103����ѧ�γ̵�
--ѧ��ѧ�š�











