
#include "sql.h"
int main()
{
    int temp;
    string input;
    vector<vector<string> > result;
    vector<vector<string> >::iterator i;
    vector<string>::iterator j;
    load_configuration();
    do
    {
        getline(cin, input);
        if(input.empty())
            break;
        //server(input, result);
        //server(" CREATE TABLE [测试 TABLE 1](第一列 int, [ 第二列 TABLE ] string)");
        //server("ALTER TABLE [测试 TABLE 1] ADD 第三列 int");
        //server("ALTER TABLE [测试 TABLE 1] ADD [ 第4列 ALTER ] string");
        //server("INSERT INTO [测试 TABLE 1] VALUES (1234, ' \\[BOOK\\] ', 321, ' VALUE = \\'myl\\' ')");
        //server("INSERT INTO [测试 TABLE 1] (第一列, 第三列) VALUES (110, 233)");
        //server("INSERT INTO [测试 TABLE 1] ([ 第二列 TABLE ], [ 第4列 ALTER ]) VALUES (' \\[BOOK\\] ', ' VALUE = \\'myl\\' ')");
        //server("INSERT INTO [测试 TABLE 1] (第一列, [ 第4列 ALTER ]) VALUES (110, ' VALUE = \\'myl\\' ')");
        //server("UPDATE [测试 TABLE 1] SET 第一列 = 233, 第三列 = 321 WHERE [ 第二列 TABLE ] = ' \\[BOOK\\] ' OR [ 第4列 ALTER ] = ' VALUE = \\'myl\\' '");
        //server("UPDATE [测试 TABLE 1] SET 第一列 = 233, [ 第二列 TABLE ] = 'hello' WHERE 第三列 = 321 AND [ 第二列 TABLE ] = ' \\[BOOK\\] '");
        /*server("UPDATE [测试 TABLE 1] SET 第一列 = 384, [ 第二列 TABLE ] = 'cool'");
        server("SELECT 第一列, 第三列 FROM [测试 TABLE 1] WHERE 第一列 = 384", result);
        server("SELECT 第一列, [ 第4列 ALTER ] FROM [测试 TABLE 1] WHERE [ 第二列 TABLE ] = 'cool'", result);
        server("SELECT * FROM [测试 TABLE 1] WHERE [ 第二列 TABLE ] = 'cool'", result);
        server("SELECT * FROM [测试 TABLE 1]", result);
        server("DELETE FROM [测试 TABLE 1] WHERE 第三列 = 233");
        server("DELETE FROM [测试 TABLE 1] WHERE [ 第二列 TABLE ] = 'hello'");
        server("DELETE FROM [测试 TABLE 1]");*/
        //server("DROP TABLE [测试 TABLE 1]");
        /*server("create table student(姓名 string, 学号 string, 成绩 int)");
        server("insert into student values('maoyilong', '100', 95)");
        server("insert into student values('aoao', '101', 90)");
        server("insert into student values('aiai', '102', 95)");
        server("insert into student values('jinkela', '103', 90)");
        server("insert into student values('jiji', '104', 100)");
        server("insert into student values('aowu', '105', 90)");
        server("insert into student values('ggao', '106', 90)");
        server("insert into student values('silly', '107', 90)");
        server("insert into student values('wuhaha', '108', 90)");
        server("insert into student values('bilibili', '109', 80)");
        server("insert into student values('shit', '110', 100)");*/
        //server("create index on student(姓名, 学号)");
        //server("update student set 姓名 = 'doubi' where 学号 = '100' or 学号 = '101'");
        //server("select * from student where 姓名 like 'ao' or 姓名 = 'silly'", result);
        server("select * from student where 姓名 = ao", result);
        //server("select * from student where 姓名 = 'aaa' and 成绩 = 100", result);
        //server("update student set 姓名 = 'hhh', 成绩 = 90 where 学号 = '110'");
        //server("update student set 成绩 = 0");
        //server("select 姓名, 成绩 from student where 学号 = 100 and 姓名 = 'aaa' or 姓名 = 'bbb' or 姓名 = 'ccc'", result);
        //server("ALTER TABLE student DROP COLUMN 成绩");
        //server("ALTER TABLE student add 成绩 int");
        //server("DELETE FROM student WHERE 姓名 = 'ccc'");
        //server("DELETE FROM student WHERE 姓名 = 'ccc' or 姓名 = 'aaa'");
        //server("DELETE FROM student");*/
        //server("create table student1(姓名 string, 学号 string, 成绩 int)");
        //server("select * from student1 where 姓名 = 'aaa' and 成绩 = 100", result);
        for(i = result.begin(); i != result.end(); i++)
        {
            for(j = (*i).begin(); j != (*i).end(); j++)
                cout << *j << "---";
            cout << endl;
        }
    }
    while(1);
    //bool init_data();
    //init_data();
    return 0;
}
