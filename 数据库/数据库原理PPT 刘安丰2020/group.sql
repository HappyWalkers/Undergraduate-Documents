 select sdept,count(*) as ѧ������, avg(sage) as 
ƽ������ from student group by sdept 

select sdept,count(*) Ů������ from student where
ssex='Ů' group by sdept

select sdept,ssex,count(*) ����,max(sage) �������
 from student group by sdept,ssex order by sdept

use pubs
go
select royalty,avg(price*2) as ƽ���۸� from titles
group by royalty

select royalty,avg(price*2) as ƽ���۸� from titles
where royalty is not null group by royalty

use master
select sno,count(*) from sc group by sno 
having  count(*)>3
go

select sno,ƽ���ɼ�=avg(grade),�޿�����=count(*)
from sc group by sno having count(*)>=4

use pubs
go
select type,count(*)as ���� from titles group by type
having count(*)>1

use pubs
select type,count(*) ���� from titles group by type
having type like 'p%'
go

select type,count(*) ���� from titles 
where type like 'p%' 
group by type
go

select pub_id,sum(advance) as ��Ԥ����,avg(price) 
as ƽ���۸� from pubs.dbo.titles
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

select type,avg(price) as ƽ���۸� from titles
where royalty=10 group by type
go

select type,avg(price) as ƽ���۸� from titles
where royalty=10 group by all type
go







