drop database if exists sp_user;
create database if not exists sp_user character set utf8mb4;
use sp_user;
drop table if exists `user`;
create table if not exists `user`
(
	uid 	bigint not null,
    name    varchar(255),
    sex     int,
    pass    varchar(255),
    figure  text,
    flag    int ,
    banned  int not null default 0,
    primary key(uid)
);