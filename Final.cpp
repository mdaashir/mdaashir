//Header files
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <algorithm>

using namespace std;

//Class to store student records
class Student
{
    public:
        string name;
        string address;
        int rollno;

        void getInput();
};

//Function to get new record input
void Student :: getInput()
{
    system("cls");

    fflush(stdin);

    cout << "\n\n\n\n\n\n";
    cout << "\t\t  ********************************************************************************\n";
    cout << "\t\t  *                                  NEW RECORD                                  *\n";
    cout << "\t\t  ********************************************************************************\n";
    cout << "\n";

    cout << "\t\t  NAME        : ";
    getline(cin,name);
    transform(name.begin(), name.end(), name.begin(), ::toupper);
    cout << "\n";

    cout << "\t\t  ROLL NUMBER : ";
    cin >> rollno;
    cout << "\n";

    fflush(stdin);

    cout << "\t\t  ADDRESS     : ";
    getline(cin,address);
    transform(address.begin(), address.end(), address.begin(), ::toupper);
    cout << "\n";
}

//Class to store data related to a node
class Node
{
	public:
        Student *key;
        Node *left;
        Node *right;

        int height;
};

//Function to create a new node
Node* newNode(Student *stud)
{
	Node *node = new Node();
	node->key = stud;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;

	return(node);
}

//Function to return height of a node
int height(Node *node)
{
    if(node == NULL)
        return 0;

    return node->height;
}

//Function to compare height of left and right subtree of a particular node
int maxHeight(int a, int b)
{
	return (a > b) ? a : b;
}

//Function to calculate and return balance factor of a particular node
int getBalance(Node *node)
{
	if(node == NULL)
		return 0;

    return (height(node->left) - height(node->right));
}

//Function to perform Right Rotation (RR)
Node* rightRotate(Node *y)
{
	Node *x = y->left;
	Node *z = x->right;

	x->right = y;
	y->left = z;

	y->height = maxHeight(height(y->left),height(y->right)) + 1;
	x->height = maxHeight(height(x->left),height(x->right)) + 1;

	return x;
}

//Function to perform Left Rotation (LL)
Node* leftRotate(Node *y)
{
	Node *x = y->right;
	Node *z = x->left;

	x->left = y;
	y->right = z;

	y->height = maxHeight(height(y->left),height(y->right)) + 1;
	x->height = maxHeight(height(x->left),height(x->right)) + 1;

	return x;
}

//Function to insert node in the tree
Node* insertElement(Node *node, Student *stud)
{
	if(node == NULL)
		return(newNode(stud));

	if(stud->rollno < (node->key)->rollno)
		node->left = insertElement(node->left,stud);
	else if(stud->rollno > (node->key)->rollno)
		node->right = insertElement(node->right,stud);
	else
		return node;

	node->height = 1 + maxHeight(height(node->left),height(node->right));

	int balance = getBalance(node);

	if(balance > 1 && (stud->rollno < ((node->left)->key)->rollno))
        return rightRotate(node);

	if(balance < -1 && (stud->rollno > ((node->right)->key)->rollno))
		return leftRotate(node);

	if(balance > 1 && (stud->rollno > ((node->left)->key)->rollno))
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	if(balance < -1 && (stud->rollno < ((node->right)->key)->rollno))
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	return node;
}

//Function to find the least element from the subtree of a particular node
Node* minValueNode(Node *node)
{
    Node *current = node;

    while(current->left != NULL)
        current = current->left;

    return current;
}

//Function to delete a particular node containing the element rno
Node* deleteElement(Node *root, int rno)
{
    if(root == NULL)
        return root;

    if(rno < (root->key)->rollno)
        root->left = deleteElement(root->left,rno);
    else if(rno > (root->key)->rollno)
        root->right = deleteElement(root->right,rno);
    else
    {
        if((root->left == NULL) || (root->right == NULL))
        {
            Node *temp = root->left ? root->left : root->right;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;

            free(temp);
        }
        else
        {
            Node *temp = minValueNode(root->right);
            root->key = temp->key;

            root->right = deleteElement(root->right,(temp->key)->rollno);
        }
    }

    if (root == NULL)
        return root;

    root->height = maxHeight(height(root->left),height(root->right)) + 1;

    int balance = getBalance(root);

    if (balance > 1 && (getBalance(root->left) >= 0))
        return rightRotate(root);

    if (balance > 1 && (getBalance(root->left) < 0))
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && (getBalance(root->right) <= 0))
        return leftRotate(root);

    if (balance < -1 && (getBalance(root->right) > 0))
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

//Function to search for element rno in the tree
bool searchElement(Node *node, int rno)
{
    if(node != NULL)
    {
        if((node->key)->rollno == rno)
        {
            cout << "\n";
            cout << "\t\t  NAME        : " << (node->key)->name << "\n";
            cout << "\t\t  ROLL NUMBER : " << (node->key)->rollno << "\n";
            cout << "\t\t  ADDRESS     : " << (node->key)->address <<  "\n";
            return true;
        }
        else if((node->left == NULL) && (node->right == NULL))
            return false;
        else if((node->key)->rollno > rno)
            searchElement(node->left,rno);
        else if((node->key)->rollno < rno)
            searchElement(node->right,rno);
    }

    return false;
}

static int t = 0;

//Function to perform inorder traversal (ascending order)
void inOrder(Node *root)
{
	if(root != NULL)
	{
		t++;
		if(t == 1)
        {
            system("cls");
            cout << "\n\n\n\n\n\n";
            cout << "  ********************************************************************************************************************\n";
            cout << "  |    ROLL NO    |            NAME            |                               ADDRESS                               |\n";
            cout << "  ********************************************************************************************************************\n";
        }

		inOrder(root->left);

        cout << "  |               |                            |                                                                     |\n";
        cout << " ";
        cout << " | " << right << setw(13) << (root->key)->rollno;
        cout << " | " << right << setw(26) << (root->key)->name;
        cout << " | " << right << setw(67) << (root->key)->address;
        cout << " |\n";

		inOrder(root->right);
	}
}

//Function to display the operations
Node* homepage(Node *root)
{
    system("cls");
    system("COLOR 70");

    int choice;
    int roll;

    Student *s;

home:

    fflush(stdin);

    cout << "\n\n\n\n\n\n";
    cout << "\t\t\t\t\t  ************************************\n";
    cout << "\t\t\t\t\t  *    STUDENT RECORD MAINTENANCE    *\n";
    cout << "\t\t\t\t\t  ************************************\n";
    cout << "\t\t\t\t\t  |                                  |\n";
    cout << "\t\t\t\t\t  |    1. INSERT NEW RECORD          |\n";
    cout << "\t\t\t\t\t  |                                  |\n";
    cout << "\t\t\t\t\t  |    2. DELETE A RECORD            |\n";
    cout << "\t\t\t\t\t  |                                  |\n";
    cout << "\t\t\t\t\t  |    3. SEARCH A RECORD            |\n";
    cout << "\t\t\t\t\t  |                                  |\n";
    cout << "\t\t\t\t\t  |    4. DISPLAY ALL RECORDS        |\n";
    cout << "\t\t\t\t\t  |__________________________________|\n\n\n";

    cout << "\t\t\t\t\t  ENTER YOUR CHOICE : ";
    cin >> choice;

    switch(choice)
    {
        case 1:
            s = new Student();
            s->getInput();
            if(searchElement(root,s->rollno))
            {
                cout << "\n\n";
                cout << "\t\t  ********************************************************************************\n";
                cout << "\t\t  *                         ROLL NUMBER ALREADY EXIST !!!                        *\n";
                cout << "\t\t  ********************************************************************************\n";
                delete(s);
            }
            else
            {
                root = insertElement(root,s);
                cout << "\n\n";
                cout << "\t\t  ********************************************************************************\n";
                cout << "\t\t  *                         RECORD INSERTED SUCCESSFULLY                         *\n";
                cout << "\t\t  ********************************************************************************\n";
            }
            break;
        case 2:
            system("cls");
            cout << "\n\n\n\n\n\n";
            cout << "\t\t  ********************************************************************************\n";
            cout << "\t\t  *                                 DELETE RECORD                                *\n";
            cout << "\t\t  ********************************************************************************\n";
            cout << "\n\t\t  ENTER ROLL NUMBER OF STUDENT TO BE DELETED : ";
            cin >> roll;
            if(searchElement(root,roll))
            {
                root = deleteElement(root,roll);
                cout << "\n\n";
                cout << "\t\t  ********************************************************************************\n";
                cout << "\t\t  *                          RECORD DELETED SUCCESSFULLY                         *\n";
                cout << "\t\t  ********************************************************************************\n";
            }
            else
            {
                cout << "\n\n";
                cout << "\t\t  ********************************************************************************\n";
                cout << "\t\t  *                        ROLL NUMBER DOES NOT EXIST !!!                        *\n";
                cout << "\t\t  ********************************************************************************\n";
            }
            break;
        case 3:
            system("cls");
            cout << "\n\n\n\n\n\n";
            cout << "\t\t  ********************************************************************************\n";
            cout << "\t\t  *                                 SEARCH RECORD                                *\n";
            cout << "\t\t  ********************************************************************************\n";
            cout << "\n\t\t  ENTER ROLL NUMBER OF STUDENT TO BE SEARCHED : ";
            cin >> roll;
            if(searchElement(root,roll))
            {
                cout << "\n\n";
                cout << "\t\t  ********************************************************************************\n";
                cout << "\t\t  *                               RECORD AVAILABLE                               *\n";
                cout << "\t\t  ********************************************************************************\n";
            }
            else
            {
                cout << "\n\n";
                cout << "\t\t  ********************************************************************************\n";
                cout << "\t\t  *                             RECORD NOT AVAILABLE                             *\n";
                cout << "\t\t  ********************************************************************************\n";
            }
            break;
        case 4:
            t = 0;
            inOrder(root);
            if(t == 0)
            {
                cout << "\n\n";
                cout << "\t\t\t\t\t  ************************************\n";
                cout << "\t\t\t\t\t  *       NO RECORDS AVAILABLE       *\n";
                cout << "\t\t\t\t\t  ************************************\n";
            }
            else
            {
                cout << "  |               |                            |                                                                     |\n";
                cout << "  ********************************************************************************************************************\n";
                cout << "\n\n";
            }
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

    cout << "\n\t\t\t\t\t  ";
    system("pause");
    root = homepage(root);

    return root;
}

//Main function - Program starts here
int main()
{
    int i;

    Node *root = NULL;

    char a = 219;

    system("COLOR 02");

    cout << "\n\n\n\n\n\n";
    cout << "\t\t\t\t\t  ************************************\n";
    cout << "\t\t\t\t\t  *    STUDENT RECORD MAINTENANCE    *\n";
    cout << "\t\t\t\t\t  ************************************\n";
    cout << "\t\t\t\t\t  |                                  |\n";
    cout << "\t\t\t\t\t  |    DESIGNED BY :                 |\n";
    cout << "\t\t\t\t\t  |                                  |\n";
    cout << "\t\t\t\t\t  |    22PT17 - MOHAMED AASHIR S     |\n";
    cout << "\t\t\t\t\t  |                                  |\n";
    cout << "\t\t\t\t\t  |    22PT01 - SREE RAM A           |\n";
    cout << "\t\t\t\t\t  |__________________________________|\n\n";
    cout << "\n\t\t\t\t\t  ";
    cout << "             LOADING...\n";
    cout << "\n\t\t\t\t\t  ";

    for (i = 1; i <= 36; i++)
    {
        cout << a;
        Sleep(120);
    }

    system("cls");
    root = homepage(root);

    return 0;
}
