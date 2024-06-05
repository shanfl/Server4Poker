drop database if exists sp_user;
create database if not exists sp_user character set utf8mb4;
use sp_user;
drop table if exists `user`;
create table if not exists `user`
(
	uid 	bigint not null,
    name    varchar(255),
    pass    varchar(255),
    nickname varchar(255),
    sex     int,    
    figure  text,
    flag    int ,
    banned  int not null default 0,
    `created_at` timestamp DEFAULT current_timestamp COMMENT '创建时间',
    `updated_at` timestamp null on update current_timestamp COMMENT '更新时间',
    primary key(uid)
);