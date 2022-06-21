 --我们先删除这三个表
drop table sc;
drop table student;
drop table course;
go
--创建学生表，表名是student
create table student (  
sno char(7) primary key,  --学号，是主码
sname char(10) not null,  --姓名
ssex char(2),          --性别
sage smallint,         --年龄
sdept varchar(20) --所在系
)  ;
--创建课程表，表名是course
create table course (
cno char(10) not null,  --课程编号
cname char(20) not null, --课程名称
ccredit smallint ,    --学分
semester smallint,  --此门课开课的学期
primary key(cno) --指明cno是主码
);
--创建成绩表，表名是sc
create table sc(
sno char(7) not null,   --学生编号
cno char(10) not null, --课程号
grade smallint ,    --成绩
primary key(sno,cno), --声明sno,cno是主码
foreign key(sno) references student(sno), 
--上面是声明sno是外健，参照student表的sno
foreign key(cno) references course(cno)
--上面是声明cno是外健，参照course表的cno
)

go
