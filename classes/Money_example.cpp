#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>
using namespace std; 

class Money {
    public: 
        friend Money operator +(const Money& amount1, const Money& amount2);
        friend Money operator -(const Money& amount1, const Money& amount2);
        friend Money operator -(const Money& amount);
        friend bool operator ==(const Money& amount1, const Money& amount2);
        friend bool operator <(const Money& amount1, const Money& amount2);
        Money (long dollars, int cents);
        Money(long dollars);
        Money();
        double get_value() const;
        friend istream& operator >>(istream& ins, Money& amount); 
        friend ostream& operator <<(ostream& outs, const Money& amount); 
    private:
        long all_cents;
};

class Check {
    public:
        Check();
        Check(int number, Money amount, bool cashed);
        friend ostream& operator <<(ostream& outs, const Check& check);
        friend istream& operator >>(istream& ins, Check& check);
        double get_amount() const;
        int get_id() const; 
        bool is_cashed() const; 
    private:
        int number;
        Money amount;
        bool cashed; 
};

void sort_cashed_checks(Check * check_arr, int check_amount, int cashed_checks);
void sort_checks_by_id(Check * check_arr, int size);
void print_checks(Check * check_arr, int size);
Money count_check_amounts(Check * check_arr, int size);
Money count_deposit_amounts(Money * deposit_arr, int size);
Money get_new_balance(Money old_balance, Money deposits, Money cashed_checks);
int digit_to_int(char c);

int main() {
    int check_amount, cashed_checks = 0; 
    Check current_check;

    cout << "How many checks will you enter today? Enter a positive integer." << endl;
    cin >> check_amount;
    Check * check_arr = new Check[check_amount];

    cout << "Enter checks with the number of each check, the amount of the check, and whether or not it has been cashed (1 or 0)" << endl;
    cout << "For example: 456 -$43.00 1 or 123 $34.00 0" << endl;

    for(int i = 0; i < check_amount; i++) {
        cin >> current_check; 
        check_arr[i] = current_check;

        if(current_check.is_cashed()) {
            cashed_checks++;
        }
    }

    int uncashed_checks = check_amount - cashed_checks;

    sort_cashed_checks(check_arr, check_amount, cashed_checks);
    sort_checks_by_id(check_arr, cashed_checks);
    sort_checks_by_id(check_arr + cashed_checks, uncashed_checks);

    // ENTER DEPOSIT 
    int deposit_amount; 
    Money current_deposit; 
    
    cout << "How many deposits will you enter today? Enter a positive integer." << endl;
    cin >> deposit_amount;
    Money * deposit_arr = new Money[deposit_amount];

    cout << "Enter deposits here in money, for ex. $34.00:" << endl;
    for(int i = 0; i < deposit_amount; i++) {
        cin >> current_deposit; 
        deposit_arr[i] = current_deposit;
    }

    // ENTER BALANCE
    Money old_balance;
    cout << "What is your old account balance? Enter the amount in money, for ex. $300.00" << endl;
    cin >> old_balance;

    Money cashed = count_check_amounts(check_arr, cashed_checks);
    Money deposits = count_deposit_amounts(deposit_arr, deposit_amount);
    Money new_balance = get_new_balance(old_balance, deposits, cashed);

    cout << "Total of cashed checks: " << cashed << "\n\n";
    cout << "New balance: " << new_balance << "\n\n";
    cout << "Difference from old balance: " << new_balance - old_balance << "\n\n"; 

    cout << '\t' <<"--- Checks cashed since last checkbook balancing ---" << endl;
    print_checks(check_arr, cashed_checks);
    cout <<"\n\n";

    cout << '\t' << "--- Checks still not balanced ----" << endl;
    print_checks(check_arr + cashed_checks, uncashed_checks);

    delete [] check_arr;
    delete [] deposit_arr;
    return 0;
}

// DEFINE MONEY FUNCTIONS
Money::Money() {
    all_cents = 0;
}

Money::Money(long dollars, int cents) {
    all_cents = dollars * 100;
    all_cents += cents;
}

Money::Money(long dollars): Money(dollars, 0) {}

Money operator +(const Money& amount1, const Money& amount2) {
    int total_cents = amount1.all_cents + amount2.all_cents;
    return Money((total_cents / 100), (total_cents % 100));
}

Money operator -(const Money& amount1, const Money& amount2) {
    int total_cents = amount1.all_cents - amount2.all_cents;
    return Money((total_cents / 100), (total_cents % 100));
}

Money operator -(const Money& amount) {
    return -1 * amount.all_cents;
}

bool operator ==(const Money& amount1, const Money& amount2) {
    return amount1.all_cents == amount2.all_cents;
}

bool operator <(const Money& amount1, const Money& amount2) {
    return amount1.all_cents < amount2.all_cents;
}

double Money::get_value() const {
    return all_cents;
}

istream& operator >>(istream& ins, Money& amount) {
    char one_char, decimal_point, digit1, digit2;
    long dollars;
    int cents; 
    bool negative = false;

    ins >> one_char;
    if(one_char == '-') {
        negative = true;
        ins >> one_char; //read '$'
    } 

    ins >> dollars >> decimal_point >> digit1 >> digit2; 

/*
    if(one_char != '$' || decimal_point != '.' || isdigit(digit1) || isdigit(digit2)) { // Validation 
        cout << "Error illegal form for money input \n";
        exit(1);
    }
*/

    cents = digit_to_int(digit1) * 10 + digit_to_int(digit2);
    amount.all_cents = dollars * 100 + cents; 

    if(negative)
        amount.all_cents = -amount.all_cents;

    return ins;
}

int digit_to_int(char c) {
    return ( static_cast<int>(c) - static_cast<int>('0'));
}

ostream& operator <<(ostream& outs, const Money& amount){
    long positive_cents, dollars, cents;
    positive_cents = labs(amount.all_cents);
    dollars = positive_cents/100;
    cents = positive_cents%100;

    if(amount.all_cents < 0) 
        outs << "-";
    
    outs << "$" << dollars << ".";

    if(cents < 10) 
        outs << "0";
    
    outs << cents;
    return outs;
}

// DEFINE CHECK FUNCTIONS
Check::Check() {
    number = 0;
    amount = Money();
    cashed = 0;
}

Check::Check(int number, Money amount, bool cashed) {
    this -> number = number;
    this -> amount = amount;
    this -> cashed = cashed; 
}

istream& operator >>(istream& ins, Check& check) {
    int number; Money amount; int cashed;
    
    ins >> number >> amount >> cashed;

    /*
    if(isdigit(number) || (cashed != 0 && cashed != 1)) { // Validation 
        cout << "Error illegal form for check input \n";
        exit(1);
    }
    */

    check.number = number;
    check.amount = amount;

    if(cashed == 1) { 
        check.cashed = true;
    } else {
        check.cashed = false;
    }
  
    return ins;
}

ostream& operator <<(ostream& outs, const Check& check) {
    outs << "Number: " << check.number << endl;
    outs << "Amount: " << check.amount << endl;
    outs << "Cashed: "; 

    if(check.cashed)
        outs << "true" << endl;
    else 
        outs << "false" << endl;

    return outs;
}

bool Check::is_cashed() const{
    return cashed; 
}

int Check::get_id() const{
    return number; 
}

double Check::get_amount() const{
    return amount.get_value();
}

void print_checks(Check * check_arr, int size) {
    for(int i = 0; i < size; i++) {
        cout << check_arr[i] << endl;
    }
}

Money get_new_balance(Money old_balance, Money deposits, Money cashed_checks) {
    return old_balance + deposits - cashed_checks; 
}

Money count_check_amounts(Check * check_arr, int size) {
    int total = 0;
    
    for(int i = 0; i < size; i++) {
        total += check_arr[i].get_amount();
    }

    int dollars = total / 100;
    int cents = total % 100; 

    return Money(dollars, cents);
}

Money count_deposit_amounts(Money * money_arr, int size) {
    int total = 0;
    
    for(int i = 0; i < size; i++) {
        total += money_arr[i].get_value();
    }

    int dollars = total / 100;
    int cents = total % 100; 

    return Money(dollars, cents);
}

void sort_cashed_checks(Check * check_arr, int check_amount, int cashed_checks) {
    int sort_cashed = 0;
    int i_to_swap = -1;
    int i = 0, j = check_amount - 1;

    while(sort_cashed < cashed_checks) {

        if(check_arr[i].is_cashed()) { // checks should be cashed 
            i++; sort_cashed++;
        } else if(i_to_swap == -1){
            i_to_swap = i;
        }
            
        if(check_arr[j].is_cashed()) { // checks should not be cahsed 
            if(i_to_swap != -1) {
                Check cashed = check_arr[j];
                check_arr[j] = check_arr[i_to_swap];
                check_arr[i_to_swap] = cashed; 
                i_to_swap = -1; 
                j--; 
                i++; sort_cashed++;
            } 
        } else {
            j--;
        }
    }
}

// sort groups of checks by id number: selection sort
void sort_checks_by_id(Check * check_arr, int size) {
 int min_index;

    for(int i = 0; i < (size - 1); i++) {
        min_index = i;

        for(int j = i + 1; j < size; j++) {
            if(check_arr[j].get_id() < check_arr[min_index].get_id()) {
                min_index = j;
            }  
        }
       
        Check new_min = check_arr[min_index];
        check_arr[min_index] = check_arr[i];
        check_arr[i] = new_min;
    }
}