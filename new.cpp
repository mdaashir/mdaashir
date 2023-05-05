// Header files
#include <algorithm>
#include <conio.h>
#include <ctype.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <windows.h>

using namespace std;

// Class to store student records
class Student
{
    // Structure that hold that user data
    typedef struct
    {
        string name;
        char rollno[7];
        char dob[11];
        char dep[4];
        string passwd;
        string rpasswd;
    } user;

public:
    void homepage()
    {
        system("cls");
        system("COLOR 70");

        int choice;

    home:

        fflush(stdin);

        cout << "\n\n\n\n\n\n";
        cout << "\t\t\t\t\t  ************************************\n";
        cout << "\t\t\t\t\t  *    STUDENT RECORD MAINTENANCE    *\n";
        cout << "\t\t\t\t\t  ************************************\n";
        cout << "\t\t\t\t\t  |                                  |\n";
        cout << "\t\t\t\t\t  |    1. LOGIN                      |\n";
        cout << "\t\t\t\t\t  |                                  |\n";
        cout << "\t\t\t\t\t  |    2. SIGNUP                     |\n";
        cout << "\t\t\t\t\t  |__________________________________|\n\n\n";

        cout << "\t\t\t\t\t  ENTER YOUR CHOICE : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            login();
            break;
        case 2:
            signup();
            break;
        default:
            cout << "\n";
            cout << "\t\t\t\t\t  ************************************\n";
            cout << "\t\t\t\t\t  *        INVALID CHOICE !!!        *\n";
            cout << "\t\t\t\t\t  ************************************\n";
            cout << "\n\t\t\t\t\t  ";
            system("pause");
            system("cls");
            goto home;
        }
    }

    void login()
    {
        // Command to clear the screen
        system("cls");

        int l;

        char choice;
        char rollno[7];
        string pass;
        string chk;
        char path[45];
        char a;

    home:

        // Command to clear the input buffer
        fflush(stdin);

        cout << "\n\n\n\n\n\n";
        cout << "\t\t\t\t\t  ************************************\n";
        cout << "\t\t\t\t\t  *       STUDENT RECORD LOGIN       *\n";
        cout << "\t\t\t\t\t  ************************************\n\n";
        cout << "\t\t\t\t\t  NOTE : ROLL NUMBER IS YOUR USERNAME\n\n";

        cout << "\t\t\t\t\t  USERNAME : ";
        cin >> rollno;

        // Converting the user-name entered by user to uppercase

        for (char &c : rollno)
        {
            c = toupper(c);
        }

        ifstream f;

        sprintf(path, "%s.txt", rollno);

        fflush(stdin);

        /*
            -> If statement to check if the account exists or not
            -> This is done by checking if the complier if able to open the file in the given path
        */

        f.open(path, ios::in | ios::out);

        if (!f.is_open())
        {
            cout << "\n\n";
            cout << "\t\t\t\t\t  ************************************\n";
            cout << "\t\t\t\t\t  *    ACCOUNT DOES NOT EXIST !!!    *\n";
            cout << "\t\t\t\t\t  ************************************\n\n";

            cout << "\t\t\t\t\t  DO YOU HAVE AN EXISTING ACCOUNT ? ( Y / N ) : ";
            cin >> choice;

            if (choice == 'Y' || choice == 'y')
            {
                system("cls");
                goto home;
            }
            else
            {
                cout << "\n\t\t\t\t\t  ";
                cout << "DO YOU WANT TO SIGNUP ? ( Y / N ) : ";
                cin >> choice;
                if (choice == 'Y' || choice == 'y')
                {
                    signup();
                }
                else
                {
                    homepage();
                }
            }
            f.close();
        }

        cout << "\n\n";
        cout << "\t\t\t\t\t  PASSWORD : ";

        pass = "";

        a = 0;

        // Loop to get the password from the user if the account exists
        while (a != '\r')
        {
            a = getch();
            if (a == '\b' && !pass.empty())
            {
                pass.pop_back();
                cout << "\b \b";
            }
            else if (a != '\r' && a != '\b')
            {
                pass.push_back(a);
                cout << "*";
            }
        }

        //   fgets(chk, sizeof(chk), f);
        getline(f, chk);

        // Fill other characters of password with !
        l = pass.length();

        for (int i = 0; i < 19 - l; i++)
        {
            pass += "!";
        }
        pass.resize(20);

        // Comparing the password entered by the user and the password stored in the first line of the file
        if (chk == pass)
        {
            // If the password matches then options() function is called
            // options(rollno);
        }
        else
        {
            cout << "\n\n";
            cout << "\t\t\t\t\t  ************************************\n";
            cout << "\t\t\t\t\t  *      INCORRECT PASSWORD !!!      *\n";
            cout << "\t\t\t\t\t  ************************************\n";
            cout << "\n\t\t\t\t\t  ";
            system("pause");
            system("cls");
            goto home;
        }
    }

    void signup()
    {
        system("cls");

        int i;
        int t = 0;
        int b = 0;

        char a = 0;

        user newuser;

        fflush(stdin);

        cout << "\n\n\n\n\n\n";
        cout << "\t\t\t\t  ***********************************************\n";
        cout << "\t\t\t\t  *            STUDENT RECORD SIGNUP            *\n";
        cout << "\t\t\t\t  ***********************************************\n";
        cout << "\n";

        // Getting the Name from user
        cout << "\t\t\t\t  NAME                      : ";
        cin >> newuser.name;

        // Checking whether the first character entered by user in NULL
        if (newuser.name.empty())
            t = 1;

        // Loop to check if the entered Name is Valid or Not
        i = 0;
        while (1)
        {
            b = 0;
            // Base Condition to Terminate from the Loop if a NULL or ENTER character is encountered
            if (newuser.name[i] == '\0' || newuser.name[i] == '\r')
            {
                break;
            }
            // Checking if the user has entered only alphabets in
            if (newuser.name[i] >= 'A' && newuser.name[i] <= 'Z')
            {
                b = 1;
            }
            if (newuser.name[i] >= 'a' && newuser.name[i] <= 'z')
            {
                b = 1;
            }
            // Checking whether any other character other than alphabet, entered by the user for name is a blank-space (or) dot
            if (newuser.name[i] == ' ')
            {
                b = 1;
            }
            if (newuser.name[i] == '.')
            {
                b = 1;
            }
            // If statement to set the Flag variable 1 if the entered name is invalid
            if (b == 0)
            {
                t = 1;
                break;
            }
            i++;
        }

        // if statement to print INVALID NAME if the Flag variable is 1
        if (t == 1)
        {
            cout << "\n\n";
            cout << "\t\t\t\t  ***********************************************\n";
            cout << "\t\t\t\t  *               INVALID NAME !!!              *\n";
            cout << "\t\t\t\t  ***********************************************\n";
            cout << "\n\t\t\t\t  ";
            system("pause");
            homepage();
        }

        // Getting the Roll Number from user
        cout << "\t\t\t\t  ROLL NUMBER               : ";
        cin >> newuser.rollno;

        /*
            -> Checking whether the roll number contains only 6 characters
            -> Checking whether the first two characters of roll number is a digit
            -> Checking whether the second and third character of roll number is a alphabet
            -> Checking whether the number obtained from last two characters is greater than zero and less than or equal to 40
        */

        if (newuser.rollno[6] != '\0')
            t = 1;
        if (newuser.rollno[0] < '0' || newuser.rollno[0] > '9')
            t = 1;
        if (newuser.rollno[1] < '0' || newuser.rollno[1] > '9')
            t = 1;
        if (!((newuser.rollno[2] > 65 && newuser.rollno[2] < 90) || (newuser.rollno[2] > 97 && newuser.rollno[2] < 122)))
            t = 1;
        if (!((newuser.rollno[3] > 65 && newuser.rollno[3] < 90) || (newuser.rollno[3] > 97 && newuser.rollno[3] < 122)))
            t = 1;
        if (newuser.rollno[4] == '4' && newuser.rollno[5] != '0')
            t = 1;
        if (newuser.rollno[4] < '0' || newuser.rollno[4] > '9')
            t = 1;
        if (newuser.rollno[4] == '0' && newuser.rollno[5] == '0')
            t = 1;

        // if statement to print INVALID ROLL NUMBER if the Flag variable is 1
        if (t == 1)
        {
            cout << "\n\n";
            cout << "\t\t\t\t  ***********************************************\n";
            cout << "\t\t\t\t  *           INVALID ROLL NUMBER !!!           *\n";
            cout << "\t\t\t\t  ***********************************************\n";
            cout << "\n\t\t\t\t  ";
            system("pause");
            homepage();
        }

        // Converting the Roll number to uppercase
        for (char &c : newuser.rollno)
        {
            c = toupper(c);
        }

        /*
            Checking whether the user has already created a account,
            The isExistingUser() function returns 1 if the user has already Created a account
            Or else it return 0
        */

        if (isExistingUser(newuser))
        {
            cout << "\n\n";
            cout << "\t\t\t\t  ***********************************************\n";
            cout << "\t\t\t\t  *          ACCOUNT ALREADY EXISTS !!!         *\n";
            cout << "\t\t\t\t  ***********************************************\n";
            cout << "\n\t\t\t\t  ";
            system("pause");
            homepage();
        }

        // Getting the Date of Birth from user
        cout << "\t\t\t\t  DATE OF BIRTH (DD/MM/YYYY): ";
        cin >> newuser.dob;

        /*
            -> Checking whether the date of birth contains only 10 characters
            -> Checking whether the number obtained from first two characters are greater than zero and less than or equal to 31
            -> Checking whether the number obtained from fourth and fifth characters are greater than zero and less than or equal to 12
            -> Checking whether the number obtained from last four digits are greater than or equal to 1000
            -> Checking whether the user has entered a invalid day(00) and month(00)
            -> Checking whether the last four characters entered by the user is a digit
        */

        if (newuser.dob[10] != '\0')
            t = 1;
        if (newuser.dob[0] < '0' || newuser.dob[0] > '3')
            t = 1;
        if (newuser.dob[1] < '0' || newuser.dob[1] > '9')
            t = 1;
        if (newuser.dob[0] == '3' && newuser.dob[1] > '1')
            t = 1;
        if (newuser.dob[3] < '0' || newuser.dob[3] > '1')
            t = 1;
        if (newuser.dob[4] < '0' || newuser.dob[4] > '9')
            t = 1;
        if (newuser.dob[3] == '1' && newuser.dob[4] > '2')
            t = 1;
        if (strstr(newuser.dob, "00/"))
            t = 1;
        if (newuser.dob[6] < '1' || newuser.dob[6] > '2')
            t = 1;

        i = 7;
        do
        {
            if (!(isdigit(newuser.dob[i])))
            {
                t = 1;
                break;
            }
            i++;
        } while (i != 10);

        // if statement to print INVALID Date of Birth if the Flag variable is 1
        if (t == 1)
        {
            cout << "\n\n";
            cout << "\t\t\t\t  ***********************************************\n";
            cout << "\t\t\t\t  *          INVALID DATE OF BIRTH !!!          *\n";
            cout << "\t\t\t\t  ***********************************************\n";
            cout << "\n\t\t\t\t  ";
            system("pause");
            homepage();
        }

        cout << "\t\t\t\t  DEPARTMENT (SS/TCS/DS/CS) : ";
        cin >> newuser.dep;

        // Checking whether the user has entered valid a department within the given opions
        if (strcmpi(newuser.dep, "tcs") && strcmpi(newuser.dep, "ss") && strcmpi(newuser.dep, "ds") && strcmpi(newuser.dep, "cs"))
        {
            cout << "\n\n";
            cout << "\t\t\t\t  ***********************************************\n";
            cout << "\t\t\t\t  *            INVALID DEPARTMENT !!!           *\n";
            cout << "\t\t\t\t  ***********************************************\n";
            cout << "\n\t\t\t\t  ";
            system("pause");
            homepage();
        }

        cout << "\t\t\t\t  PASSWORD                  : ";

        // Loop to get the password from the user character by character and displaying * at the same time
        while (a != '\r')
        {
            a = getch();
            if (a == '\r')
            {
                cout << "\n\n";
                cout << "\t\t\t\t  ***********************************************\n";
                cout << "\t\t\t\t  *             INVALID PASSWORD !!!            *\n";
                cout << "\t\t\t\t  ***********************************************\n";
                cout << "\n\t\t\t\t  ";
                system("pause");
                homepage();
            }
            if (a == '\b' && !newuser.passwd.empty())
            {
                newuser.passwd.pop_back();
                cout << "\b \b";
            }
            else if (a != '\r' && a != '\b')
            {
                cout << "*";
                newuser.passwd.push_back(a);
            }
        }

        cout << "\n";

        cout << "\t\t\t\t  RE-TYPE PASSWORD          : ";

        // Loop to get the password from the user character by character and displaying * at the same time
        a = 0;
        while (a != '\r')
        {
            a = getch();
            if (a == '\b' && !newuser.rpasswd.empty())
            {
                newuser.rpasswd.pop_back();
                cout << "\b \b";
            }
            else if (a != '\r' && a != '\b')
            {
                newuser.rpasswd.push_back(a);
                cout << "*";
            }
        }

        // Checking whether both the passwords entered by the user is same or not.
        if (newuser.passwd == newuser.rpasswd)
        {
            // Calling a the addnewuser() function to create a new account
            // addnewuser(newuser);
        }
        else
        {
            cout << "\n\n";
            cout << "\t\t\t\t  ***********************************************\n";
            cout << "\t\t\t\t  *            PASSWORD MISMATCH !!!            *\n";
            cout << "\t\t\t\t  ***********************************************\n";
            cout << "\n\t\t\t\t  ";
            system("pause");
            homepage();
        }
    }

    int isExistingUser(user A)
    {
        /*
            -> Function to check if the user has already created a account or not
            -> The function return 0 if user is a new user
            -> The function returns 1 if the user has already created a account
        */

        ifstream f;

        f.open("USERS.txt", ios::out);

        // while (fgets(A.name, sizeof(A.name), f))
        while (getline(f, A.name))
        {
            // Checks whether the given user A's name is written in the users file(Contains the list of users)
            if (A.name.find(A.rollno))
            {
                f.close();
                return 1;
            }
        }
        f.close();

        return 0;
    }

    Student()
    {
        int i;

        char a = 219;

        system("COLOR 02");

        cout << "\n\n\n\n\n\n";
        cout << "\t\t\t\t\t  ************************************\n";
        cout << "\t\t\t\t\t  *    STUDENT RECORD MAINTENANCE    *\n";
        cout << "\t\t\t\t\t  ************************************\n";
        cout << "\t\t\t\t\t  |                                  |\n";
        cout << "\t\t\t\t\t  |    DESIGNED BY :                 |\n";
        cout << "\t\t\t\t\t  |                                  |\n";
        cout << "\t\t\t\t\t  |    22PT01 - SREE RAM A           |\n";
        cout << "\t\t\t\t\t  |                                  |\n";
        cout << "\t\t\t\t\t  |    22PT17 - MOHAMED AASHIR S     |\n";
        cout << "\t\t\t\t\t  |__________________________________|\n\n";
        cout << "\n\t\t\t\t\t  ";
        cout << "             LOADING...\n";
        cout << "\n\t\t\t\t\t  ";

        for (i = 1; i <= 36; i++)
        {
            cout << a;
            Sleep(100);
        }

        system("cls");
        homepage();
    }
};

// Main function - Program starts here
int main()
{
    Student s;

    return 0;
}
