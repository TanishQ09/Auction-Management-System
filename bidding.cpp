#include <iostream>
#include <string.h>
#include <conio.h>
#include <stdio.h>
#include <process.h>
#include <cstdio>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <vector>
#include <time.h>
using namespace std;
fstream fp;

class product
{
    int pno;
    char name[50];
    float price, qty, tax, dis;
    char diss[100];

public:
    void create_product()
    {
        cout << "\nPlease Enter The Product ID : ";
        cin >> pno;
        cout << "\nPlease Enter The Name of The Product : ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "\nPlease Enter The Price of Product : ";
        cin >> price;
        cout << "\nPlease Enter The Description of Product : ";
        cin.ignore();
        cin.getline(diss, 100);
    }
    void show_product()
    {
        cout << "Product ID : " << pno;
        cout << "\nProduct Name :";
        puts(name);
        cout << "\nProduct Price :" << price;
        cout << "\nProduct Description :" << diss;
    }
    int retpno()
    {
        return pno;
    }
    float retprice()
    {
        return price;
    }
    char *retname()
    {
        return name;
    }
    char *retdess()
    {
        return diss;
    }
};
product pr;
void admin_menu();
void write_product()
{
    fp.open("shop.dat", ios::out | ios::app);
    pr.create_product();
    fp.write((char *)&pr, sizeof(product));
    fp.close();
    cout << "\nThe Product Has Been Created ";
    getch();
    admin_menu();
}
void display_all()
{
    cout << "\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    fp.open("shop.dat", ios::in);
    while (fp.read((char *)&pr, sizeof(product)))
    {
        pr.show_product();
        cout << "\n\n==========================================================================================\n";
        getch();
    }
    fp.close();
    admin_menu();
    getch();
}
void display_sp(int n)
{
    int flag = 0;
    fp.open("shop.dat", ios::in);
    while (fp.read((char *)&pr, sizeof(product)))
    {
        if (pr.retpno() == n)
        {
            pr.show_product();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0)
    {
        cout << "\n\nRecord Not Exist";
        getch();
    }
    admin_menu();
}
void modify_product()
{
    int no, found = 0;
    cout << "\n\n\tTo Modify ";
    cout << "\n\n\tPlease Enter The Product Id. of The Product ";
    cin >> no;
    fp.open("shop.dat", ios::in | ios::out);
    while (fp.read((char *)&pr, sizeof(product)) && found == 0)
    {
        if (pr.retpno() == no)
        {
            pr.show_product();
            cout << "\nPlease Enter The New Details Of The Product " << endl;
            pr.create_product();
            int pos = -1 * sizeof(pr);
            fp.seekp(pos, ios::cur);
            fp.write((char *)&pr, sizeof(product));
            cout << "\n\n\t Record Updated ";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
        cout << "\n\n Record Not Found ";
    getch();
    admin_menu();
}
void delete_product()
{
    int no;
    cout << "\n\n\n\t Delete Record ";
    cout << "\n\nPlease Enter The Product ID. of The Product You Want To Delete ";
    cin >> no;
    fp.open("shop.dat", ios::in | ios::out);
    fstream fp2;
    fp2.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char *)&pr, sizeof(product)))
    {
        if (pr.retpno() != no)
        {
            fp2.write((char *)&pr, sizeof(product));
        }
    }
    fp2.close();
    fp.close();
    remove("shop.dat");
    rename("Temp.dat", "shop.dat");
    cout << "\n\n\tRecord Deleted..";
    getch();
    admin_menu();
}
void menu()
{
    fp.open("shop.dat", ios::in);
    if (!fp)
    {
        cout << "Error !!! File Could Not Be Open\n\n\n Go To Admin Menu to Create File";
        cout << "\n\n\n Program is Closing...";
        getch();
        exit(0);
    }
    cout << "\n\n\t\t\tProduct Menu\n\n";
    cout << "=====================================================================\n";
    cout << "Pr.ID.\t\tPrice\t\tName\t\tDescription\n";
    cout << "=====================================================================\n";
    while (fp.read((char *)&pr, sizeof(product)))
    {
        cout << pr.retpno() << "\t\t" << pr.retprice() << "\t\t" << pr.retname() << "\t\t" << pr.retdess() << endl;
    }
    fp.close();
}
void place_order()
{
    int order_arr[50], quan[50], c = 0;
    float amt, damt, total = 0;
    char ch = 'Y';
    char ch1;
    menu();
    cout << "\n=====================================================================";
    cout << "\n\t\t\tPlace Your Order ";
    cout << "\n=====================================================================";
    do
    {
        cout << "\n\nEnter The Product Id. Of The Product :";
        cin >> order_arr[c];
    label:
        int t = order_arr[c];
        cout << "\nAmount for Bid :";
        cin >> quan[c];
        fp.open("shop.dat", ios::in);
        fp.read((char *)&pr, sizeof(product));
        while (!fp.eof())
        {
            if (pr.retpno() == t)
            {
                if (pr.retprice() <= quan[c])
                {
                    c++;
                    break;
                }
                if (pr.retprice() > quan[c])
                {
                    cout << "not accepted re-enter price ";
                    goto label;
                }
            }
            fp.read((char *)&pr, sizeof(product));
        }
        fp.close();
        cout << "\nDo You Want To Bid on Another Product ? (y/n)";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    cout << "\n\nCongratulations For Your Successfull Bid ";
    getch();
    cout << "\nDo you want to place order ? (y/n)" << endl;
    cin >> ch1;
    if (ch1 == 'y' || ch1 == 'Y')
    {
        string biller_name, biller_address, biller_mobno;
        cout << "Enter Your name : ";
        getline(cin >> ws, biller_name);
        cout << "Enter Your address : ";
        getline(cin >> ws, biller_address);
        cout << "Enter Your Mobile No. : ";
        getline(cin >> ws, biller_mobno);
        cout << "\n\n*********************** INVOICE ************************\n";
        cout << "Name : " << biller_name << endl;
        cout << "Mobile No. : " << biller_mobno << endl;
        cout << "Address : " << biller_address << endl;
        cout << "\nPr.ID\tPr Name\tBid Amount\tMin Bid\tDescription\n";
        for (int x = 0; x <= c; x++)
        {
            fp.open("shop.dat", ios::in);
            fp.read((char *)&pr, sizeof(product));
            while (!fp.eof())
            {
                if (pr.retpno() == order_arr[x])
                {
                    if (pr.retprice() <= quan[x])
                    {
                        total += quan[x];
                        cout << "\n"
                             << " " << order_arr[x] << "\t"
                             << " " << pr.retname() << "\t"
                             << " " << quan[x] << "\t\t" << pr.retprice() << "\t\t" << pr.retdess();
                    }
                }
                fp.read((char *)&pr, sizeof(product));
            }
            fp.close();
        }
        cout << "\n\n\t\t\t\t\tTotal = " << total;
        getch();
    }
    else
    {
        cout << "Thanks for Bidding " << endl;
    }
}
bool login_customer()
{
    string username, password, un, pw;
    cout << "Enter UserName : ";
    cin >> username;
    cout << "Enter Password : ";
    cin >> password;
    ifstream read("data" + username + ".txt");
    getline(read, un);
    getline(read, pw);
    if (un == username && pw == password)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool login_admin()
{
    string username, password, un, pw;
    cout << "Enter UserName : ";
    cin >> username;
    cout << "Enter Password : ";
    cin >> password;
    ifstream read("Admin" + username + ".txt");
    getline(read, un);
    getline(read, pw);
    if (un == username && pw == password)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void regis_customer()
{
    string username, password, name, email, address;
    long long int mob_no;
    cout << "Select a username : ";
    cin >> username;
    cout << "Select a Password : ";
    cin >> password;
    cout << "Enter Your Name : ";
    getline(cin >> ws, name);
    cout << "Enter Your E-mail : ";
    getline(cin >> ws, email);
    cout << "Enter Your Mobile No. : ";
    cin >> mob_no;
    cout << "Enter Your address : ";
    getline(cin >> ws, address);
    ofstream file;
    file.close();
    file.open("data" + username + ".txt");
    file << username << endl
         << password << endl
         << name << endl
         << email << endl
         << mob_no << endl
         << address;
    file.close();
    cout << "Registered Succesfully...";
}
void regis_admin()
{
    string username, password, name, email, address;
    long long int mob_no;
    cout << "Select a username : ";
    cin >> username;
    cout << "Select a Password : ";
    cin >> password;
    cout << "Enter Your Name : ";
    getline(cin >> ws, name);
    cout << "Enter Your E-mail : ";
    getline(cin >> ws, email);
    cout << "Enter Your Mobile No. : ";
    cin >> mob_no;
    cout << "Enter Your address : ";
    getline(cin >> ws, address);
    ofstream file;
    file.close();
    file.open("Admin" + username + ".txt");
    file << username << endl
         << password << endl
         << name << endl
         << email << endl
         << mob_no << endl
         << address;
    file.close();
    cout << "Registered Succesfully...";
}
void admin_menu()
{
    int ch2;
    cout << "\n\n\n\tAdmin Menu";
    cout << "\n\n\n\t1. Create Product ";
    cout << "\n\n\n\t2. Display All Product ";
    cout << "\n\n\n\t3. Query ";
    cout << "\n\n\n\t4. Modify Product ";
    cout << "\n\n\n\t5. Delete Product ";
    cout << "\n\n\n\t6. View Product Menu ";
    cout << "\n\n\n\t7. Logout ";
    cout << "\n\n\n\t Please Enter Your Choice (1-7)";
    cin >> ch2;
    switch (ch2)
    {
    case 1:
        write_product();
        break;
    case 2:
        display_all();
        break;
    case 3:
        int num;
        cout << "Please Enter The Product No. ";
        cin >> num;
        display_sp(num);
        break;
    case 4:
        modify_product();
        break;
    case 5:
        delete_product();
        break;
    case 6:
        menu();
        getch();
    case 7:
        break;
    default:
        cout << "\a";
        admin_menu();
        break;
    }
}
int main()
{
    int ch;
    while (ch != 3)
    {
        cout<<endl<<" _______________________________________"<<endl;
        cout<<"|              Welcome To               |"<<endl;
        cout<<"|                Auction                |"<<endl;
        cout<<"|_______________________________________|"<<endl;
        cout << "\n\n\n\t1. Customer";
        cout << "\n\n\n\t2. Administrator";
        cout << "\n\n\n\t3. Exit";
        cout << "\n\n\n\tPlease Enter Your Choice (1-3) ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            int ch_user;
            cout << endl
                 << " __________________________________________" << endl;
            cout << "| *************** Customer *************** |" << endl;
            cout << "|__________________________________________|" << endl;
            cout << "1. Register \n2. Login" << endl;
            cout << "Enter Your Choice : ";
            cin >> ch_user;
            if (ch_user == 1)
            {
                regis_customer();
            }
            else if (ch_user == 2)
            {
                bool status = login_customer();
                if (!status)
                {
                    cout << "Invalid username or Password !! " << endl;
                    system("PAUSE");
                    return 0;
                }
                else
                {
                    cout << "Succesfully logged in " << endl;
                    cout << "Press any key to continue...";
                    getch();
                    cout << endl
                         << " __________________________________________" << endl;
                    cout << "| ********* Welcome Customer !!! ********* |" << endl;
                    cout << "|__________________________________________|" << endl;
                    cout << "\n1. View Product Menu " << endl;
                    cout << "2. Place Order " << endl;
                    cout << "3. Logout " << endl;
                    int ch;
                    cout << "Enter Your Choice " << endl;
                    cin >> ch;
                    switch (ch)
                    {
                    case 1:
                        menu();
                        char ch1;
                        cout << "Do you want to bid on any product ? (y/n)" << endl;
                        cin >> ch1;
                        if (ch1 == 'y' || ch1 == 'Y')
                        {
                            place_order();
                        }
                        else
                            break;
                    case 2:
                        place_order();
                    case 3:
                        exit(0);
                        break;
                    default:
                        break;
                    }
                }
            }
            break;
        case 2:
            int ch_admin;
            cout << endl
                 << " __________________________________________" << endl;
            cout << "| ***************** Admin **************** |" << endl;
            cout << "|__________________________________________|" << endl;
            cout << "1. Register \n2. Login" << endl;
            cout << "Enter Your Choice : ";
            cin >> ch_admin;
            if (ch_admin == 1)
            {
                regis_admin();
            }
            else if (ch_admin == 2)
            {
                bool status = login_admin();
                if (!status)
                {
                    cout << "Invalid username or Password !! " << endl;
                    system("PAUSE");
                    return 0;
                }
                else
                {
                    cout << "Succesfully logged in " << endl;
                    cout << "Press any key to continue...";
                    getch();
                    cout << endl
                         << " __________________________________________" << endl;
                    cout << "| *********** Welcome Admin !!! ********** |" << endl;
                    cout << "|__________________________________________|" << endl;
                    admin_menu();
                }
            }
            break;
        case 3:
            exit(0);
        default:
            cout << "\a";
            break;
        }
    }
}