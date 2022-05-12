#include <iostream>
#include <ctime> 
using namespace std; 

class Letter {
    char symbol;
    public:
        Letter(char s = ' '): symbol(s) {}
        friend ostream& operator <<(ostream& outs, const Letter& cell); 
};

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
        void print_addresses() const; 
        void reverse(); 
};

// REVERSE
// head A B C D E tail      ---->     head E D C B A tail

// Store the current and previous node 
// Loop through nodes 
// Save the "old" next node from the current node N
// Flip the pointers so N->next is the previous node and vice versa 
// Set the current node to the old next node, and the prev node to the old current node
// Stop when the current node is the tail 
// After the loop, set the last prev node->prev = head, the head->next, and tail->prev 

template <class T>
void List<T>::reverse() {
    Node<T>* current_node = head->next; 
    Node<T>* prev_node = tail; 

    while(current_node != tail) {
        Node<T>* old_next = current_node->next; 

        current_node->next = prev_node;
        current_node->prev = old_next;

        prev_node = current_node;
        current_node = old_next; 
    }

    prev_node->prev = head;
    tail->prev = head->next; 
    head->next = prev_node;     
}

int main() {
   List<Letter> l1;
  
   for(int i = 0; i < 10; i++) {
       l1.insert_at_tail(Letter('a' + i));
   }

    cout << "List 1:\n";
    l1.print();

    l1.reverse(); 

    cout << "\nList 1 reversed:\n";
    l1.print();

    return 0;
}

ostream& operator <<(ostream& outs, const Letter& letter) {
    outs << letter.symbol << " ";
    return outs; 
}

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
void List<T>::print_addresses() const {
    Node<T>* n = head->next; 
    while(n != tail) {
        cout << "prev: " << n->prev << " current: " << n << " " << n->data << " next: " << n->next << endl; 
        n = n->next; 
    }
}

template <class T>
void List<T>::print() const {
    Node<T>* n = head->next; 
    while(n != tail) {
        cout << n->data << " "; 
        n = n->next; 
    }
}