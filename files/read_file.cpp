#include <iostream>
#include <fstream>
#include <string> 
#include <vector>
using namespace std; 

class Food {
    string name;
    double price;
    int aisle;  
    public:
        Food(string n, double p, int a): name(n), price(p), aisle(a) {}
        friend ostream& operator <<(ostream& outs, const Food& food);
};

ostream& operator <<(ostream& outs, const Food& food) {
    outs << food.name << ", $" << food.price << ", aisle " << food.aisle << endl; 
    return outs; 
}

int main() {
    ifstream in_file; 
    string file_name; 
    cout << "Enter the name of the file to open (hint: in_txt.txt)" << endl; 
    cin >> file_name; 

    in_file.open(file_name);
    while(!in_file) {
        cout << "There was an erroring opening that file. Enter another file name." << endl;
        cin >> file_name; 
        in_file.clear();
        in_file.open(file_name); 
    }

    vector<Food> shopping_list; 

    string curr_name;
    double curr_price;
    int curr_aisle; 
    while(in_file >> curr_price >> curr_aisle) {
        getline(in_file, curr_name);
        shopping_list.push_back(Food(curr_name, curr_price, curr_aisle)); 
    }

    in_file.close(); 

    for(Food i: shopping_list) {
        cout << i; 
    }

    return 0;
}