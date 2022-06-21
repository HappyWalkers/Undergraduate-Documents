drop database if exists KindlePushv2;
create database KindlePushv2;
use kindlepushv2;
drop table if exists bookinfo;
create table bookinfo(
                         bookid int auto_increment primary key,
                         bookname varchar(200),
                         author varchar(200),
                         description varchar(5000),
                         covername varchar(1000),
                         path varchar(1000),
                         date varchar(200)
);

drop table if exists userinfo;
create table userinfo(
                         userid int auto_increment primary key,
                         username varchar(200),
                         userpwd varchar(200),
                         email varchar(200),
                         kindle_email varchar(200)
);

