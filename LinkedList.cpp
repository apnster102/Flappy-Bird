#include<iostream>

using namespace std;

struct node{
	int data;
	node *next;
    node()
    {
        data = 0;
        next = NULL;
    }

    node(int _data)
    {
        data = _data;
        next = NULL;
    }

    void printList()
    {
        node *p = this;
        while (p != NULL){
            cout << p->data << " ";
            p = p->next;
	    }
    }
    node *addElement(int x)
    {
        node *temp = new node(x);
        next = temp;
        return temp;
    }
};


int main(){
	int n, x;
	cin >> n;
	cin >> x;
	node *l = new node(x);
	node *p = l;
	for (int i = 1; i < n; i++){
		cin >> x;
		p = p->addElement(x);
	}
	l->printList();
	return 0;
}
