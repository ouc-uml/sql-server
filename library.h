#ifndef SQL_H
#define SQL_H
#include "sql.h"
#endif // SQL_H
#include <sstream>

template<class out_type,class in_value>
out_type convert(const in_value & t)    //将in_value类型变量转换成out_type类型
{
    stringstream stream;
    stream << t;//向流中传值
    out_type result;//这里存储转换结果
    stream >> result;//向result中写入值
    return result;
}

void replace_str(string & str, const string & old_value, const string & new_value)
{
    for(string::size_type pos(0); pos!=string::npos; pos+=new_value.length())
        if(   (pos=str.find(old_value,pos)) != string::npos   )
            str.replace(pos,old_value.length(),new_value);
        else
            break;
}

void show_vv(vector<vector<string> > & x)
{
    for(int i = 0; i < x.size(); i++)
    {
        for(int j = 0; j < x.at(i).size(); j++)
            cout << x.at(i).at(j) << "---";
        cout << endl;
    }
}
/*void combination_message(vector<vector<string> > & data, vector<string> & result)
//将3个碎片消息合在一起
{
    string temp;
    for(int i = 1; i < data.size(); i++)
    {
        temp = data.at(i).at(0) + data.at(i).at(1) + data.at(i).at(2);
        replace_str(temp, "\\'", "'");
        result.push_back(temp);
    }
}*/

void norm_val(string & val)
{
    replace_str(val, "'", "\\'");
    val = "'" + val + "'";
}

/*bool authority(bool role, unsigned int level, string table_name, int ope)
//检查权限，role为0管理员，ope为1、2、3、4对应增、删、查、改,有权限返回1
{
    vector<vector<string> > result;
    string command, column_name;
    switch(ope)
    {
    case 1:
        column_name = "增";
        break;
    case 2:
        column_name = "删";
        break;
    case 3:
        column_name = "查";
        break;
    case 4:
        column_name = "改";
        break;
    default:
        return 0;
    }
    command = "select 角色 from 权限表 where 角色 = " + convert<string>(role) + " and 级别 = " + convert<string>(level) + " and 表名 = " + table_name + " and " + column_name + " = 1";
    server(command, result);
    if(result.size() == 1)
        return 0;
    else
        return 1;
}*/

int login(string userid, string passwd, bool role)
//登录，仅仅判断能否登录。role为0是管理员，成功返回0，密码或帐号错误返回1，帐号冻结返回2,
{
    vector<vector<string> > result;
    string command, table_name;
    if(role)
        table_name = "用户表";
    else
        table_name = "管理员表";
    command = "select 状态 from " + table_name + " where 账号 = " + userid + " and 密码 = " + passwd;
    server(command, result);
    if(result.size() == 1)
        return 1;
    else if(result.at(1).at(0) != "0")
        return 2;
    else
        return 0;
}

vector<string> get_message(string userid)//输入用户id，返回他收到管理员的消息数组
{
    vector<vector<string> > temp;
    vector<string> result;
    string command;
    command = "select 消息 from 消息表 where 账号2 = " + userid + " or 账号2 = 0";
    server(command, temp);
    for(int i = 1; i < temp.size(); i++)
        result.push_back(temp.at(i).at(0));
    return result;
}

vector<vector<string> > search_Bno(string bno, bool mode)
//根据isbn查询书，模式为0返回图书信息，模式为1返回单本信息
{
    vector<vector<string> > result;
    string command, table_name;
    if(mode)
        table_name = "单本表";
    else
        table_name = "图书信息表";
    command = "select * from " + table_name + " where ISBN = " + bno;
    server(command, result);
    return result;
}

vector<vector<string> > search_Bclm(string clm_name, string val)//根据列名，部分匹配查找
{
    vector<vector<string> > result;
    string command;
    norm_val(val);
    command = "select * from 图书信息表 where " + clm_name + " like " + val;
    server(command, result);
    return result;
}

bool recommend(string bno, string bname, string userid)//图书荐购，成功返回1,已存在返回0
{
    vector<vector<string> > result;
    result = search_Bno(bno, 0);
    if(result.size() != 1)
        return 0;
    string time_s, command;
    time_t tt = time(NULL);//这句返回的只是一个时间cuo
    tm* ltm = localtime(&tt);
    time_s = convert<string>(ltm->tm_year + 1900) + "." + convert<string>(ltm->tm_mon + 1) + "." + convert<string>(ltm->tm_mday) + "." + convert<string>(ltm->tm_hour);
    norm_val(bname);
    command = "insert into 荐购表 values (" + userid + ", " + bno + ", " + bname + ", " + time_s + ", 1)";
    server(command);
    return 1;
}

vector<vector<string> > reader_history(string userid)//读者借阅记录
{
    vector<vector<string> > result;
    string command;
    command = "select * from 借阅表 where 账号 = " + userid;
    server(command, result);
    return result;
}

vector<vector<string> > reader_current(string userid)//读者当前借阅
{
    vector<vector<string> > result;
    string command;
    command = "select * from 借阅表 where 账号 = " + userid + " and 状态 = 1";
    server(command, result);
    return result;
}

vector<string> reader_info(string userid, bool role)//读者自身信息,role为0是管理员
{
    vector<vector<string> > temp;
    vector<string> result;
    string command, table_name;
    if(role)
        table_name = "用户表";
    else
        table_name = "管理员表";
    command = "select * from " + table_name + " where 账号 = " + userid;
    server(command, temp);
    for(int i = 0; i < temp.at(1).size(); i++)
        result.push_back(temp.at(1).at(i));
    return result;
}

int borrow(string userid, string bno, unsigned int eno, string uno, int day)
//借书, 返回1 保存本，2 没有权限 3 已被借阅且未被预约，4 已被借阅且被预约,成功返回0
{
    vector<vector<string> > temp;
    string command;
    command = "select 账号 from 管理员表 where 账号 = " + userid;
    server(command, temp);
    if(temp.size() == 1)
        return 2;
    command = "select 状态 from 单本表 where ISBN = " + bno + " and 单本编号 = " + convert<string>(eno);
    server(command, temp);
    int state = convert<int>(temp.at(1).at(0));
    if(state != 2)
    {
        if(state != 5)
            return state;
        command = "select 账号 from 预约表 where ISBN = " + bno + " and 单本编号 = " + convert<string>(eno) + " and 状态 = 1";
        server(command, temp);
        if(temp.size() == 1)
            return state;
        if(temp.at(1).at(0) == uno)
        {
            command = "update 预约表 set 状态 = 0 where 账号 = " + uno + " and ISBN = " + bno + " and 单本编号 = " + convert<string>(eno);
            server(command);
        }
        else
            return state;
    }
    command = "update 单本表 set 状态 = 3 where ISBN = " + bno + " and 单本编号 = " + convert<string>(eno);
    server(command);
    string time1, time2;
    time_t tt = time(NULL);//这句返回的只是一个时间cuo
    tm* ltm = localtime(&tt);
    time1 = convert<string>(ltm->tm_year + 1900) + "." + convert<string>(ltm->tm_mon + 1) + "." + convert<string>(ltm->tm_mday) + "." + convert<string>(ltm->tm_hour);
    time2 = convert<string>(ltm->tm_year + 1900) + "." + convert<string>(ltm->tm_mon + 1) + "." + convert<string>(ltm->tm_mday + day) + "." + convert<string>(ltm->tm_hour);
    command = "insert into 借阅表 values(" + uno + ", " + bno + ", " + convert<string>(eno) + ", " + time1 + ", " + time2 + ", 1)";
    server(command);
    return 0;
}

bool return_book(string userid, string bno, unsigned int eno)//还书,成功返回1
{
    vector<vector<string> > temp;
    string command;
    command = "select 账号 from 管理员表 where 账号 = " + userid;
    server(command, temp);
    if(temp.size() == 1)
        return 0;
    command = "select 状态 from 单本表 where ISBN = " + bno + " and 单本编号 = " + convert<string>(eno);
    server(command, temp);
    int state = convert<int>(temp.at(1).at(0));
    if(state == 4)
        command = "update 单本表 set 状态 = 5 where ISBN = " + bno + " and 单本编号 = " + convert<string>(eno);
    else
        command = "update 单本表 set 状态 = 2 where ISBN = " + bno + " and 单本编号 = " + convert<string>(eno);
    server(command);
    command = "update 借阅表 set 状态 = 0 where ISBN = " + bno + " and 单本编号 = " + convert<string>(eno);
    server(command);
    return 1;
}

bool add_book(string userid, vector<string> & book)
//增加图书,成功返回1,book顺序：ISBN, 单本编号, 是否保存本, 书名, 类别, 编著人, 出版社
//1是保存表，2不是，字符串形式
{
    vector<vector<string> > temp;
    string command, values;
    command = "select 账号 from 管理员表 where 账号 = " + userid;
    server(command, temp);
    if(temp.size() == 1)
        return 0;
    command = "select ISBN from 图书信息表 where ISBN = " + book.at(0);
    server(command, temp);
    if(temp.size() == 1)
    {
        values = book.at(0);
        for(int i = 3; i < book.size(); i++)
        {
            values += ", ";
            norm_val(book.at(i));
            values += book.at(i);
        }
        string time_s;
        time_t tt = time(NULL);//这句返回的只是一个时间cuo
        tm* ltm = localtime(&tt);
        time_s = convert<string>(ltm->tm_year + 1900) + "." + convert<string>(ltm->tm_mon + 1) + "." + convert<string>(ltm->tm_mday) + "." + convert<string>(ltm->tm_hour);
        values += ", " + time_s + ", " + userid;
        command = "insert into 图书信息表 values (" + values + ")";
        server(command);
    }
    else
    {
        command = "select 状态 from 单本表 where ISBN = " + book.at(0) + " and 单本编号 = " + book.at(1);
        server(command, temp);
        if(temp.size() != 1)
            return 0;
    }
    command = "insert into 单本表 values (" + book.at(0) + ", " + book.at(1) + ", " + book.at(2) + ")";
    server(command);
    return 1;
}

bool delete_book(string userid, string bno, unsigned int eno)//删除图书,成功返回1
{
    vector<vector<string> > temp;
    string command;
    command = "select 账号 from 管理员表 where 账号 = " + userid;
    server(command, temp);
    if(temp.size() == 1)
        return 0;
    command = "select 状态 from 单本表 where ISBN = " + bno + " and 单本编号 = " + convert<string>(eno);
    server(command, temp);
    int state = convert<int>(temp.at(1).at(0));
    if(state == 3 || state == 4)
        return 0;
    command = "delete from 单本表 where ISBN = " + bno + " and 单本编号 = " + convert<string>(eno);
    server(command);
    return 1;
}

bool update_book(string userid, vector<string> clm_name, vector<string> val)//修改图书属性
{
    vector<vector<string> > temp;
    string command;
    command = "select 账号 from 管理员表 where 账号 = " + userid;
    server(command, temp);
    if(temp.size() == 1)
        return 0;
    command = "update 图书信息表 set ";
    int i;
    for(i = 1; i < clm_name.size() - 1; i++)
    {
        command += clm_name.at(i) + " = ";
        norm_val(val.at(i));
        command += val.at(i) + ", ";
    }
    command += clm_name.at(i) + " = ";
    norm_val(val.at(i));
    command += val.at(i) + " where " + clm_name.at(0) + " = " + val.at(0);
    server(command);
    return 1;
}

bool add_student(string userid, vector<string> & student)//增加学生
{
    vector<vector<string> > temp;
    string command, values;
    command = "select 账号 from 管理员表 where 账号 = " + userid;
    server(command, temp);
    if(temp.size() == 1)
        return 0;
    command = "select 账号 from 用户表 where 账号 = " + student.at(0);
    server(command, temp);
    if(temp.size() != 1)        //如果学生已经存在
        return 0;
    values = student.at(0);
    for(int i = 1; i < student.size(); i++)
    {
        values += ", ";
        norm_val(student.at(i));
        values += student.at(i);
    }
    string time_s;
    time_t tt = time(NULL);//这句返回的只是一个时间cuo
    tm* ltm = localtime(&tt);
    time_s = convert<string>(ltm->tm_year + 1900) + "." + convert<string>(ltm->tm_mon + 1) + "." + convert<string>(ltm->tm_mday) + "." + convert<string>(ltm->tm_hour);
    values += ", " + time_s;
    command = "insert into 用户表 values (" + values + ")";
    server(command);
    return 1;
}

bool delete_student(string userid, string uno)//删除学生
{
    vector<vector<string> > temp;
    string command, values;
    command = "select 账号 from 管理员表 where 账号 = " + userid;
    server(command, temp);
    if(temp.size() == 1)
        return 0;
    command = "delete from 用户表 where 账号 = " + uno;
    server(command);
    return 1;
}

bool update_student(string userid, vector<string> clm_name, vector<string> val)
//修改学生属性，成功返回1
{
    vector<vector<string> > temp;
    string command;
    command = "select 账号 from 管理员表 where 账号 = " + userid;
    server(command, temp);
    if(temp.size() == 1)
        return 0;
    command = "update 用户表 set ";
    int i;
    for(i = 1; i < clm_name.size() - 1; i++)
    {
        command += clm_name.at(i) + " = ";
        norm_val(val.at(i));
        command += val.at(i) + ", ";
    }
    command += clm_name.at(i) + " = ";
    norm_val(val.at(i));
    command += val.at(i) + " where " + clm_name.at(0) + " = " + val.at(0);
    server(command);
    return 1;
}

vector<string> search_student_no(string userid, string uno)//查询学生
{
    vector<vector<string> > temp;
    vector<string> result;
    string command;
    command = "select 账号 from 管理员表 where 账号 = " + userid;
    server(command, temp);
    if(temp.size() == 1)
        return result;
    command = "select * from 用户表 where 账号 = " + uno;
    server(command, temp);
    for(int i = 0; i < temp.at(1).size(); i++)
        result.push_back(temp.at(1).at(i));
    return result;
}

bool add_manager(string userid, vector<string> & manager)//增加管理员
{
    vector<vector<string> > temp;
    string command, values;
    command = "select 管理员级别 from 管理员表 where 账号 = " + userid;
    server(command, temp);
    if(temp.size() == 1)
        return 0;
    if(convert<int>(temp.at(1).at(0)) != 1)
        return 0;
    command = "select 账号 from 管理员表 where 账号 = " + manager.at(0);
    server(command, temp);
    if(temp.size() != 1)        //如果管理员已经存在
        return 0;
    values = manager.at(0);
    for(int i = 1; i < manager.size(); i++)
    {
        values += ", ";
        norm_val(manager.at(i));
        values += manager.at(i);
    }
    string time_s;
    time_t tt = time(NULL);//这句返回的只是一个时间cuo
    tm* ltm = localtime(&tt);
    time_s = convert<string>(ltm->tm_year + 1900) + "." + convert<string>(ltm->tm_mon + 1) + "." + convert<string>(ltm->tm_mday) + "." + convert<string>(ltm->tm_hour);
    values += ", " + time_s;
    command = "insert into 管理员表 values (" + values + ")";
    server(command);
    return 1;
}

bool delete_manager(string userid, string managerid)//删除管理员
{
    vector<vector<string> > temp;
    string command, values;
    command = "select 管理员级别 from 管理员表 where 账号 = " + userid;
    server(command, temp);
    if(temp.size() == 1)
        return 0;
    if(convert<int>(temp.at(1).at(0)) != 1)
        return 0;
    command = "delete from 管理员表 where 账号 = " + managerid;
    server(command);
    return 1;
}

bool update_manager(string userid, vector<string> clm_name, vector<string> val)//修改管理员属性
{
    vector<vector<string> > temp;
    string command, values;
    command = "select 管理员级别 from 管理员表 where 账号 = " + userid;
    server(command, temp);
    if(temp.size() == 1)
        return 0;
    if(convert<int>(temp.at(1).at(0)) != 1)
        return 0;
    command = "update 管理员表 set ";
    int i;
    for(i = 1; i < clm_name.size() - 1; i++)
    {
        command += clm_name.at(i) + " = ";
        norm_val(val.at(i));
        command += val.at(i) + ", ";
    }
    command += clm_name.at(i) + " = ";
    norm_val(val.at(i));
    command += val.at(i) + " where " + clm_name.at(0) + " = " + val.at(0);
    server(command);
    return 1;
}

vector<string> search_manager_no(string userid, string managerid)//查询管理员
{
    vector<vector<string> > temp;
    vector<string> result;
    string command, values;
    command = "select 管理员级别 from 管理员表 where 账号 = " + userid;
    server(command, temp);
    if(temp.size() == 1)
        return result;
    if(convert<int>(temp.at(1).at(0)) != 1)
        return result;
    command = "select * from 管理员表 where 账号 = " + managerid;
    server(command, temp);
    for(int i = 0; i < temp.at(1).size(); i++)
        result.push_back(temp.at(1).at(i));
    return result;
}

bool send_message(string userid1, string userid2, string message)//发送消息，userid2为0时且userid1为管理员时视为群发
{
    vector<vector<string> > temp;
    string command;
    if(userid2 == "0")
    {
        command = "select 账号 from 管理员表 where 账号 = " + userid1;
        server(command, temp);
        if(temp.size() == 1)
            return 0;
    }
    command = "insert into 消息表 values(" + userid1 + ", " + userid2 + ", " + message + ")";
    server(command);
    return 1;
}

bool reserve_book(string userid, string bno, unsigned int eno, string uno, int day)//预约图书
{
    vector<vector<string> > temp;
    string command;
    command = "select 账号 from 管理员表 where 账号 = " + userid;
    server(command, temp);
    if(temp.size() == 1)
        return 0;
    command = "select 状态 from 单本表 where ISBN = " + bno + " and 单本编号 = " + convert<string>(eno);
    server(command, temp);
    int state = convert<int>(temp.at(1).at(0));
    if(state != 3)
        return 0;
    command = "select 账号 from 借阅表 where ISBN = " + bno + " and 单本编号 = " + convert<string>(eno) + " and 状态 = 1";
    server(command, temp);
    if(temp.at(1).at(0) == uno)             //已经借此书的人不能预约
        return 0;
    command = "update 单本表 set 状态 = 4 where ISBN = " + bno + " and 单本编号 = " + convert<string>(eno);
    server(command);
    string time1, time2;
    time_t tt = time(NULL);//这句返回的只是一个时间cuo
    tm* ltm = localtime(&tt);
    time1 = convert<string>(ltm->tm_year + 1900) + "." + convert<string>(ltm->tm_mon + 1) + "." + convert<string>(ltm->tm_mday) + "." + convert<string>(ltm->tm_hour);
    time2 = convert<string>(ltm->tm_year + 1900) + "." + convert<string>(ltm->tm_mon + 1) + "." + convert<string>(ltm->tm_mday + day) + "." + convert<string>(ltm->tm_hour);
    command = "insert into 预约表 values(" + uno + ", " + bno + ", " + convert<string>(eno) + ", " + time1 + ", " + time2 + ", 1)";
    server(command);
    return 1;
}

vector<vector<string> > search_recommend(string userid, string uno)//荐购记录查询，id为0为查询所有未处理记录
{
    vector<vector<string> > temp;
    string command;
    command = "select 账号 from 管理员表 where 账号 = " + userid;
    server(command, temp);
    if(temp.size() == 1)
    {
        temp.clear();
        return temp;
    }
    if(uno == "0")
        command = "select * from 荐购表 where 状态 = 1";
    else
        command = "select * from 荐购表 where 账号 = " + uno;
    server(command, temp);
    return temp;
}

