#ifndef SQL_H
#define SQL_H
#include "sql.h"
#endif // SQL_H
#include <fstream>
int main()
{
    vector<string> command;
    string temp;
    fstream file("table_set_up.txt");
    do
    {
        getline(file, temp);
        if(file.eof())
            break;
        command.push_back(temp);
    }
    while(1);
    file.close();
    load_configuration();
    for(int i = 0; i < command.size(); i++)
        server(command.at(i));
    return 0;
}
