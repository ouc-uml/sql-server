sql语句部分：
函数原型：	int server(string command, vector<vector<string> > &result)
     	   或者 int server(string command)
	把sql命令输入参数command，二维数组result储存结果
  
运算符只能满足等号、like、and、or，此like只能满足部分匹配;
数据类型只有string和int两种;
无法实现where嵌套。
方括号和单引号的对数不超过54个，（因为逗号的ascii码是54,  此问题暂时保留）
  
提示：	若表名或者列名包含空字符，或者正好是sql解释语句，比如create、update等，需要用方括号包含名字;
	若值中存在方括号或者单引号，需要在其前方加转义字符\;
  
  目前完成的语句：
1.	CREATE TABLE 表名称(列名称1 数据类型, 列名称2 数据类型, 列名称3 数据类型...)	//括号内可以省略
2.	CREATE INDEX index_name ON table_name (column_name, ...)//对表中列建索引，因为没有删除索引的功能，所以index name暂时没有什么用，可以省略
3.	ALTER TABLE table_name ADD column_name datatype
4.	ALTER TABLE table_name DROP COLUMN column_name
5.	DROP TABLE 表名称
6.	SELECT 列名称 FROM 表名称 WHERE 列 运算符 值			//列名称为 * 时选择所有列
7.	UPDATE 表名称 SET 列名称 = 新值 WHERE 列名称 = 某值		//where后可以省略
8.	DELETE FROM 表名称 WHERE 列名称 = 值
9.	INSERT INTO table_name (列1, 列2,...) VALUES (值1, 值2,.…)	//可以省略table name后面的括号，此时表示插入完整一行





所有表：
//所有时间的格式均为类似“2017.11.11.11”，所有string不超过64位
图书信息表(ISBN string, 书名 string, 类别 string, 编著人 string, 出版社 string, 入库时间 string, 负责人工号 string)
单本表(ISBN string, 单本编号 int, 状态 int)
//状态为1 保存本，2 非保存本在馆，3 已被借阅且未被预约，4 已被借阅且被预约，5 被预约且还回馆
用户表(账号 string, 密码 string, 昵称 string, 用户级别 int, 注册时间 string, 状态 int)
//状态为0正常
管理员表(账号 string, 密码 string, 管理员级别 int, 注册时间 string, 状态 int)
借阅表(账号 string, ISBN string, 单本编号 int, 借阅时间 string, 结束时间 string, 状态 int)
//状态为0视为已归还
预约表(账号 string, ISBN string, 单本编号 int, 预约时间 string, 终止时间 string, 状态 int)
//状态为0视为已得到书
荐购表(账号 string, ISBN string, 书名 string, 荐购时间 string, 状态 int)
//状态为0视为已处理
消息表(账号1 string, 账号2 string, 消息 string)
//第一个帐号发送者，第二个帐号接收者，第二个帐号为空时表示群发
权限表(角色 int, 级别 int, 表名 string, 增 int, 删 int, 查 int, 改 int)
//角色int 为0 管理员，1 用户;增删查改为1表示有权限。





接口函数：
int login(string userid, string passwd, bool role)
//登录，仅仅判断能否登录。role为0是管理员，成功返回0，密码或帐号错误返回1，帐号冻结返回2,
vector<string> get_message(string userid)
//返回用户收到的消息（来自所有管理员的所有消息）
vector<vector<string> > search_Bno(string bno, bool mode)
//根据isbn查询书，模式为0返回图书信息，模式为1返回单本信息
vector<vector<string> > search_Bclm(string clm_name, string val)
//根据列名，部分匹配查找
bool recommend(string bno, string bname, string userid)
//图书荐购，成功返回1,已存在返回0
vector<vector<string> > reader_history(string userid)
//返回读者借阅记录
vector<vector<string> > reader_current(string userid)
//返回读者正在借阅的书
vector<string> reader_info(string userid, bool role)
//读者自身信息,role为0是管理员
int borrow(string userid, string bno, unsigned int eno, string uno, int day)
//借书, 返回1 保存本，2 没有权限 3 已被借阅且未被预约，4 已被借阅且被预约,成功返回0
bool return_book(string userid, string bno, unsigned int eno)
//还书,成功返回1,userid是管理员帐号
bool add_book(string userid, vector<string> & book)
//增加图书,成功返回1,book顺序：ISBN, 单本编号, 是否保存本, 书名, 类别, 编著人, 出版社
//1是保存表，2不是
bool delete_book(string userid, string bno, unsigned int eno)
//删除图书,成功返回1
bool update_book(string userid, vector<string> clm_name, vector<string> val)
//修改图书属性
bool add_student(string userid, vector<string> & student)
//增加学生
bool delete_student(string userid, string uno)
//删除学生
bool update_student(string userid, vector<string> clm_name, vector<string> val)
//修改学生属性，成功返回1
vector<string> search_student_no(string userid, string uno)
//查询学生
bool add_manager(string userid, vector<string> & manager)
//增加管理员
bool delete_manager(string userid, string managerid)
//删除管理员
bool update_manager(string userid, vector<string> clm_name, vector<string> val)
//修改管理员属性
vector<string> search_manager_no(string userid, string managerid)
//查询管理员
bool send_message(string userid1, string userid2, string message)
//发送消息，userid2为0时且userid1为管理员时视为群发
bool reserve_book(string userid, string bno, unsigned int eno, string uno, int day)
//预约图书
vector<vector<string> > search_recommend(string userid, string uno)
//荐购记录查询，id为0为查询所有未处理记录
