函数原型：int server(string command, vector<vector<string> > &result)
    或者 int server(string command)
把sql命令输入参数command，二维数组result储存结果
  
  运算符只能满足等号和like，此like只能满足部分匹配;  数据类型只有string和int两种;
  
  特别提示：	若表名或者列名包含空字符，或者正好是sql解释语句，比如create、update等，需要用方括号包含名字; 		若值中存在方括号或者单引号，需要在其前方加转义字符\;			方括号和单引号的对数不超过54个，（因为逗号的ascii码是54,  此问题暂时保留）
  
  目前完成的语句：
1.	CREATE TABLE 表名称
(
列名称1 数据类型,
列名称2 数据类型,
列名称3 数据类型,
....
)		//括号内可以省略

2.	CREATE INDEX index_name ON table_name (column_name, ...)
//对表中列建索引，因为没有删除索引的功能，所以index name暂时没有什么用，可以省略

3.	ALTER TABLE table_name ADD column_name datatype

4.	ALTER TABLE table_name DROP COLUMN column_name

5.	DROP TABLE 表名称

6.	SELECT 列名称 FROM 表名称 WHERE 列 运算符 值
//列名称为 * 时选择所有列

7.	UPDATE 表名称 SET 列名称 = 新值 WHERE 列名称 = 某值		//where后可以省略

8.	DELETE FROM 表名称 WHERE 列名称 = 值

9.	INSERT INTO table_name (列1, 列2,...) VALUES (值1, 值2,.…)
//可以省略table name后面的括号，此时表示插入完整一行
