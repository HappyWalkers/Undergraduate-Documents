 --������ɾ����������
drop table sc;
drop table student;
drop table course;
go
--����ѧ����������student
create table student (  
sno char(7) primary key,  --ѧ�ţ�������
sname char(10) not null,  --����
ssex char(2),          --�Ա�
sage smallint,         --����
sdept varchar(20) --����ϵ
)  ;
--�����γ̱�������course
create table course (
cno char(10) not null,  --�γ̱��
cname char(20) not null, --�γ�����
ccredit smallint ,    --ѧ��
semester smallint,  --���ſο��ε�ѧ��
primary key(cno) --ָ��cno������
);
--�����ɼ���������sc
create table sc(
sno char(7) not null,   --ѧ�����
cno char(10) not null, --�γ̺�
grade smallint ,    --�ɼ�
primary key(sno,cno), --����sno,cno������
foreign key(sno) references student(sno), 
--����������sno���⽡������student���sno
foreign key(cno) references course(cno)
--����������cno���⽡������course���cno
)

go
