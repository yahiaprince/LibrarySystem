#include <bits/stdc++.h>
using namespace std;

class IBook
{
public:
    virtual void read() = 0;
    virtual bool borrow(int user_id) = 0;
    virtual void return_copy() = 0;
    virtual bool has_prefix(string prefix) = 0;
    virtual void print() = 0;
    virtual ~IBook() {}
};
class Book
{
    int id;
    string name;
    int total_quantity;
    int total_borrowed;

public:
    Book() : id(-1), name(""), total_quantity(0), total_borrowed(0) {}

    void read()
    {
        cout << "Enter book info: id & name & total quantity: ";
        cin >> id >> name >> total_quantity;
        total_borrowed = 0;
    }

    bool borrow(int user_id)
    {
        if (total_quantity - total_borrowed == 0)
            return false;
        ++total_borrowed;
        return true;
    }

    void return_copy()
    {
        assert(total_borrowed > 0);
        --total_borrowed;
    }

    bool has_prefix(const string &prefix) const
    {
        return name.compare(0, prefix.size(), prefix) == 0;
    }

    void print() const
    {
        cout << "id = " << id << " name = " << name << " total_quantity "
             << total_quantity << " total_borrowed " << total_borrowed
             << "\n";
    }

    int get_id() const
    {
        return id;
    }

    string get_name() const
    {
        return name;
    }
};

class User
{
    int id;
    string name;
    vector<int> borrowed_books_ids;

public:
    User() : id(-1), name("") {}

    void read()
    {
        cout << "Enter user name & national id: ";
        cin >> name >> id;
    }

    void borrow(int book_id)
    {
        borrowed_books_ids.push_back(book_id);
    }

    void return_copy(int book_id)
    {
        auto it = find(borrowed_books_ids.begin(), borrowed_books_ids.end(), book_id);
        if (it != borrowed_books_ids.end())
            borrowed_books_ids.erase(it);
        else
            cout << "User " << name << " never borrowed book id " << book_id << "\n";
    }

    bool is_borrowed(int book_id) const
    {
        return find(borrowed_books_ids.begin(), borrowed_books_ids.end(), book_id) != borrowed_books_ids.end();
    }

    void print() const
    {
        cout << "user " << name << " id " << id << " borrowed books ids: ";
        for (int book_id : borrowed_books_ids)
            cout << book_id << " ";
        cout << "\n";
    }

    string get_name() const
    {
        return name;
    }
};

class BookManager
{
    vector<Book> books;

public:
    void add_book()
    {
        Book book;
        book.read();
        books.push_back(book);
    }

    void search_books_by_prefix() const
    {
        cout << "Enter book name prefix: ";
        string prefix;
        cin >> prefix;
        bool found = false;
        for (const auto &book : books)
        {
            if (book.has_prefix(prefix))
            {
                cout << book.get_name() << "\n";
                found = true;
            }
        }
        if (!found)
            cout << "No books with such prefix\n";
    }

    int find_book_idx_by_name(const string &name) const
    {
        for (size_t i = 0; i < books.size(); ++i)
        {
            if (books[i].get_name() == name)
                return i;
        }
        return -1;
    }

    Book &get_book_by_idx(int idx)
    {
        return books[idx];
    }

    void print_books_sorted_by_id() const
    {
        vector<Book> sorted_books = books;
        sort(sorted_books.begin(), sorted_books.end(), [](const Book &a, const Book &b)
             { return a.get_id() < b.get_id(); });
        for (const auto &book : sorted_books)
        {
            book.print();
        }
    }

    void print_books_sorted_by_name() const
    {
        vector<Book> sorted_books = books;
        sort(sorted_books.begin(), sorted_books.end(), [](const Book &a, const Book &b)
             { return a.get_name() < b.get_name(); });
        for (const auto &book : sorted_books)
        {
            book.print();
        }
    }
};

class UserManager
{
    vector<User> users;

public:
    void add_user()
    {
        User user;
        user.read();
        users.push_back(user);
    }

    int find_user_idx_by_name(const string &name) const
    {
        for (size_t i = 0; i < users.size(); ++i)
        {
            if (users[i].get_name() == name)
                return i;
        }
        return -1;
    }

    User &get_user_by_idx(int idx)
    {
        return users[idx];
    }

    void print_users() const
    {
        for (const auto &user : users)
        {
            user.print();
        }
    }

    void print_who_borrowed_book(int book_id) const
    {
        for (const auto &user : users)
        {
            if (user.is_borrowed(book_id))
                cout << user.get_name() << "\n";
        }
    }
};

class LibrarySystem
{
    BookManager book_manager;
    UserManager user_manager;

public:
    void run()
    {
        while (true)
        {
            int choice = menu();
            if (choice == 1)
                book_manager.add_book();
            else if (choice == 2)
                book_manager.search_books_by_prefix();
            else if (choice == 3)
                print_who_borrowed_book();
            else if (choice == 4)
                book_manager.print_books_sorted_by_id();
            else if (choice == 5)
                book_manager.print_books_sorted_by_name();
            else if (choice == 6)
                user_manager.add_user();
            else if (choice == 7)
                user_borrow_book();
            else if (choice == 8)
                user_return_book();
            else if (choice == 9)
                user_manager.print_users();
            else
                break;
        }
    }

    int menu()
    {
        int choice = -1;
        while (choice == -1)
        {
            if (false)
            {
                cout << "\nLibrary Menu;\n";
                cout << "1) add_book\n";
                cout << "2) search_books_by_prefix\n";
                cout << "3) print_who_borrowed_book_by_name\n";
                cout << "4) print_library_by_id\n";
                cout << "5) print_library_by_name\n";
                cout << "6) add_user\n";
                cout << "7) user_borrow_book\n";
                cout << "8) user_return_book\n";
                cout << "9) print_users\n";
                cout << "10) Exit\n";
            }

            cout << "\nEnter your menu choice [1 - 10]: ";
            cin >> choice;

            if (!(1 <= choice && choice <= 10))
            {
                cout << "Invalid choice. Try again\n";
                choice = -1; // loop keep working
            }
        }
        return choice;
    }

    void user_borrow_book()
    {
        int user_idx, book_idx;
        if (!read_user_and_book(user_idx, book_idx))
            return;

        User &user = user_manager.get_user_by_idx(user_idx);
        Book &book = book_manager.get_book_by_idx(book_idx);

        if (!book.borrow(user_idx))
            cout << "No more copies available right now\n";
        else
            user.borrow(book.get_id());
    }

    void user_return_book()
    {
        int user_idx, book_idx;
        if (!read_user_and_book(user_idx, book_idx))
            return;

        User &user = user_manager.get_user_by_idx(user_idx);
        Book &book = book_manager.get_book_by_idx(book_idx);

        book.return_copy();
        user.return_copy(book.get_id());
    }

    bool read_user_and_book(int &user_idx, int &book_idx)
    {
        string user_name, book_name;
        cout << "Enter user name and book name: ";
        cin >> user_name >> book_name;

        user_idx = user_manager.find_user_idx_by_name(user_name);
        if (user_idx == -1)
        {
            cout << "Invalid user name\n";
            return false;
        }

        book_idx = book_manager.find_book_idx_by_name(book_name);
        if (book_idx == -1)
        {
            cout << "Invalid book name\n";
            return false;
        }

        return true;
    }

    void print_who_borrowed_book()
    {
        string book_name;
        cout << "Enter book name: ";
        cin >> book_name;

        int book_idx = book_manager.find_book_idx_by_name(book_name);
        if (book_idx == -1)
        {
            cout << "Invalid book name\n";
            return;
        }

        Book &book = book_manager.get_book_by_idx(book_idx);
        if (book.get_id() == 0)
        {
            cout << "No borrowed copies\n";
        }
        else
        {
            user_manager.print_who_borrowed_book(book.get_id());
        }
    }
};

int main()
{
    LibrarySystem library;
    library.run();
    return 0;
}
