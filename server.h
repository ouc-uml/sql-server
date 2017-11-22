#ifndef TABLE_H
#define TABLE_H
#include "../DBsystem-master/table.h"
#endif

#include <regex>
#define column_len 32
#define val_len 64
using namespace std;

void show_vector_string(vector<string> & str)       //显示string数组
{
    vector<string>::iterator i;
    for(i = str.begin(); i != str.end(); i++)
        cout << *i << endl;
}

string utos(unsigned int n)     //int转string
{
    string sResult;
    stringstream ssTmp;
    ssTmp << n;
    ssTmp >> sResult;
    return sResult;
}

void cut_by_reg(string obj, string reg, vector<string>& res_str)        //通过正则表达式切割字符串，不分大小写
{
    res_str.clear();
    std::regex ip_reg(reg, std::regex::icase);
    sregex_token_iterator p(obj.begin(), obj.end(), ip_reg, -1);
    sregex_token_iterator end;
    while(p != end)
    {
        if(*p != "")
            res_str.push_back(*p);
        p++;
    }
}

bool operations(string co_expression, vector<string>& values1, vector<string>& values2, vector<char>& operators, vector<string>& change1, vector<string>& change2)
//。。。。。。分解一个等式组
{
    bool explain_values(vector<string>& values, vector<string>& change, char a, char b);
    string digit;
    vector<string> expressions;
    vector<string>::iterator i;
    std::regex ip_reg1("\\s*,\\s*");
    std::regex ip_reg2("([\\s\\S]*)\\s*=\\s*([\\s\\S]*)\\s*");
    std::smatch matchResult;
    values1.clear();
    values2.clear();
    operators.clear();
    cut_by_reg(co_expression, "\\s*,\\s*", expressions);
    for(i = expressions.begin(); i != expressions.end(); i++)
    {
        if(std::regex_match(*i, matchResult, ip_reg2))
        {
            digit = matchResult[1].str();
            values1.push_back(digit);
            digit = matchResult[2].str();
            values2.push_back(digit);
            operators.push_back('1');
        }
        else
            return 1;
    }
    explain_values(values1, change1, '[', ']');
    explain_values(values2, change2, '\'', '\'');
    return 0;
}

void combination_or(vector<unsigned int>& to, vector<unsigned int>& or_m)   //or合并两个数组
{
    vector<unsigned int>::iterator i, s;
    for(i = or_m.begin(); i != or_m.end(); i++)
    {
        s = find(to.begin(), to.end(), *i);
        if(s == to.end())
            to.push_back(*i);
    }
}

void combination_and(vector<unsigned int>& to, vector<unsigned int>& and_m)   //and两个数组
{
    vector<unsigned int>::iterator i, s;
    for(i = to.begin(); i != to.end(); )
    {
        s = find(and_m.begin(), and_m.end(), *i);
        if(s == and_m.end())
            i = to.erase(i);
        else
            i++;
    }
}

bool explain_value(string& value, vector<string>& change, char a, char b)                //解释有可能被字符包含的值
{
    string reg1 = "\\s*\\";
    reg1 += a;
    reg1 += "([\\s\\S])\\";
    reg1 += b;
    reg1 += "\\s*";
    std::regex ip_reg1(reg1);
    std::regex ip_reg2("\\s*([\\S]*)\\s*");
    std::smatch matchResult;
    if(std::regex_match(value, matchResult, ip_reg1))
    {
        value = matchResult[1].str();
        value = change.at((int)value[0]);
    }
    else if(std::regex_match(value, matchResult, ip_reg2))
        value = matchResult[1].str();
    else
        return 1;
    return 0;
}

bool explain_values(vector<string>& values, vector<string>& change, char a, char b)      //解释有可能被字符方包含的字符数组
{
    vector<string>::iterator i;
    for(i = values.begin(); i != values.end(); i++)
        if(explain_value(*i, change, a, b))
            return 1;
    return 0;
}

bool edit_items(table & t, vector<unsigned int> &p, string column_name, string value)     //编辑表中单元,列方向
{
    int i;
    unsigned char to_ch[column_len] = "";
    for(i = 0; i < column_name.size(); i++)
        to_ch[i] = column_name[i];
    to_ch[i] = '\0';
    switch(t.get_type(to_ch))
    {
    case 'd':
        t.edit_items(to_ch, p, atoi(value.c_str()));
        //for(i = 0; i < p.size(); i++)
        //t.get_item(p.at(i)).modify_val(to_ch, atoi(value.c_str()));
        break;
    case 's':
    {
        unsigned char ch_val[val_len] = "";
        for(i = 0; i < value.size(); i++)
            ch_val[i] = value[i];
        ch_val[i] = '\0';
        t.edit_items(to_ch, p, ch_val);
        //for(i = 0; i < p.size(); i++)
        //    t.get_item(p.at(i)).modify_val(to_ch, ch_val);
        break;
    }
    default:
        return 1;
    }
    return 0;
}

bool edit_item(table & t, unsigned int id, string column_name, string value)     //编辑表中单元
{
    vector<unsigned int> p;
    p.push_back(id);
    if(edit_items(t, p, column_name, value))
        return 1;
    return 0;
}

bool get_value(table & t, vector<unsigned int> &p, string column_name, vector<string>& values)    //得到表中数据,列方向
{
    unsigned int i, i_val;
    unsigned char to_ch[column_len] = "";
    for(i = 0; i < column_name.size(); i++)
        to_ch[i] = column_name[i];
    to_ch[i] = '\0';
    values.clear();
    switch(t.get_type(to_ch))
    {
    case 'd':
        for(i = 0; i < p.size(); i++)
        {
            t.get_item(p.at(i)).get_val(to_ch, &i_val);
            values.push_back(utos(i_val));
        }
        break;
    case 's':
        for(i = 0; i < p.size(); i++)
        {
            unsigned char to_ch1[val_len] = "";
            t.get_item(p.at(i)).get_val(to_ch, to_ch1);
            values.push_back((char *)to_ch1);
        }
        break;
    default:
        return 1;
    }
    return 0;
}

void add_column(table & t, string column_name, char type)
{
    int i;
    unsigned char to_ch[column_len] = "";
    for(i = 0; i < column_name.size(); i++)
        to_ch[i] = column_name[i];
    to_ch[i] = '\0';
    t.add_column(to_ch, type);
}

void drop_column(table & t, string column_name)
{
    int i;
    unsigned char to_ch[column_len] = "";
    for(i = 0; i < column_name.size(); i++)
        to_ch[i] = column_name[i];
    to_ch[i] = '\0';
    t.delete_column(to_ch);
}

void select_items(table & t, string column_name, string value, vector<unsigned int> &p, char mode)
//模式1是全匹配，模式2是部分匹配
{
    string old_val;
    vector<unsigned int>::iterator j;
    int k;
    unsigned char to_ch[column_len] = "";
    p.clear();
    for(k = 0; k < column_name.size(); k++)
        to_ch[k] = column_name[k];
    to_ch[k] = '\0';
    switch(t.get_type(to_ch))
    {
    case 'd':
        if(mode == '1')
            p = t.find_from_all(to_ch, atoi(value.c_str()));
        break;
    case 's':
    {
        int i;
        unsigned char ch_val[val_len] = "";
        for(i = 0; i < value.size(); i++)
            ch_val[i] = value[i];
        ch_val[i] = '\0';
        if(mode == '1')
            p = t.find_from_all(to_ch, ch_val);
        else if(mode == '2')
            p = t.find_by_index(to_ch, ch_val);
        break;
    }
    }
}

bool calculate_one(table & t, string expression, vector<unsigned int> &p, vector<string>& change1, vector<string>& change2)
//计算一个表达式
{
    char mode;
    string column_name, value;
    std::regex ip_reg1("([\\s\\S]*)\\s*=\\s*([\\s\\S]*)\\s*");
    std::regex ip_reg2("([\\s\\S]*)\\s+like\\s+([\\s\\S]*)\\s*", std::regex::icase);
    /*std::regex ip_reg3("([\\s\\S]*)\\s*<\\s*([\\s\\S]*)\\s*");
    std::regex ip_reg4("([\\s\\S]*)\\s*>\\s*([\\s\\S]*)\\s*");
    std::regex ip_reg5("([\\s\\S]*)\\s*<=\\s*([\\s\\S]*)\\s*");
    std::regex ip_reg6("([\\s\\S]*)\\s*>=\\s*([\\s\\S]*)\\s*");*/
    std::smatch matchResult;
    if(std::regex_match(expression, matchResult, ip_reg1))
        mode = '1';
    else if(std::regex_match(expression, matchResult, ip_reg2))
        mode = '2';
    /*else if(std::regex_match(expression, matchResult, ip_reg3))
        mode = '3';
    else if(std::regex_match(expression, matchResult, ip_reg4))
        mode = '4';
    else if(std::regex_match(expression, matchResult, ip_reg5))
        mode = '5';
    else if(std::regex_match(expression, matchResult, ip_reg6))
        mode = '6';*/
    else
        return 1;
    column_name = matchResult[1].str();
    value = matchResult[2].str();
    explain_value(column_name, change1, '[', ']');
    explain_value(value, change2, '\'', '\'');
    select_items(t, column_name, value, p, mode);
    return 0;
}

bool calculate_and(table & t, string co_expression, vector<unsigned int> &p, vector<string>& change1, vector<string>& change2)
//计算and连接的表达式
{
    vector<string> and_m;
    vector<string>::iterator i;
    vector<unsigned int> temp;
    cut_by_reg(co_expression, "\\s+and\\s+", and_m);
    p.clear();
    for(i = and_m.begin(); i != and_m.end(); i++)
    {
        if(calculate_one(t, *i, temp, change1, change2))
            return 1;
        if(i == and_m.begin())
            p = temp;
        else
            combination_and(p, temp);
    }
    return 0;
}

bool select_all_item(table & t, string co_expression, vector<unsigned int> &p, vector<string>& change1, vector<string>& change2)
//通过co_expression表达式筛选出条目数组
{
    vector<string> values1, values2, or_m;
    vector<char> operators;
    vector<unsigned int> temp;
    vector<string>::iterator i;
    p.clear();
    cut_by_reg(co_expression, "\\s+or\\s+", or_m);
    for(i = or_m.begin(); i != or_m.end(); i++)
    {
        if(calculate_and(t, *i, temp, change1, change2))
            return 1;
        combination_or(p, temp);
    }
    return 0;
}

void get_all_column_name(table & t, vector<string>& columns)    //得到表中所有列的名字
{
    columns.clear();
    unsigned char keys_i[t.c][v_len];
    for(int i = 0; i < t.c; i++)
    {
        t._column.get_by_key((unsigned)(i + 1),keys_i[i]);
        columns.push_back((char *)keys_i[i]);
    }
}

void get_all_item(table & t, vector<unsigned int> &p)           //得到表中所有行的id
{
    int num = t.items.get_size();
    unsigned int keys[num];
    t.items.get_all_key(keys);
    p.clear();
    for(int i = 0; i < num; i++)
        p.push_back(keys[i]);
}

void set_index(table & t, string column_name)
{
    int i;
    unsigned char to_ch[column_len] = "";
    for(i = 0; i < column_name.size(); i++)
        to_ch[i] = column_name[i];
    to_ch[i] = '\0';
    t.set_index(to_ch);
}

bool simplify(string& command, vector<string>& change, char a, char b)
//将命令中方括号内容全部替代，并存放在change数组,默认第一个字符不是特殊字符
{
    char i = 0;
    int p1 = 0, p2 = 0;
    change.clear();
    do
    {
        do
        {
            p1 = command.find_first_of(a, p1 + 1);
            if(p1 == -1)
                return 0;
        }
        while(command[p1 - 1] == '\\');
        p2 = p1;
        do
        {
            p2 = command.find_first_of(b, p2 + 1);
            if(p2 == -1)
                return 1;
        }
        while(command[p2 - 1] == '\\');
        change.push_back(command.substr(p1 + 1, p2 - p1 - 1));
        command.replace(p1 + 1, p2 - p1 - 1, 1, i);
        p1 += 2;
        i++;
    }
    while(1);
}

bool explain_table(string table, string& table_name, string& co_column, vector<string>& change1)
//解释table name（列名字，。。。）格式
{
    std::regex ip_reg("\\s*([\\s\\S]*)\\s*\\(\\s*([\\s\\S]*)\\)\\s*");
    std::smatch matchResult;
    if(std::regex_match(table, matchResult, ip_reg))
    {
        table_name = matchResult[1];
        co_column = matchResult[2];
    }
    else
    {
        table_name = table;
        co_column = "";
    }
    if(explain_value(table_name, change1, '[', ']'))
        return 1;
    return 0;
}

int judge_type(string co_name, string& column_name, vector<string>& change1)
//由命令判断列的类型string类返回1,int类返回2,不满足返回0
{
    std::regex ip_reg1("\\s*([\\s\\S]*)\\s+string\\s*", std::regex::icase);
    std::regex ip_reg2("\\s*([\\s\\S]*)\\s+int\\s*", std::regex::icase);
    std::smatch matchResult;
    if(std::regex_match(co_name, matchResult, ip_reg1))
    {
        column_name = matchResult[1].str();
        if(explain_value(column_name, change1, '[', ']'))
            return 0;
        return 1;
    }
    else if (std::regex_match(co_name, matchResult, ip_reg2))
    {
        column_name = matchResult[1].str();
        if(explain_value(column_name, change1, '[', ']'))
            return 0;
        return 2;
    }
    else
        return 0;
}

void cut_where(string& command, string& co_expression)
//分离带where的命令
{
    std::regex ip_reg("([\\s\\S]*)\\s*where\\s+([\\s\\S]*)", std::regex::icase);
    std::smatch matchResult;
    co_expression = "";
    if(std::regex_match(command, matchResult, ip_reg))
    {
        command = matchResult[1].str();
        co_expression = matchResult[2].str();
    }
}

bool creat_m(string table_m, vector<string>& change1)
{
    string table_name, column_name, co_column;
    vector<string> columns;
    vector<string>::iterator i;
    if(explain_table(table_m, table_name, co_column, change1))
        return 1;
    cut_by_reg(co_column, "\\s*,\\s*", columns);
    table t(table_name.c_str());
    for(i = columns.begin(); i != columns.end(); i++)
        switch(judge_type(*i, column_name, change1))
        {
        case 0:
            return 1;
        case 1:
            add_column(t, column_name, 's');
            break;
        case 2:
            add_column(t, column_name, 'd');
            break;
        }
    t.show_all();
    return 0;
}

bool alter_m(string command, vector<string>& change1)
{
    string table_name, column_name;
    std::smatch matchResult;
    std::regex ip_reg1("([\\s\\S]*)\\s+add\\s+([\\s\\S]*)\\s*", std::regex::icase);
    std::regex ip_reg2("([\\s\\S]*)\\s+drop\\s+column\\s+([\\s\\S]*)", std::regex::icase);
    //std::regex ip_reg3("([\\s\\S]*)\\s+alter\\s+column\\s+([\\s\\S]*)\\s*", std::regex::icase);
    if(std::regex_match(command, matchResult, ip_reg1))
    {
        table_name = matchResult[1].str();
        if(explain_value(table_name, change1, '[', ']'))
            return 1;
        command = matchResult[2].str();
        table t(table_name.c_str());
        switch(judge_type(command, column_name, change1))
        {
        case 0:
            return 1;
        case 1:
            add_column(t, column_name, 's');
            break;
        case 2:
            add_column(t, column_name, 'd');
            break;
        }
        t.show_all();
    }
    else if(std::regex_match(command, matchResult, ip_reg2))
    {
        table_name = matchResult[1].str();
        if(explain_value(table_name, change1, '[', ']'))
            return 1;
        column_name = matchResult[2].str();
        if(explain_value(column_name, change1, '[', ']'))
            return 1;
        table t(table_name.c_str());
        drop_column(t, column_name);
        t.show_all();
    }
    /*else if(std::regex_match(command, matchResult, ip_reg3))
    {
        PART1
    }*/
    else
        return 1;
    return 0;
}

bool select_m(string co_column, string command, vector<string>& change1, vector<string>& change2, vector<vector<string> > &result)
{
    string table_name, co_name, co_expression, s_val;
    vector<string> columns, temp;      //存放列名称
    vector<unsigned int> p;     //p存放了要选择的列
    vector<string>::iterator i;
    vector<unsigned int>::iterator ii;
    unsigned int i_val, j;
    cut_where(command, co_expression);
    table_name = command;
    if(explain_value(table_name, change1, '[', ']'))
        return 1;
    table t(table_name.c_str());
    if(co_expression == "")
        get_all_item(t, p);
    else if(select_all_item(t, co_expression, p, change1, change2))
        return 1;
    if(co_column == "*")
        get_all_column_name(t, columns);
    else
    {
        cut_by_reg(co_column, "\\s*,\\s*", columns);
        if(explain_values(columns, change1, '[', ']'))
            return 1;
    }
    vector<string> res[p.size()];
    for(i = columns.begin(); i != columns.end(); i++)
    {
        get_value(t, p, *i, temp);
        for(j = 0; j < p.size(); j++)
            res[j].push_back(temp.at(j));
    }
    for(j = 0; j < p.size(); j++)
        result.push_back(res[j]);
    return 0;
}

bool update_m(string table_name, string command, vector<string>& change1, vector<string>& change2)
{
    int flag = 0;
    string co_expression;
    vector<string> values1, values2;
    vector<char> operators;
    vector<unsigned int> p;     //p存放了要选择的列
    if(explain_value(table_name, change1, '[', ']'))
        return 1;
    table t(table_name.c_str());
    cut_where(command, co_expression);
    if(operations(command, values1, values2, operators, change1, change2))
        return 1;
    if(co_expression == "")
        get_all_item(t, p);
    else if(select_all_item(t, co_expression, p, change1, change2))
        return 1;
    for(int i = 0; i < values1.size(); ++i)
        if(edit_items(t, p, values1.at(i), values2.at(i)))
            flag = 1;
    t.show_all();
    return flag;
}

bool delete_m(string command, vector<string>& change1, vector<string>& change2)
{
    string table_name, co_expression;
    vector<unsigned int> p;     //p存放了要选择的列
    vector<unsigned int>::iterator i;
    cut_where(command, co_expression);
    table_name = command;
    if(explain_value(table_name, change1, '[', ']'))
        return 1;
    table t(table_name.c_str());
    if(co_expression == "")
        get_all_item(t, p);
    else if(select_all_item(t, co_expression, p, change1, change2))
        return 1;
    for(i = p.begin(); i != p.end(); i++)
        t.delete_item(*i);
    t.show_all();
    //cout << "delete" << endl;
    return 0;
}

bool insert_m(string table_m, string co_value, vector<string>& change1, vector<string>& change2)
{
    int flag = 0;
    string table_name, co_column;
    vector<string> columns, values;      //存放列名称和分开的值
    if(explain_table(table_m, table_name, co_column, change1))
        return 1;
    cut_by_reg(co_column, "\\s*,\\s*", columns);
    cut_by_reg(co_value, "\\s*,\\s*", values);
    table t(table_name.c_str());
    if(columns.empty())
        get_all_column_name(t, columns);
    else if(explain_values(columns, change1, '[', ']'))
        return 1;
    if(explain_values(values, change2, '\'', '\''))
        return 1;
    int id = t.add_item();
    for(int i = 0; i < columns.size(); i++)
        if(edit_item(t, id, columns.at(i), values.at(i)))
            flag = 1;
    t.show_all();
    return flag;
}

bool index_m(string table_m, vector<string>& change1)
{
    string table_name, co_column;
    vector<string> columns;
    vector<string>::iterator i;
    if(explain_table(table_m, table_name, co_column, change1))
        return 1;
    cut_by_reg(co_column, "\\s*,\\s*", columns);
    if(explain_values(columns, change1, '[', ']'))
        return 1;
    table t(table_name.c_str());
    for(i = columns.begin(); i != columns.end(); i++)
        set_index(t, *i);
    return 0;
}

int server(string command, vector<vector<string> > &result)
{
    vector<string> change1;     //存放方括号内容
    vector<string> change2;     //存放单引号内容
    if(simplify(command, change1, '[', ']') || simplify(command, change2, '\'', '\''))
        return 1;
    std::regex ip_reg1("\\s*create\\s+table\\s+([\\s\\S]*)", std::regex::icase);
    std::regex ip_reg2("\\s*alter\\s+table\\s+([\\s\\S]*)", std::regex::icase);
    std::regex ip_reg3("\\s*drop\\s+table\\s+([\\s\\S]*)", std::regex::icase);
    std::regex ip_reg4("\\s*select\\s+([\\s\\S]*)\\s+from\\s+([\\s\\S]*)", std::regex::icase);
    std::regex ip_reg5("\\s*update\\s+([\\s\\S]*)\\s+set\\s+([\\s\\S]*)", std::regex::icase);
    std::regex ip_reg6("\\s*delete\\s+from\\s+([\\s\\S]*)", std::regex::icase);
    std::regex ip_reg7("\\s*insert\\s+into\\s+([\\s\\S]*)\\s+values\\s*\\(\\s*([\\s\\S]*)\\s*\\)", std::regex::icase);
    std::regex ip_reg8("\\s*create\\s+index([\\s\\S]*)on\\s+([\\s\\S]*)", std::regex::icase);
    std::smatch matchResult;
    result.clear();
    if(std::regex_match(command, matchResult, ip_reg1))
    {
        string table_m = matchResult[1].str();
        if(creat_m(table_m, change1))
            return 1;
    }
    else if(std::regex_match(command, matchResult, ip_reg2))
    {
        command = matchResult[1].str();
        if(alter_m(command, change1))
            return 1;
    }
    else if(std::regex_match(command, matchResult, ip_reg3))
    {
        string table_name = matchResult[1].str();
        if(explain_value(table_name, change1, '[', ']'))
            return 1;
        table t(table_name.c_str());
        t.delete_talbe();
    }
    else if(std::regex_match(command, matchResult, ip_reg4))
    {
        string co_column = matchResult[1].str();
        command = matchResult[2].str();
        if(select_m(co_column, command, change1, change2, result))
            return 1;
    }
    else if(std::regex_match(command, matchResult, ip_reg5))
    {
        string table_name = matchResult[1].str();
        command = matchResult[2].str();
        if(update_m(table_name, command, change1, change2))
            return 1;
    }
    else if(std::regex_match(command, matchResult, ip_reg6))
    {
        command = matchResult[1].str();
        if(delete_m(command, change1, change2))
            return 1;
    }
    else if(std::regex_match(command, matchResult, ip_reg7))
    {
        string table_m, co_value;
        table_m = matchResult[1].str();
        co_value = matchResult[2].str();
        if(insert_m(table_m, co_value, change1, change2))
            return 1;
    }
    else if(std::regex_match(command, matchResult, ip_reg8))
    {
        cout << "match" << endl;
        string table_m;
        table_m = matchResult[2].str();
        if(index_m(table_m, change1))
            return 1;
    }
        return 1;
    return 0;
}

int server(string command)
{
    vector<vector<string> > result;
    return server(command, result);
}
