#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct Book {
    string title, author, isbn;
    bool issued = false;
};

class Library {
    vector<Book> books;
public:
    void load() {
        ifstream f("lib.data");
        string l;
        while (getline(f, l)) {
            // title|author|isbn|issued
            auto p1 = l.find('|');
            auto p2 = l.find('|', p1+1);
            auto p3 = l.find('|', p2+1);
            if (p1 != string::npos && p2 != string::npos && p3 != string::npos) {
                string t = l.substr(0, p1);
                string a = l.substr(p1+1, p2-p1-1);
                string i = l.substr(p2+1, p3-p2-1);
                bool iss = l.substr(p3+1) == "1";
                books.push_back({t, a, i, iss});
            }
        }
    }

    void save() {
        ofstream f("lib.data");
        for (auto& b : books) {
            f << b.title << '|' << b.author << '|' << b.isbn << '|' << b.issued << '\n';
        }
    }

    void add() {
        string t,a,i;
        cout << "Title: "; getline(cin, t);
        cout << "Author: "; getline(cin, a);
        cout << "ISBN: "; getline(cin, i);
        books.push_back({t,a,i});
        cout << "Added.\n";
    }

    void list() {
        cout << "\nID Title Author ISBN Status\n";
        for (int i=0; i<books.size(); i++) {
            cout << i << ' ' << books[i].title << ' ' << books[i].author << ' ' << books[i].isbn << ' ' 
                 << (books[i].issued ? "Issued" : "Avail") << '\n';
        }
    }

    void issue(int id) {
        if (id>=0 && id<books.size() && !books[id].issued) {
            books[id].issued = true;
            cout << "Issued.\n";
        }
    }

    void ret(int id) {
        if (id>=0 && id<books.size() && books[id].issued) {
            books[id].issued = false;
            cout << "Returned.\n";
        }
    }

    void del(int id) {
        if (id>=0 && id<books.size()) {
            books.erase(books.begin()+id);
            cout << "Deleted.\n";
        }
    }
};

int main() {
    Library l;
    l.load();
    int ch, id;
    cout << "Library: 1 add 2 list 3 issue 4 ret 5 del 0 quit\n";
    while (cin >> ch, ch) {
        if (ch==1) l.add();
        else if (ch==2) l.list();
        else {
            cout << "ID: ";
            cin >> id;
            if (ch==3) l.issue(id);
            else if (ch==4) l.ret(id);
            else if (ch==5) l.del(id);
        }
        l.save();
    }
    return 0;
}

