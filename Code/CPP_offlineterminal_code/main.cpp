#include <iostream>
#include<windows.h>
#include<mysql.h>
#include <sstream>
#include<stdio.h>
//CREATED by Dhruba_Das
using namespace std;

bool dbconn(); //data base connection
void addrec(); //to update that a car has parked in the database
void editrec(); // function to exit a car from the lot
void view_police();
void view(); // To see the slots used up in the parking slots
void user_reg(); //To register a new user, who has not used the web app before
void home_page(); //Home Page (Login/ sign-up page)
int page1(); //  Page to do operations such as park, view, exit, etc.


int main()
{
    home_page();
    return(0);
}




void home_page()
{
    string dummy;
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "192.168.1.2", "Hello_world", "Hello_world", "Car_Parked", 0, NULL, 0); //connecting to the local host mySQL server
        int answ;
     if(conn){
            int mobile,input;
    cout<<"1. login or 2. sign up?"<<endl;
    cin>>answ;
    switch(answ){
        case 1:
            {// enter mobile number and name to verify and then proceed to page 1
                cout << "Enter Mobile_Number : ";
                cin >> mobile;
/* Future improvement area: To verify if the logged in user exists in the user_base database
      // cout<<input;
        int qstate=mysql_query(conn, "SELECT name FROM Mobile_Number" );
            while(row=mysql_fetch_row(res)){
                    cout<<"hello1";
                stringstream ss;
                ss<<"SELECT EXISTS(SELECT * FROM user_base WHERE Mobile_Number="<<mobile<<")";
                cout<<"hello2";
            }*/
            cout<<"User Verified"<<endl;
            system("pause");
    system("cls");
              page1();
            break;
            }


        case 2:
            user_reg();
            break;
    system("pause");
    system("cls");
    }
    }else{
            cout << "Insert Error" << mysql_error(conn) << endl;
            cout << "Press B to go back";
            cin >> dummy;
            }

}

int page1(){ //user has signed in
    int runforever = 1;
    int ans;

    while(runforever == 1){

        cout << endl << endl << "---------------" << endl << endl << "1. Add Car to slot" << endl << "2. Exit Car" << endl << "3. Find Car (police only)" << endl << "4. View occupied slots" << endl << "5. End" <<endl<<endl << endl << endl << "---------------" << endl;

        cout << endl << "Your Answer : ";

        cin >> ans;

        switch(ans){
        case 1:
            addrec();
            break;
        case 2:
            editrec();
            break;
        case 7899: //1234 is the secret code that the Cop in the tow truck has to enter to see the full database of cars parked
            view_police();
            break;
        case 4:
            view();
            break;
        case 5:
            runforever = 0;
            break;
        case 6:
            user_reg();;
            break;
        }
    }

    return 0;
}


void addrec(){
    string dummy;
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "192.168.1.2", "Hello_world", "Hello_world", "Car_Parked", 0, NULL, 0);
    if(conn){//connection to server is successful
        int qstate = 0; int Slot_Number;
        string name, Number_plate;

        cout << "Enter name : ";
        cin >> name;

        cout << "Enter Reg Details : ";
        cin >> Number_plate;
         cout << "Enter Slot_Number : ";
        cin >> Slot_Number;

        //cout << "Enter quantity : ";
        //cin >> quantity;

        stringstream ss;
        ss << "INSERT INTO inventory(name, Number_Plate, Slot_Number) VALUES('" << name << "','" << Number_plate << "'," << Slot_Number<<")"; //database name is inventory in the server

        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0){
            cout << "Record Inserted..." << endl;
            cout << "Press B to go back";
            cin >> dummy;
        }else{
            cout << "Insert Error" << mysql_error(conn) << endl;
            cout << "Press B to go back";
            cin >> dummy;
        }
    }else{
        cout << "Connection Error" << endl;
        cout << "Press B to go back";
        cin >> dummy;
    }

    system("pause");
    system("cls");

}

void editrec(){// to exit  the car
    string dummy;
    MYSQL* conn;
    conn = mysql_init(0);
    //conn = mysql_real_connect(conn, "192.168.1.2", "Hello_world", "Hello_world", "Car_Parked", 0, NULL, 0);
    conn = mysql_real_connect(conn, "192.168.1.2", "Hello_world", "Hello_world", "Car_Parked", 0, NULL, 0); //Car_Parked=
    if(conn){
        int qstate = 0;
        string name; string Number_plate;
        int quantity;
        cout << "Enter RegNo : ";
        cin >> Number_plate;
        stringstream ss;
       // ss << "UPDATE inventory SET quantity = quantity + " << quantity << " WHERE name = '" << name << "'"; //inventory is the column name
        ss<<"DELETE FROM `inventory` WHERE Number_Plate= '"<<Number_plate<<"'";
        string query = ss.str();

        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0){
            cout << "Car Exited!" << endl;
            cout << "Press B to go back";
            cin >> dummy;
        }else{
            cout << " Error" << mysql_error(conn) << endl;
            cout << "Press B to go back";
            cin >> dummy;
        }
    }else{
        cout << "Connection Error" << endl;
        cout << "Press B to go back";
        cin >> dummy;
    }

    system("pause");
    system("cls");

}

void view(){//to view slots that are occupied. Only displays appropriate data to the public from the database
    string dummy;
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "192.168.1.2", "Hello_world", "Hello_world", "Car_Parked", 0, NULL, 0); //Car_Parked= meds
    if(conn){
        int qstate = mysql_query(conn, "SELECT Slot_Number FROM inventory");

        if(!qstate){
            res = mysql_store_result(conn);
            cout<<"Slot number(s) occupied \t"<<endl;
            while(row = mysql_fetch_row(res)){

                cout << row[0] <<"\t | \t" <<"\t | \t"   << endl;
             }
        }
    }

    cout << "Press B to go back";
    cin >> dummy;

    system("pause");
    system("cls");
}


void view_police(){//to view entire database
    string dummy;
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "192.168.1.2", "Hello_world", "Hello_world", "Car_Parked", 0, NULL, 0);
    if(conn){
        int qstate = mysql_query(conn, "SELECT name,Number_plate,Slot_Number FROM inventory");

        if(!qstate){
            res = mysql_store_result(conn);
            cout<<"Name of driver"<<"\t"<<"Car Number"<<"\t"<<"Slot number"<<endl;
            while(row = mysql_fetch_row(res)){

                cout << row[0] <<"\t | \t" << row[1] <<"\t | \t"   << row[2] <<"\t | \t"<<endl;
             }
        }
    }

    cout << "Press B to go back";
    cin >> dummy;

    system("pause");
    system("cls");
}


void user_reg(){
    string dummy;
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "192.168.1.2", "Hello_world", "Hello_world", "Car_Parked", 0, NULL, 0); //Car_Parked= meds
//name,Number_plate, RC_no, Mobile No
    if(conn){
        int qstate = 0; int Slot_Number,rc, mobile_number;
        string name, Number_plate;

        cout << "Enter name : ";
        cin >> name;

        cout << "Enter Number Plate Details : ";
        cin >> Number_plate;
         cout << "Enter Car chasis number : ";
        cin >> rc;
        cout<<"Enter mobile number: ";
        cin>>mobile_number;




        stringstream ss;
        ss << "INSERT INTO user_base(name, Number_Plate, RC_No,Mobile_Number) VALUES('" << name << "','" << Number_plate << "'," << rc<<","<<mobile_number<<")";

        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0){
            cout << "Record Inserted..." << endl;
            cout << "Press B to go back";
            cin >> dummy;
        }else{
            cout << "Insert Error" << mysql_error(conn) << endl;
            cout << "Press B to go back";
            cin >> dummy;
        }
    }else{
        cout << "Connection Error" << endl;
        cout << "Press B to go back";
        cin >> dummy;
    }

    system("pause");
    system("cls");
          page1();
}
