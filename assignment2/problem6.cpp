#include <iostream>

using namespace std;

struct node
{
    int data;
    node *next;
};

class linked_list
{
private:
    node *head,*tail;
public:
    linked_list()
    {
        head = NULL;
        tail = NULL;
    }

    void add_node(int n)
    {
        node *tmp = new node;
        tmp->data = n;
        tmp->next = NULL;

        if(head == NULL)
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            tail->next = tmp;
            tail = tail->next;
        }
    }

    node* get_head(){
        return head;
    }

    void reverse(){
        node *tmp = NULL;
        node *next = head;
        node *future = head->next;
        while (next != tail){
            next->next = tmp;
            tmp = next;
            next = future;
            future = future->next;
        }
        next->next = tmp;
        tail = head;
        head = next;
    }

    void display()
    {
        node *tmp;
        tmp = head;
        while (tmp != NULL)
        {
            cout << tmp->data << endl;
            tmp = tmp->next;
        }
    }
};

int main()
{
    linked_list a;
    a.add_node(1);
    a.add_node(2);
    a.add_node(3);
    a.add_node(4);
    a.add_node(5);
    a.add_node(6);
    a.display();
    cout << endl;
    a.reverse();
    a.display();
    return 0;

    
}
