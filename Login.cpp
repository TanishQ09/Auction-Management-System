#include<iostream>
#include<string>
#include<fstream>
using namespace std;

bool is_logged_in()
{
    string username,password, un ,pw;
    cout<<"Enter UserName : ";
    cin>>username;
    cout<<"Enter Password : ";
    cin>>password;
    ifstream read("data"+username+".txt");
    getline(read, un);
    getline(read , pw);
    if(un == username && pw == password)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

int main()
{
    int choice;
    cout<<"1. Register \n2. Login ";
    cout<<endl<<"Enter your Choice : ";cin>>choice;
    if(choice == 1)
    {
        string username, password,name,email,address;
        long long int mob_no;
        cout<<"Select a username : ";cin>>username;
        cout<<"Select a Password : ";cin>>password;
        cout<<"Enter Your Name : ";getline(cin>>ws,name);
        cout<<"Enter Your E-mail : ";getline(cin>>ws,email);
        cout<<"Enter Your Mobile No. : ";cin>>mob_no;
        cout<<"Enter Your address : ";getline(cin>>ws,address); 
        ofstream file;
        file.close();
        file.open("data"+username+".txt");
        file<<username<<endl<<password<<endl<<name<<endl<<email<<endl<<mob_no<<endl<<address;
        file.close();
        main();
    }
    else if(choice == 2 )
    {
        bool status = is_logged_in();
        if(!status)
        {
            cout<<"False Login "<<endl;
            system("PAUSE");
            return 0;
        }
        else
        {
            cout<<"Succesfully logged in "<<endl;
            system("PAUSE");
            return 1;
        }
    }
}