#include <iostream>
#include <ctime> 
using namespace std; 

class Cell {
    int x;
    int y; 
    public:
        Cell(int x_data = 0, int y_data = 0): x(x_data), y(y_data) {}
        friend ostream& operator <<(ostream& outs, const Cell& cell); 
};

ostream& operator <<(ostream& outs, const Cell& cell) {
    outs << cell.x << " " << cell.y << endl;
    return outs; 
}

template <class T>
class List; 

template <class T>
class Node {
    T data;
    Node<T>* next;
    Node<T>* prev;
    public: 
        Node(T dat = T(), Node<T>* n = nullptr, Node<T>* p = nullptr): data(dat), next(n), prev(p) {}
        friend class List<T>; 
};

template <class T>
class List {
    Node<T>* head;
    Node<T>* tail; 
    public:
        List();
        List(const List<T>& rhs);
        List<T>& operator =(const List<T>& rhs);
        ~List(); 
        void insert_at_tail(T data);
        void remove_from_head();
        void clear(); 
        bool is_empty() const; 
        void print() const; 
};

// create list w/ dummy head + tail 
template <class T>
List<T>::List() {
    head = new Node<T>();
    tail = new Node<T>(); 

    head->next = tail;
    tail->prev = head; 
}

// copy constructor 
template <class T>
List<T>::List(const List<T>& rhs) {
    head = new Node<T>();
    tail = new Node<T>(); 

    head->next = tail;
    tail->prev = head;    
    *this = rhs; 
}

template <class T>
List<T>& List<T>::operator=(const List<T>& rhs) {
    if(this == &rhs) {
        return *this;
    }

    // clear any existing data
    clear(); 

    //copy + insert all data 
    Node<T>* n = rhs.head->next; 
    while(n != rhs.tail) {
        insert_at_tail(n->data);
        n = n->next;
    }

    return *this; 
}

// destructor 
template <class T> 
List<T>::~List() {
    clear(); 
    delete head;
    delete tail; 
}

template <class T>
void List<T>::insert_at_tail(T data) {
    Node<T>* new_node = new Node<T>(data);

    Node<T>* old_end = tail->prev; 

    // [old_end] <- [new_node] -> [tail]
    new_node->prev = old_end; 
    new_node->next = tail; 

    // [old_end] -> [new_node] <- [tail]
    tail->prev = new_node;
    old_end->next = new_node;
}

template <class T>
bool List<T>::is_empty() const {
    return head->next == tail; 
}

template <class T>
void List<T>::remove_from_head() {
    Node<T>* to_delete = head->next; 
    Node<T>* new_start = to_delete->next; 

    head->next = new_start;
    new_start->prev = head; 

    delete to_delete; 
}

template <class T>
void List<T>::clear() {
    while(!is_empty()) {
        remove_from_head(); 
    }
}

template <class T>
void List<T>::print() const {
    Node<T>* n = head->next; 
    while(n != tail) {
        cout << n->data; 
        n = n->next; 
    }
}

int main() {
   List<Cell> l1;
  

   for(int i = 0; i < 10; i++) {
       l1.insert_at_tail(Cell(rand() % 10 + 1, rand() % 10 + 1));
   }

    List<Cell> l2 = l1;  
    cout << "List 1:\n";
    l1.print();

    cout << "\nList 2:\n";
    l2.print();

    return 0;
}