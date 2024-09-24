mysql procedure

DECLARE A INT;
SET A = 123;
SELECT A    // RESULTS
SELECT B    //  A + B 2RESULTS

DELIMITER $$
DELIMITER ;

DROP PROCEGURE IF EXISTS hello(in_value int, OUT ret_value int);
DELIMITER $$
begin


end$$
DELIMITER ;


####  条件

###### IF  THEN ELSEIF THEN  ELSE END IF;
```
DROP PROCEDURE IF EXISTS discount_price;
DELIMITER $$
create procedure discount_price(normal_price numeric(8,2), OUT discount_price NUMERIC(8,2))
BEGIN
    IF(normql_price >50) THEN
        set discount_price = normal_price*0.8;
    elseif(normal_price > 1000) then
        set discount_price = normal_price*0.9;
    else 
        set discount_price = normal_price;
    end if;
end $$
DELIMITER;
```
######  LOOPS
####### 1. simple `LOOP  .. [LEAVE] ..  END LOOP`

```
CREATE PROCEDURE simple_loop()
begin
    DECLARE counter INT DEFAULT 0;

    my_simple_loop: LOOP
        set counter = counter +1;
        if counter = 10 then 
            LEAVE my_simple_loop;
        end if;
    end loop my_simple_loop;
    select 'i can count to 10';    
end
```


####### 2. `WHILE  ... END WHILE`
####### 3. `REPEAT ... UNTIL`

### 存储过程的错误处理
存储过程出错,mysql会终止程序的执行,并将错误传递给调用程序,但是如果你希望另外一种相应错误的方法,
你可以创建一个 error handler,它定义了存储过程程序如果相应一种或者多种错误状况.
    场景:
        1. 用 cursor 获取行 结果出现 NOT FOUND. NOT FOUND error handler 可以免于报错
        2. 违反约束条件,报错
 

#### 与数据库的交互
 - Store the results of a SQL statement that returns a single row into local variables
 - Create a “cursor” that allows the stored program to iterate through the rowsreturned by a SQL statement
 - Execute a SQL statement, returning the result set(s) to the calling program.
 - Embed a SQL statement that does not return a result set,such as INSERT,UPDATE,DELETE, etc.

 ##### 1. select into  , select (没有into) 可以从存储过程中返回result sets
    SELECTING INTO  LOCAL Variables
    单行查询
 
 ##### 2. 使用cursors

```
    DECLARE handler_action HANDLER
        FOR condition_value [, condition_value] ...
        statement

    handler_action: {
        CONTINUE
    | EXIT
    | UNDO
    }

    condition_value: {
        mysql_error_code
    | SQLSTATE [VALUE] sqlstate_value
    | condition_name
    | SQLWARNING
    | NOT FOUND
    | SQLEXCEPTION
    }
```


 ```
delimiter $$
dorp procedure if exists cursor_example$$
create procedure cursor_example()
    READS SQL DATA
begin
    DECLARE l_employee_id int;
    declare l_salary numeric(8,2);
    declare l_department_id int;

    declare done int default 0;

    declare cur1 CURSOR for select employee_id,salary,department_id from employees;

    declare CONTINUE HANDLER for NOT FOUND SET done = 1;

    OPEN cur1;

    employee_loop:LOOP
        fetch cur1 INTO l_employee_id,l_salary,l_department_id;
        if done = 1 then 
            LEAVE employee_loop;
        end if;
    END LOOP employee_loop;
    
    CLOSE cur1;
end$$
delimiter ;
 ```

 ##### 2. non-select
 update delete insert ...

 ##### call procdeure in a procedure



##### create trigger

```
CREATE TRIGGER sales_bi_trg
    before insert on sales
    for each row

begin 

end
```

### language foundations
1. data types

2. declare v-name1[,v-name2  ...] type  [default v]

3. 赋值  set v = a , v2 = b [, v3 = c ...];

4. 参数  IN INOUT OUT
CREATE PROCEDURE XXX(   [
         [IN|OUT|INOUT] paramter data_type ...
                        ]
         )



#### block

```
    create procedure  nested_blocks5()
    outer_block:BEGIN
        DECLARE l_status int;
        inner_block : begin
            if(l_status = 1) then 
                leave inner_block;
            end if;

            select 'this statement will never be executed'
        end inner_block
        select 'end of program'
    end outer_block$$
```

```
    IF ... THEN
    ELSEIF .... THEN
    END IF;
```

```
CASE expression
    when value then
        statements
    when value then 

    else
        statements
end case;
```

#### `searched` CASE statement
```
    CASE 
        WHEN condition then 
            statement
        WHEN condition2 then 
            ...
        ELSE
            ...
    END CASE;
```

#### ITERATE 
    相当于 continue

```
    set i = 0;
    loop1: LOOP
        SET i = i + 1;
        if i > 10 then 
            leave loop1;
        elseif mod(i,2) = 0 then 
            iterate;
        end if;

        SELECT CONTACT(i,'is an odd number')
    end loop loop1;
```

#### repeat

```
    set i = 0;
    loop1: REPEAT
            SET i = i+1;
            if(mod(i,2) <>0) then 
                select contact(i,'is an odd number');
            end if;
    until i > 10
    end repeat;
```

#### while 
```
    set i = 0;
    loop1 : WHILE i < 10 do
        if mod(i,2) <> 0 then 
            select contact(i, " is an odd number);
        end if;
        set i = i + 1;
    end while loop1;

## 5 using sql in stored programming
    1. none-select
    2. select into      //if multi rows erros
    3. select multi-rows  to loop through 
    
    4. creating and using cursor
        4.1 define cursor
            DECLARE cursor_name  CURSOR for select_statement
            ```
                create procedure bad_cursor()
                begin
                    declare c cursor for select * from departments;
                    declare i int;      // 错误 ,cursor的声明必须在所有变量声明之后
            ```

            ```
                create procedure cursor_demo(in_custom_id INT)
                BEGIN
                    declare v_custom_id INT;
                    declare v_custom_name VARCHAR(30);
                    DECLARE C1 cursor for 
                        select in_custom_id,customer_name 
                        from customers
                        where customer_id = in_customer_id;
            ```
        4.2 cursor state
            open  open cursor1
            fetch   fetch cursor1 into VARIABLE list
            close

            ```
            DECLARE CONTINUE HANDLER FOR NOT FOUND SET l_last_row_fetched = 1;
            DECLARE c_dept cursor for 
                select depart_id from departments;
            
            open c_dept;
            dept_cursor:LOOP
                fetch c_dept into l_dept_id;
            end loop dept_cursor;
            CLOSE c_dept;
            ```

#### 将结果集传递给另一个存储过程  通过  临时表

```
create procedure sp_overdue_sales()
begin
    drop temporary table  if exists overdue_sales_tmp;
    create temporary table overdue_sales_tmp as 
        as select sales_id,customer_id,sale_date,quantity,sale_value from sales 
        where sale_status = '0';
end
```

##### PREPARE STATEMENTS
`PREPARE statement_name from sql_text;`

```
一、SQL 语句的执行处理
1、即时 SQL
　　一条 SQL 在 DB 接收到最终执行完毕返回，大致的过程如下：
　　1. 词法和语义解析；
　　2. 优化 SQL 语句，制定执行计划；
　　3. 执行并返回结果；
　　如上，一条 SQL 直接是走流程处理，一次编译，单次运行，此类普通语句被称作 Immediate Statements （即时 SQL）。
2、预处理 SQL
　　但是，绝大多数情况下，某需求某一条 SQL 语句可能会被反复调用执行，或者每次执行的时候只有个别的值不同（比如 select 的 where 子句值不同，update 的 set 子句值不同，insert 的 values 值不同）。如果每次都需要经过上面的词法语义解析、语句优化、制定执行计划等，则效率就明显不行了。
　　所谓预编译语句就是将此类 SQL 语句中的值用占位符替代，可以视为将 SQL 语句模板化或者说参数化，一般称这类语句叫Prepared Statements。
　　预编译语句的优势在于归纳为：一次编译、多次运行，省去了解析优化等过程；此外预编译语句能防止 SQL 注入。
```

``` 
# 定义预处理语句
PREPARE stmt_name FROM preparable_stmt;
# 执行预处理语句
EXECUTE stmt_name [USING @var_name [, @var_name] ...];
# 删除(释放)定义
{DEALLOCATE | DROP} PREPARE stmt_name;
```

```
    PREPARE prod_insert_stmt FROM  "insert into product_codes values(?,");

    set @code="DB";
    set @name="MySql Query Browsers";
    EXECUTE  prod_insert_stmt using @code,@name;
```

```
create procedure execut_sql(in_sql varchar(4000))
begin
    set @tmp_sql = in_sql;
    PREPARE s1  from @tmp_sql;
    execute s1;
    deallocate PREPARE s1;
end;

```