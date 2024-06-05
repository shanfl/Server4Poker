
drop database if exists uid_map;

create database if not exists uid_map character set utf8mb4;

use uid_map;

create table if not exists next_id(id int primary key not null, nextid bigint );
insert into next_id value(1,10000000);

delimiter $$
create procedure GetNextId(out result int,out _nextid bigint)
begin 
    set result = 1;

    select nextid into _nextid from next_id where id = 1;    
    update next_id set nextid = _nextid + 1 where id = 1;
    
    set result = 0;
end$$
delimiter ;

/*
    use uid_map;
    
    call GetNextId(@res,@id);
    select @res,@id;
    select * from next_id ;
*/