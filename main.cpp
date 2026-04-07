#include <iostream>
#include <cstdio>
using namespace std;

namespace LIST
{

struct NODE
{
    int data;
    NODE *prev;
    NODE *next;
    NODE(int d = 0, NODE *p = nullptr, NODE *n = nullptr): data(d), prev(p), next(n) {}
};

NODE *head = nullptr, *tail = nullptr;
int len = 0;

void Pre()
{
    head = nullptr;
    tail = nullptr;
    len = 0;
}

NODE* move(int i)
{
    if (i < 0 || i >= len) return nullptr;
    NODE *cur = head;
    if (i <= len / 2) {
        cur = head;
        for (int j = 0; j < i; ++j) {
            cur = cur->next;
        }
    } else {
        cur = tail;
        for (int j = len - 1; j > i; --j) {
            cur = cur->prev;
        }
    }
    return cur;
}

void insert(int i, int x)
{
    if (i < 0 || i > len) return;
    if (len == 0) {
        head = tail = new NODE(x);
    } else if (i == 0) {
        NODE *node = new NODE(x, nullptr, head);
        head->prev = node;
        head = node;
    } else if (i == len) {
        NODE *node = new NODE(x, tail, nullptr);
        tail->next = node;
        tail = node;
    } else {
        NODE *cur = move(i);
        NODE *node = new NODE(x, cur->prev, cur);
        cur->prev->next = node;
        cur->prev = node;
    }
    len++;
}

void remove(int i)
{
    if (i < 0 || i >= len) return;
    NODE *cur = move(i);
    if (cur->prev) {
        cur->prev->next = cur->next;
    } else {
        head = cur->next;
    }
    if (cur->next) {
        cur->next->prev = cur->prev;
    } else {
        tail = cur->prev;
    }
    delete cur;
    len--;
}

int Get_length()
{
    return len;
}

int Query(int i)
{
    if (i < 0 || i >= len) return -1;
    NODE *cur = move(i);
    if (cur) return cur->data;
    return -1;
}

void Print()
{
    if (len == 0) {
        cout << -1 << "\n";
        return;
    }
    NODE *cur = head;
    while (cur) {
        cout << cur->data;
        if (cur->next) cout << " ";
        cur = cur->next;
    }
    cout << "\n";
}

void Clear()
{
    NODE *cur = head;
    while (cur) {
        NODE *nx = cur->next;
        delete cur;
        cur = nx;
    }
    head = tail = nullptr;
    len = 0;
}

}
int n;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;
    int op, x, p, ans;
    LIST::Pre();
    for (int _=0; _<n; ++_)
    {
        cin >> op;
        switch(op)
        {
            case 0:
                ans = LIST::Get_length();
                cout << ans << "\n";
                break;
            case 1:
                cin >> p >> x;
                LIST::insert(p,x);
                break;
            case 2:
                cin >> p;
                ans = LIST::Query(p);
                cout << ans << "\n";
                break;
            case 3:
                cin >> p;
                LIST::remove(p);
                break;
            case 4:
                LIST::Print();
                break;
        }
    }
    LIST::Clear();
    return 0;
}
