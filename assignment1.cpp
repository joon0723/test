/* #include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Loaded_List_Node // a node of the loaded linked list
{
public:
    int num;
    string a;
    Loaded_List_Node* next;
    Loaded_List_Node() // default constructor
    {
        num = 0;
        a.empty();
        next = NULL;
    }
    Loaded_List_Node(int Num, string A) // parameterised Constructor
    {
        this->num = Num;
        this->a = A;
        this->next = NULL;
    }
};
class Loaded_List
{
private:
    Loaded_List_Node* head; // private member
public:
    Loaded_List() // default constructor
    {
        head = NULL;
    }
    void insertNode1()
    {
        Loaded_List_Node* newNode;
    }
    void insertNode2(int Num, string str)
    {
        Loaded_List_Node* newNode = new Loaded_List_Node(Num, str); // create new node
        if (head == NULL) // assign to head
        {
            head = newNode;
            return;
        }
        Loaded_List_Node* tmp = head;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;  // update temp
        }
        tmp->next = newNode; // insert at the last node
    }
    void deleteNode(int node) // function to delete the node at given position
    {
        Loaded_List_Node* tmp1 = head, * tmp2 = NULL;
        ofstream fout;
        fout.open("text.txt");
        int listlen = 0;
        if (head == NULL)
        {
            fout << "List is empty." << endl;
            return;
        }
        while (tmp1 != NULL) // find a length of the loaded linked list
        {
            tmp1 = tmp1->next;
            listlen++;
        }
        if (listlen < node) // check the position that it is less than a length of the loaded linked list
        {
            fout << "Index out of range" << endl;
            return;
        }
        tmp1 = head;
        if (node == 1) // deleting the head node
        {
            head = head->next;
            delete tmp1;
            return;
        }
        while (node-- > 1) // tranverse the list to find the node to be deleted
        {
            tmp2 = tmp1;
            tmp1 = tmp1->next;
        }
        tmp2->next = tmp1->next; // change the next pointer of the previous node
        delete tmp1;
    }
    void printList() // function to print the node of the loaded linked list 
    {
        Loaded_List_Node* tmp = head;
        ofstream fout;
        fout.open("text.txt");
        if (head == NULL)
        {
            fout << "List is empty." << endl;
            return;
        }
        fout << "========LOAD=========" << endl;
        while (tmp != NULL) // tranverse the list
        {
            fout << tmp->a << "/" << tmp->num << endl;
            tmp = tmp->next;
        }
        fout << "=====================" << endl;
    }
};
int main()
{
    Loaded_List list;
    string line;
    ifstream file("command.txt"); // Open command.txt file
    if (file.is_open()) // check the file has 'command txt'
    {
        while (getline(file, line))
        {
            if (line.find("LOAD") == 0)
            {
                string str, str1;
                int num = 0, i = 0;
                fstream fs;
                ofstream fout;
                fout.open("text.txt");
                fs.open("filesnumbers.csv", ios::in);
                if (fs.fail()) // check the file has csv file
                {
                    fout << "========ERROR========" << endl;
                    fout << "100" << endl;
                    fout << "=====================" << endl;
                    return 0;
                }
                char a, b, c;
                a = fs.get();
                b = fs.get();
                c = fs.get();
                if (a != (char)0xEF || b != (char)0xBB || c != (char)0xBF) // solving UTF-8 Bom
                {
                    fs.seekg(0);
                }
                while (!fs.eof())
                {
                    getline(fs, str);
                    if (!str.empty())
                    {
                        if (i < 100) // check the nodes that have more than 100
                        {
                            str1 = str.substr(0, str.find(",", 0)); // find file number
                            num = atoi(str1.c_str()); // change file number string into int
                            str.erase(0, str.find(",") + 1); // erase the number to ","
                            str.erase(str.find("."));
                            list.insertNode2(num, str); // insert num and str
                        }
                        else
                        {
                            list.deleteNode(1); // delete first node
                            str1 = str.substr(0, str.find(",", 0));
                            num = atoi(str1.c_str());
                            str.erase(0, str.find(",") + 1);
                            str.erase(str.find("."));
                            list.insertNode2(num, str);
                        }
                        i++;
                    }
                }
                list.printList();
            }
        }
        file.close(); // close the file
    }
    else
    {
        cout << "Unable to open file";
        return 1;
    }
} */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
class Loaded_List_Node // a node of the loaded linked list
{
public:
    int num;
    string a, b;
    Loaded_List_Node* next;
    Loaded_List_Node() // default constructor
    {
        num = 0;
        a.empty();
        b.empty();
        next = NULL;
    }
    Loaded_List_Node(int Num, string A, string B) // parameterised Constructor
    {
        this->num = Num;
        this->a = A;
        this->b = B;
        this->next = NULL;
    }
};
class Loaded_List_Node1 // a node of the loaded linked list
{
public:
    string a;
    Loaded_List_Node1* next;
    Loaded_List_Node1() // default constructor
    {
        a.empty();
        next = NULL;
    }
    Loaded_List_Node1(string A) // parameterised Constructor
    {
        this->a = A;
        this->next = NULL;
    }
};
class Loaded_List
{
private:
    Loaded_List_Node* head; // private member
    Loaded_List_Node1* Head;
public:
    Loaded_List() // default constructor
    {
        head = NULL;
    }
    bool emptyNode()
    {
        if (Head == NULL)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    void insertNode(int Num, string str, string str1)
    {
        Loaded_List_Node* newNode = new Loaded_List_Node(Num, str, str1); // create new node
        if (head == NULL) // assign to head
        {
            head = newNode;
            return;
        }
        Loaded_List_Node* tmp = head;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;  // update temp
        }
        tmp->next = newNode; // insert at the last node
    }
    void insertNode1(string str)
    {
        Loaded_List_Node1* newNode = new Loaded_List_Node1(str); // create new node
        if (Head == NULL) // assign to head
        {
            Head = newNode;
            return;
        }
        Loaded_List_Node1* tmp = Head;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;  // update temp
        }
        tmp->next = newNode; // insert at the last node
    }
    void deleteNode(int node) // function to delete the node at given position
    {
        Loaded_List_Node* tmp1 = head, * tmp2 = NULL;
        int listlen = 0;
        if (head == NULL)
        {
            cout << "List is empty." << endl;
            return;
        }
        while (tmp1 != NULL) // find a length of the loaded linked list
        {
            tmp1 = tmp1->next;
            listlen++;
        }
        if (listlen < node) // check the position that it is less than a length of the loaded linked list
        {
            cout << "Index out of range" << endl;
            return;
        }
        tmp1 = head;
        if (node == 1) // deleting the head node
        {
            head = head->next;
            delete tmp1;
            return;
        }
        while (node-- > 1) // tranverse the list to find the node to be deleted
        {
            tmp2 = tmp1;
            tmp1 = tmp1->next;
        }
        tmp2->next = tmp1->next; // change the next pointer of the previous node
        delete tmp1;
    }
    void printList() // function to print the node of the loaded linked list 
    {
        Loaded_List_Node* tmp = head;
        if (head == NULL)
        {
            cout << "List is empty." << endl;
            return;
        }
        while (tmp != NULL) // tranverse the list
        {
            cout << tmp->b << "/" << tmp->num << endl;
            tmp = tmp->next;
        }
    }
};
int main()
{
    Loaded_List list;
    string line;
    ifstream file("command.txt"); // Open command.txt file
    if (file.is_open()) // check the file has 'command txt'
    {
        while (getline(file, line, '\n'))
        {
            stringstream ss(line);
            string first, second, third;
            ss >> first >> second >> third;
            if (first=="LOAD")
            {
                string str, str1, str2;
                str2 = "img_file";
                int num = 0, i = 0;
                fstream fs;
                fs.open("img_files/filesnumbers.csv", ios::in);
                if (fs.fail()) // check the file has csv file
                {
                    cout << "========ERROR========" << endl;
                    cout << "100" << endl;
                    cout << "=====================" << endl;
                    return 0;
                }
                char a, b, c;
                a = fs.get();
                b = fs.get();
                c = fs.get();
                if (a != (char)0xEF || b != (char)0xBB || c != (char)0xBF) // solving UTF-8 Bom
                {
                    fs.seekg(0);
                }
                list.insertNode1(str2);
                while (!fs.eof())
                {
                    getline(fs, str);
                    if (!str.empty())
                    {
                        if (i < 100) // check the nodes that have more than 100
                        {
                            str1 = str.substr(0, str.find(",", 0)); // find file number
                            num = atoi(str1.c_str()); // change file number string into int
                            str.erase(0, str.find(",") + 1); // erase the number to ","
                            str.erase(str.find("."));
                            list.insertNode(num, str2, str); // insert num and str
                        }
                        else
                        {
                            list.deleteNode(1); // delete first node
                            str1 = str.substr(0, str.find(",", 0));
                            num = atoi(str1.c_str());
                            str.erase(0, str.find(",") + 1);
                            str.erase(str.find("."));
                            list.insertNode(num, str2, str);
                        }
                        i++;
                    }
                }
                cout << "========LOAD=========" << endl;
                list.printList();
                cout << "=====================" << endl;
            }
            else if (first=="ADD")
            {
                if (list.emptyNode() == false)
                {
                    cout << "========ERROR========" << endl;
                    cout << "200" << endl;
                    cout << "=====================" << endl;
                    return 0;
                }
                string str, str1, str2, str3;
                fstream fs;
                int num = 0, i = 0;
                if (second.empty() || third.empty())
                {
                    cout << "========ERROR========" << endl;
                    cout << "200" << endl;
                    cout << "=====================" << endl;
                    return 0;
                }
                str = second;
                list.insertNode1(str);
                str1 = str+'/'+third;
                fs.open(str1, ios::in);
                if (fs.fail()) // check the file has csv file
                {
                    cout << "========ERROR========" << endl;
                    cout << "200" << endl;
                    cout << "=====================" << endl;
                    return 0;
                }
                char a, b, c;
                a = fs.get();
                b = fs.get();
                c = fs.get();
                if (a != (char)0xEF || b != (char)0xBB || c != (char)0xBF) // solving UTF-8 Bom
                {
                    fs.seekg(0);
                }
                while (!fs.eof())
                {
                    getline(fs, str2);
                    if (!str2.empty())
                    {
                        if (i < 100) // check the nodes that have more than 100
                        {
                            str3 = str2.substr(0, str2.find(",", 0)); // find file number
                            num = atoi(str3.c_str()); // change file number string into int
                            str2.erase(0, str2.find(",") + 1); // erase the number to ","
                            str2.erase(str2.find("."));
                            list.insertNode(num, str, str2); // insert num and str
                        }
                        else
                        {
                            list.deleteNode(1); // delete first node
                            str3 = str2.substr(0, str2.find(",", 0)); // find file number
                            num = atoi(str3.c_str()); // change file number string into int
                            str2.erase(0, str2.find(",") + 1); // erase the number to ","
                            str2.erase(str2.find("."));
                            list.insertNode(num, str, str2); // insert num and str
                        }
                        i++;
                    }
                }
                cout << "=========ADD=========" << endl;
                cout << "SUCCESS" << endl;
                cout << "=====================" << endl;
            }
        }
        file.close(); // close the file
    }
    else
    {
        cout << "Unable to open file";
        return 1;
    }
}