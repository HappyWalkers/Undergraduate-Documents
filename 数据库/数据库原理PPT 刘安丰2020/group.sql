 select sdept,count(*) as 学生人数, avg(sage) as 
平均年龄 from student group by sdept 

select sdept,count(*) 女生人数 from student where
ssex='女' group by sdept

select sdept,ssex,count(*) 人数,max(sage) 最大年龄
 from student group by sdept,ssex order by sdept

use pubs
go
select royalty,avg(price*2) as 平均价格 from titles
group by royalty

select royalty,avg(price*2) as 平均价格 from titles
where royalty is not null group by royalty

use master
select sno,count(*) from sc group by sno 
having  count(*)>3
go

select sno,平均成绩=avg(grade),修课门数=count(*)
from sc group by sno having count(*)>=4

use pubs
go
select type,count(*)as 数量 from titles group by type
having count(*)>1

use pubs
select type,count(*) 数量 from titles group by type
having type like 'p%'
go

select type,count(*) 数量 from titles 
where type like 'p%' 
group by type
go

select pub_id,sum(advance) as 总预付款,avg(price) 
as 平均价格 from pubs.dbo.titles
where pub_id>'0800'
group by pub_id
having sum(advance)>$15000
and avg(price)<$20
order by avg(price) asc

use pubs
go
select title_id,type,price,royalty from titles
order by type
go

select type,avg(price) as 平均价格 from titles
where royalty=10 group by type
go

select type,avg(price) as 平均价格 from titles
where royalty=10 group by all type
go







