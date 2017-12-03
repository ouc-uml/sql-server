#include "library.h"

int main()
{
    load_configuration();
    string input;
    string rootid = "uml";
    string managerid = "m-233";
    string studentid = "15020032014";
    vector<string> manager;
    vector<string> clm_name;
    vector<string> val;
    vector<string> result;
    vector<string> student;
    vector<vector<string> > result2;
    //............................................................
    manager.push_back(managerid);   //账号
    manager.push_back("123456");    //密码
    manager.push_back("2");         //管理员级别
    manager.push_back("0");         //状态
    if(add_manager(rootid, manager))
        cout << "增加管理员成功" << endl;   //增加一个管理员
    else
        cout << "增加管理员失败" << endl;
    manager.clear();
    manager.push_back("m-9527");   //账号
    manager.push_back("abcdef");    //密码
    manager.push_back("2");         //管理员级别
    manager.push_back("0");         //状态
    if(add_manager(rootid, manager))
        cout << "增加管理员成功" << endl;   //增加一个管理员
    else
        cout << "增加管理员失败" << endl;
    clm_name.push_back("账号");
    val.push_back(managerid);
    clm_name.push_back("密码");
    val.push_back("654321");
    if(update_manager(rootid, clm_name, val))//更新管理员信息
        cout << "更新管理员信息成功" << endl;
    else
        cout << "更新管理员信息失败" << endl;
    result = search_manager_no(rootid, managerid);       //根据帐号查管理员
    cout << "显示管理员信息:" << endl;
    for(int i = 0; i < result.size(); i++)
        cout << result.at(i) << "---";
    cout << endl;
    if(login(managerid, "654321", 0))
        cout << "登录失败" << endl;
    else
        cout << "登录成功" << endl;
    if(delete_manager(rootid, "m-9527"))
        cout << "删除管理员成功" << endl;          //删除管理员
    else
        cout << "删除管理员失败" << endl;
    cout << "回车继续";
    getline(cin, input);
    //............................................................
    student.push_back(studentid);   //账号
    student.push_back("110110");   //密码
    student.push_back("毛逸龙");   //昵称
    student.push_back("1");         //用户级别
    student.push_back("0");          //状态
    if(add_student(managerid, student))
        cout << "增加学生成功" << endl;
    else
        cout << "增加学生失败" << endl;
    student.clear();
    student.push_back("15020032015");   //账号
    student.push_back("zxczxc");   //密码
    student.push_back("mike");   //昵称
    student.push_back("1");         //用户级别
    student.push_back("0");          //状态
    if(add_student(managerid, student))
        cout << "增加学生成功" << endl;
    else
        cout << "增加学生失败" << endl;
    student.clear();
    student.push_back("15020032016");   //账号
    student.push_back("zxczxc");   //密码
    student.push_back("bob");   //昵称
    student.push_back("1");         //用户级别
    student.push_back("0");          //状态
    if(add_student(managerid, student))
        cout << "增加学生成功" << endl;
    else
        cout << "增加学生失败" << endl;
    clm_name.clear();
    val.clear();
    clm_name.push_back("账号");
    val.push_back(studentid);
    clm_name.push_back("密码");
    val.push_back("987654");
    if(update_student(managerid, clm_name, val))
        cout << "修改学生信息成功" << endl;
    else
        cout << "修改学生信息失败" << endl;
    result = search_student_no(managerid, studentid);
    cout << "显示学生信息:" << endl;
    for(int i = 0; i < result.size(); i++)
        cout << result.at(i) << "---";
    cout << endl;
    if(login(studentid, "987654", 1))
        cout << "登录失败" << endl;
    else
        cout << "登录成功" << endl;
    if(delete_student(managerid, "15020032016"))
        cout << "删除管理员成功" << endl;
    else
        cout << "删除管理员失败" << endl;
    cout << "回车继续";
    getline(cin, input);
    //............................................................
    vector<string> book;
    book.push_back("123-456");      //ISBN
    book.push_back("1");            //单本编号
    book.push_back("1");            //是否保存本
    book.push_back("数据结构");     //书名
    book.push_back("计算机");      //类别
    book.push_back("李某某");      //编著人
    book.push_back("清华大学出版社");//出版社
    if(add_book(managerid, book))
        cout << "增书成功" << endl;
    else
        cout << "增书失败" << endl;
    book.clear();
    book.push_back("123-456");      //ISBN
    book.push_back("2");            //单本编号
    book.push_back("2");            //是否保存本
    book.push_back("数据结构");     //书名
    book.push_back("计算机");      //类别
    book.push_back("李某某");      //编著人
    book.push_back("清华大学出版社");//出版社
    if(add_book(managerid, book))
        cout << "增书成功" << endl;
    else
        cout << "增书失败" << endl;
    book.clear();
    book.push_back("123-456");      //ISBN
    book.push_back("3");            //单本编号
    book.push_back("2");            //是否保存本
    book.push_back("数据结构");     //书名
    book.push_back("计算机");      //类别
    book.push_back("李某某");      //编著人
    book.push_back("清华大学出版社");//出版社
    if(add_book(managerid, book))
        cout << "增书成功" << endl;
    else
        cout << "增书失败" << endl;
    book.clear();
    book.push_back("123-789");      //ISBN
    book.push_back("1");            //单本编号
    book.push_back("2");            //是否保存本
    book.push_back("死亡笔记");     //书名
    book.push_back("小说");      //类别
    book.push_back("张某某");      //编著人
    book.push_back("北京大学出版社");//出版社
    if(add_book(managerid, book))
        cout << "增书成功" << endl;
    else
        cout << "增书失败" << endl;
    clm_name.clear();
    val.clear();
    clm_name.push_back("ISBN");
    val.push_back("123-456");
    clm_name.push_back("出版社");
    val.push_back("海大出版社");
    clm_name.push_back("编著人");
    val.push_back("bob");
    if(update_book(managerid, clm_name, val))
        cout << "修改图书信息成功" << endl;
    else
        cout << "修改图书信息失败" << endl;
    result2 = search_Bno("123-456", 0);                   //返回图书信息
    cout << "显示图书信息:" << endl;
    for(int i = 0; i < result2.size(); i++)
    {
        for(int j = 0; j < result2.at(i).size(); j++)
            cout << result2.at(i).at(j) << "---";
        cout << endl;
    }
    result2 = search_Bno("123-456", 1);                   //返回单本信息
    cout << "显示图书信息:" << endl;
    for(int i = 0; i < result2.size(); i++)
    {
        for(int j = 0; j < result2.at(i).size(); j++)
            cout << result2.at(i).at(j) << "---";
        cout << endl;
    }
    result2 = search_Bclm("书名", "死亡");
    cout << "显示图书信息:" << endl;
    for(int i = 0; i < result2.size(); i++)
    {
        for(int j = 0; j < result2.at(i).size(); j++)
            cout << result2.at(i).at(j) << "---";
        cout << endl;
    }
    if(delete_book(managerid, "123-456", 3))
        cout << "删除图书成功" << endl;
    else
        cout << "删除图书失败" << endl;
    cout << "回车继续";
    getline(cin, input);
    //............................................................
    if(send_message(managerid, "0", "hello"))
        cout << "群发成功" << endl;
    else
        cout << "群发失败" << endl;
    if(send_message(managerid, studentid, "Silly!"))
        cout << "发送成功" << endl;
    else
        cout << "发送失败" << endl;
    result = get_message(studentid);
    cout << "显示消息:" << endl;
    for(int i = 0; i < result.size(); i++)
        cout << result.at(i) << "---";
    cout << endl;
    cout << "回车继续";
    getline(cin, input);
    //............................................................
    if(borrow(managerid, "123-456", 2, studentid, 7))
        cout << "借书失败" << endl;
    else
        cout << "借书成功" << endl;
    result2 = reader_history(studentid);
    cout << "学生借书历史:" << endl;
    for(int i = 0; i < result2.size(); i++)
    {
        for(int j = 0; j < result2.at(i).size(); j++)
            cout << result2.at(i).at(j) << "---";
        cout << endl;
    }
    result2 = reader_current(studentid);
    cout << "学生目前借书:" << endl;
    for(int i = 0; i < result2.size(); i++)
    {
        for(int j = 0; j < result2.at(i).size(); j++)
            cout << result2.at(i).at(j) << "---";
        cout << endl;
    }
    if(reserve_book(managerid, "123-456", 2, "15020032015", 7))
        cout << "预约成功" << endl;
    else
        cout << "预约失败" << endl;
    if(return_book(managerid, "123-456", 2))
        cout << "还书成功" << endl;
    else
        cout << "还书失败" << endl;
    if(borrow(managerid, "123-456", 2, studentid, 7))
        cout << "借书失败" << endl;
    else
        cout << "借书成功" << endl;
    if(borrow(managerid, "123-456", 2, "15020032015", 7))//只有预约的能能借书
        cout << "借书失败" << endl;
    else
        cout << "借书成功" << endl;
    if(return_book(managerid, "123-456", 2))
        cout << "还书成功" << endl;
    else
        cout << "还书失败" << endl;
    cout << "回车继续";
    getline(cin, input);
    //............................................................
    if(recommend("456-789", "一本书的名字", studentid))
        cout << "推荐成功" << endl;
    else
        cout << "推荐失败" << endl;
    result2 = search_recommend(managerid, studentid);
    cout << "某学生推荐记录:" << endl;
    for(int i = 0; i < result2.size(); i++)
    {
        for(int j = 0; j < result2.at(i).size(); j++)
            cout << result2.at(i).at(j) << "---";
        cout << endl;
    }
    result2 = search_recommend(managerid, "0");             //所有未处理推荐记录
    cout << "未处理推荐记录:" << endl;
    for(int i = 0; i < result2.size(); i++)
    {
        for(int j = 0; j < result2.at(i).size(); j++)
            cout << result2.at(i).at(j) << "---";
        cout << endl;
    }
    return 0;
}
