#include <iostream>
using namespace std; 

class BankAccount {
    public:
        void add_deposits(double * arr, int size); 
        void get_statement();
        BankAccount(): total(0), deposit_arr(nullptr), deposit_amt(0) {}
        BankAccount(const BankAccount& rhs);
        BankAccount& operator =(const BankAccount& rhs);
        ~BankAccount();
    private:
        double * deposit_arr; 
        int deposit_amt;
        double total; 
};

// copy constructor
BankAccount::BankAccount(const BankAccount& rhs) {
    total = rhs.total;
    deposit_amt = rhs.deposit_amt;

    if(deposit_amt != 0) {
        deposit_arr = new double[deposit_amt];

        for(int i = 0; i < deposit_amt; i++) {
            deposit_arr[i] = rhs.deposit_arr[i];
        }
    }
}

// overloaded assignment operator
BankAccount& BankAccount::operator =(const BankAccount& rhs) {
    total = rhs.total; 
    deposit_amt = rhs.deposit_amt;

    delete [] deposit_arr;

    if(deposit_amt != 0) {
        deposit_arr = new double[deposit_amt];

        for(int i = 0; i < deposit_amt; i++) {
            deposit_arr[i] = rhs.deposit_arr[i];
        }
    }
    
     return *this;
}

// destructor 
BankAccount::~BankAccount(){
    delete [] deposit_arr;
}

void BankAccount::add_deposits(double * arr, int size) {
    deposit_arr = arr;
    deposit_amt = size; 

    double total;
    for(int i = 0; i < size; i++) {
        total += arr[i];
    }

    this->total = total; 
}

void BankAccount::get_statement() {
    for(int i = 0; deposit_amt != 0  && i < deposit_amt; i++ ) {
        cout << (deposit_arr + i) << ": " << deposit_arr[i] << endl;
    }

    cout << "Total: " << total << endl; 
}

int main() {
    BankAccount acc1, acc2;

    int deposit_num = 3;
    double * deposit_arr = new double[deposit_num];
    for(int i = 0; i < deposit_num; i++) {
        deposit_arr[i] = 1.00;
    }

    acc1.add_deposits(deposit_arr, deposit_num); 

    cout << "Account 1" << endl;
    acc1.get_statement();

    acc2 = acc1;

    cout << "Account 2" << endl;
    acc2.get_statement();

    BankAccount acc3 = acc1;

    cout << "Account 3" << endl;
    acc3.get_statement();


    return 0;
}


    /*
    int deposit_num;
    cout << "How many deposits?" << endl;
    cin >> deposit_num;

    double * deposit_arr = new double[deposit_num];
    double current_deposit; 
    cout << "Enter deposits as a double. Separate each deposit by a line." << endl;

    for(int i = 0; i < deposit_num; i++) {
        cin >> current_deposit; 
        deposit_arr[i] = current_deposit;
    } */
