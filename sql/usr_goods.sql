drop database if exists sp_goods;
create database if not exists sp_goods character set utf8mb4;
use sp_goods;
drop table if exists `goods`;
create table if not exists `goods`
(
	uid 	bigint not null,
    gid     bigint not null,
    cnt     int not null default 0,
    primary key(uid,gid)
);