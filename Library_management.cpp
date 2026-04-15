#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdio>
#include<string>
using namespace std;

class Book
{
public:
    int id;
    string name;
    string author;
};

bool parseBook(string line, Book &b)
{
    stringstream ss(line);
    string tempId;

    getline(ss, tempId, '|');
    getline(ss, b.name, '|');
    getline(ss, b.author, '|');

    if(tempId == "")
        return false;

    b.id = stoi(tempId);
    return true;
}

bool isDuplicateId(int checkId)
{
    ifstream file("books.txt");
    string line;
    Book b;

    while(getline(file, line))
    {
        if(parseBook(line, b))
        {
            if(b.id == checkId)
            {
                file.close();
                return true;
            }
        }
    }

    file.close();
    return false;
}

void addBook()
{
    Book b;

    cout << "Enter Book ID: ";
    cin >> b.id;
    cin.ignore();

    if(isDuplicateId(b.id))
    {
        cout << "Book ID Already Exists!";
        return;
    }

    cout << "Enter Book Name: ";
    getline(cin, b.name);

    cout << "Enter Author Name: ";
    getline(cin, b.author);

    ofstream file("books.txt", ios::app);

    file << b.id << "|" << b.name << "|" << b.author << endl;

    file.close();

    cout << "Book Added Successfully!";
}

void showBooks()
{
    ifstream file("books.txt");
    string line;
    Book b;
    bool found = false;

    while(getline(file, line))
    {
        if(parseBook(line, b))
        {
            cout << "\n--------------------------------";
            cout << "\nID      : " << b.id;
            cout << "\nName    : " << b.name;
            cout << "\nAuthor  : " << b.author;
            cout << "\n--------------------------------\n";

            found = true;
        }
    }

    file.close();

    if(!found)
        cout << "No Books Found!";
}

void searchBook()
{
    int searchId;
    cout << "Enter Book ID to Search: ";
    cin >> searchId;

    ifstream file("books.txt");
    string line;
    Book b;
    bool found = false;

    while(getline(file, line))
    {
        if(parseBook(line, b))
        {
            if(b.id == searchId)
            {
                cout << "\nBook Found!";
                cout << "\nID      : " << b.id;
                cout << "\nName    : " << b.name;
                cout << "\nAuthor  : " << b.author;

                found = true;
                break;
            }
        }
    }

    file.close();

    if(!found)
        cout << "Book Not Found!";
}

void updateBook()
{
    int updateId;
    cout << "Enter Book ID to Update: ";
    cin >> updateId;
    cin.ignore();

    ifstream file("books.txt");
    ofstream temp("temp.txt");

    string line;
    Book b;
    bool found = false;

    while(getline(file, line))
    {
        if(parseBook(line, b))
        {
            if(b.id == updateId)
            {
                found = true;

                cout << "Enter New Book ID: ";
                cin >> b.id;
                cin.ignore();

                cout << "Enter New Book Name: ";
                getline(cin, b.name);

                cout << "Enter New Author Name: ";
                getline(cin, b.author);
            }

            temp << b.id << "|" << b.name << "|" << b.author << endl;
        }
    }

    file.close();
    temp.close();

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if(found)
        cout << "Book Updated Successfully!";
    else
        cout << "Book Not Found!";
}

void deleteBook()
{
    int deleteId;
    cout << "Enter Book ID to Delete: ";
    cin >> deleteId;

    ifstream file("books.txt");
    ofstream temp("temp.txt");

    string line;
    Book b;
    bool found = false;

    while(getline(file, line))
    {
        if(parseBook(line, b))
        {
            if(b.id == deleteId)
            {
                found = true;
                continue;
            }

            temp << b.id << "|" << b.name << "|" << b.author << endl;
        }
    }

    file.close();
    temp.close();

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if(found)
        cout << "Book Deleted Successfully!";
    else
        cout << "Book Not Found!";
}

void totalBooks()
{
    ifstream file("books.txt");
    string line;
    int total = 0;

    while(getline(file, line))
    {
        if(line != "")
            total++;
    }

    file.close();

    cout << "Total Books: " << total;
}

int main()
{
    string user, pass;
    int choice;

    cout << "Enter Username: ";
    cin >> user;

    cout << "Enter Password: ";
    cin >> pass;

    if(user != "admin" || pass != "1234")
    {
        cout << "Wrong Username or Password!";
        return 0;
    }

    do
    {
        cout << "\n\n===== Library Management System =====";
        cout << "\n1. Add Book";
        cout << "\n2. Show All Books";
        cout << "\n3. Search Book";
        cout << "\n4. Update Book";
        cout << "\n5. Delete Book";
        cout << "\n6. Total Books";
        cout << "\n7. Exit";
        cout << "\nEnter Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                cin.ignore();
                addBook();
                break;

            case 2:
                showBooks();
                break;

            case 3:
                searchBook();
                break;

            case 4:
                updateBook();
                break;

            case 5:
                deleteBook();
                break;

            case 6:
                totalBooks();
                break;

            case 7:
                cout << "Thank You!";
                break;

            default:
                cout << "Invalid Choice!";
        }

    } while(choice != 7);

    return 0;
}