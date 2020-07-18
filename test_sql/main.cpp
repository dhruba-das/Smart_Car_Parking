#include <iostream>
#include<windows.h>
#include<mysql.h>
using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    MYSQL* conn;
    conn=mysql_init(0);
    conn=mysql_real_connect(conn,"192.168.1.2","dhruba","dhruba","test_code",0,NULL,0);
    if(conn)
    {

        cout<<"connected to SQL Database";

    }
    else cout<<"Not connected";
    return 0;
}
