#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

const int BOARD = 20; 
const int DB_COUNT = 5;
const int ANT_COUNT = 100;
const string ANT_STR = "ant";
const string DB_STR = "doodlebug"; 
const int ANT_BREED = 3;
const int DB_BREED = 8;
const int DB_STARVE = 3;

class Cell {
    public:
        int get_row() { return row; }
        int get_col() { return col; }
        Cell(): row(-1), col(-1) {}
        Cell(int x, int y): row(x), col(y){}
        void set_row_col(int x, int y) { row = x, col = y; }
    private:
        int row; 
        int col; 
};

class Organism {
    public:
        Organism();
        Organism(int r, int c, string name);
        int get_row();
        int get_col();
        string get_type() { return type; }
        bool has_moved() { return moved; }
        void set_moved(bool bug_moved);
        void set_row_col(int x, int y);
        void reset_breeding(int x);
        void look_around(vector<Organism*>& bug_list, vector<Cell*>& adjacent_cells);
        virtual Organism* move(vector<Organism*>& bug_list);
        void after_moving(vector<Organism*>& bug_list);
        virtual void breed(vector<Organism*>& bug_list) =0;
        void die(vector<Organism*>& bug_list);
    private:
        Cell coordinates; 
        string type;
        int until_breed; 
        bool moved; 
};

class Doodlebug: public Organism {
    private:
        int until_starve;
    public: 
        Doodlebug():Organism(){}
        Doodlebug(int r, int c);
        virtual Organism* move(vector<Organism*>& bug_list);
        virtual void breed(vector<Organism*>& bug_list);
        void hunt(vector<Organism*>& bug_list, vector<Organism*>& potential_prey);
};

class Ant: public Organism {
    public: 
        Ant():Organism(){}
        Ant(int r, int c);
        virtual Organism* move(vector<Organism*>& bug_list);
        virtual void breed(vector<Organism*>& bug_list);
};

// Play game 
void spawn_bugs(vector<Organism*>& bug_list);
void generate_board(vector<Organism*>& vec, bool& playing);
void next_turn(vector<Organism*>& vec, int size, string type);
void extinction(int ant_count, int db_count, bool& playing); 

// Helper functions
Organism* check_cell(int x, int y, vector<Organism*>& vec);
vector<Cell> get_nearby_cells(int x, int y);
void check_if_ant(int x, int y, vector<Organism*>& vec, vector<Organism*>& ants);
void check_if_empty(int x, int y, vector<Organism*>& vec, vector<Cell>& cells);
bool cell_on_board(int row, int col);
int rand_num(int max);
int get_bug_index(vector<Organism*>& vec, Organism* bug);

int main() {
    srand(time(0));
    vector<Organism*> bug_list; 
    spawn_bugs(bug_list);

    bool playing = true; 
    generate_board(bug_list, playing);

    while(playing) {
    cout << "Press enter for another turn." << endl;
      if(cin.get() == '\n') {
            next_turn(bug_list, bug_list.size(), DB_STR);
            next_turn(bug_list, bug_list.size(), ANT_STR);
            generate_board(bug_list, playing);
        }
    }

    bug_list.clear();
}

void Organism::die(vector<Organism*>& bug_list) {
    int i = get_bug_index(bug_list, this);
    bug_list.erase(bug_list.begin() + i);
}

// countdown the steps until breeding + breed if countdown ends 
void Organism::after_moving(vector<Organism*>& bug_list) {
    until_breed -= 1;
    moved = true;

    if(until_breed == 0) 
        breed(bug_list);
}

// breed an ant in adjacent empty cell
void Ant::breed(vector<Organism*>& bug_list) {
    reset_breeding(ANT_BREED);

    vector<Cell*> adjacent_cells; 
    look_around(bug_list, adjacent_cells);

    if(adjacent_cells.size() != 0) {
        Cell* new_cell = adjacent_cells[rand_num((adjacent_cells.size()))];
        Organism* o_ptr;
        Ant* a_ptr = new Ant(new_cell->get_row(), new_cell->get_col());
        o_ptr = a_ptr; 
        bug_list.push_back(o_ptr);
    }

    adjacent_cells.clear();
}

// breed a doodlebug in adjacent empty cell
void Doodlebug::breed(vector<Organism*>& bug_list) {
    reset_breeding(DB_BREED);
    
    vector<Cell*> adjacent_cells; 
    look_around(bug_list, adjacent_cells);

    if(adjacent_cells.size() != 0) {
        Cell* new_cell = adjacent_cells[rand_num((adjacent_cells.size()))];
        Organism* o_ptr;
        Doodlebug* a_ptr = new Doodlebug(new_cell->get_col(), new_cell->get_col());
        o_ptr = a_ptr; 
        bug_list.push_back(o_ptr);
    }

    adjacent_cells.clear();
}

// eat ant if possible, move the doodlebug into the ant's cell and kill the ant 
Organism* Doodlebug::move(vector<Organism*>& bug_list) {
    vector<Organism*> potential_prey; 
    hunt(bug_list, potential_prey); 

    Organism* new_cell = this;

    if(potential_prey.size() != 0) {                                            
        Organism* eaten = potential_prey[rand_num(potential_prey.size())]; 
        int x = eaten->get_row();
        int y = eaten->get_col();  
        eaten->die(bug_list);
        set_row_col(x, y);                     
        until_starve = DB_STARVE;
    } else {
        until_starve--;
        if(until_starve == 0) {
            die(bug_list);
            return this; 
        }

        new_cell = Organism::move(bug_list);
    }

    potential_prey.clear();

    return new_cell;
}

Organism* Ant::move(vector<Organism*>& bug_list) {
   Organism* moved_ant = Organism::move(bug_list);    
   return moved_ant;
}

// move organism into an adjacent empty cell 
Organism* Organism::move(vector<Organism*>& bug_list) {
    vector<Cell*> adjacent_cells;
    look_around(bug_list, adjacent_cells);

     if(adjacent_cells.size() != 0) {
        Cell* move_to = adjacent_cells[rand_num(adjacent_cells.size())];       
        set_row_col(move_to->get_row(), move_to->get_col());                    
    } 
    
    adjacent_cells.clear();

    return this;   
} 

// return which cells the organism can move to 
void Organism::look_around(vector<Organism*>& bug_list, vector<Cell*>& adjacent_cells) {
    vector<Cell> potential_cells = get_nearby_cells(get_row(), get_col()); 
    
    for(int i = 0; i < potential_cells.size(); i++) {
        Cell cell = potential_cells[i];
        if(cell_on_board(cell.get_row(), cell.get_col())) {
        Organism* cell_contents = check_cell(cell.get_row(), cell.get_col(), bug_list);
        if(cell_contents == nullptr) 
           adjacent_cells.push_back(new Cell(cell.get_row(), cell.get_col()));
        }
    }
}

// return which cells have ants 
void Doodlebug::hunt(vector<Organism*>& bug_list, vector<Organism*>& potential_prey) {
    vector<Cell> potential_cells = get_nearby_cells(get_row(), get_col()); 
    
    for(int i = 0; i < potential_cells.size(); i++) {
        Cell cell = potential_cells[i];
        if(cell_on_board(cell.get_row(), cell.get_col())) {
        Organism* cell_contents = check_cell(cell.get_row(), cell.get_col(), bug_list);

        if(cell_contents != nullptr && cell_contents->get_type() == ANT_STR) 
           potential_prey.push_back(cell_contents);
        }
    }
}

// get the coordinates for cells above, below, left, and right of organism 
vector<Cell> get_nearby_cells(int x, int y) {
    return vector<Cell> {Cell(x + 1, y), Cell(x - 1, y), Cell(x, y + 1), Cell(x, y - 1)}; 
}

// check if cell contains an ant. if it does, push to vector 
void check_if_ant(int x, int y, vector<Organism*>& vec, vector<Organism*>& ants) {
    if(cell_on_board(x, y)) {
        Organism* cell_contents = check_cell(x, y, vec);
        if(cell_contents != nullptr && cell_contents->get_type() == ANT_STR) 
            ants.push_back(cell_contents);
    }
}

// given x, y coordinates, return a bug if it is in that cell
Organism* check_cell(int x, int y, vector<Organism*>& vec) {
    for(int k = 0; k < vec.size(); k++) {
        if(vec[k]->get_row() == x && vec[k]->get_col() == y) 
            return vec[k];
    }
    return nullptr;
}

// check if the proposed position is on the board before the bug moves 
bool cell_on_board(int row, int col) {
    return (row < BOARD && row >= 0 && col < BOARD && col >= 0);
}

// generate a random number between 0 and max - 1 
int rand_num(int max) {
    return rand() % max + 0;
}

// get a bug's index in the organism array 
int get_bug_index(vector<Organism*>& vec, Organism* bug) {
    for(int i = 0; i < vec.size(); i++) {
        if(bug->get_row() == vec[i]->get_row() && 
            bug->get_col() == vec[i]->get_col()) {
         return i; 
        }
    }
    
    return -1; 
}

// move all bugs exactly once to non-conflicting spots 
void next_turn(vector<Organism*>& vec, int size, string type) {
    if(size == 0) {
        return; 
    } else {
        Organism * bug = vec[size - 1];
        if(bug->get_type() == type && !bug->has_moved()) {
            Organism* moved_bug = bug->move(vec);
            bug->after_moving(vec);
        }
        
        next_turn(vec, size - 1, type);
    }
}

// print the game board each turn 
void generate_board(vector<Organism*>& vec, bool& playing) {
    int ants = 0, dbs = 0;
    for(int i = 0; i < BOARD; i++) {
        for(int j = 0; j < BOARD; j++) {
           Organism * cell_contents = check_cell(i, j, vec); 
            if(cell_contents != nullptr) {
                if(cell_contents->get_type() == ANT_STR) {
                    cout << "o"; ants++;
                } else {
                    cout << "X"; dbs++;
                }
                   
                cell_contents->set_moved(false); // get cell ready to move again  
            } else {
                cout << "-";
            }
        }
        cout << endl; 
    }

    if(ants == 0 || dbs == 0) 
        extinction(ants, dbs, playing);
}

void extinction(int ant_count, int db_count, bool& playing) {
    playing = false;

    cout << "\n\n\t----Extinction event!----" << endl; 
    if(!ant_count) {
        cout << "Ants "; 
    } else {
        cout << "Doodlebugs ";
    }
    cout << "are exinct. The game is over.";
}

// generate the initial coordinates for all bugs on the board 
void spawn_bugs(vector<Organism*>& bug_list){
    int bug_count = 0;
    int board[BOARD][BOARD] = {0}; 

    while(bug_count < (DB_COUNT + ANT_COUNT)) {
        int x = rand_num(BOARD);
        int y = rand_num(BOARD);

        if(board[x][y] == 0) {
            board[x][y]++;
            Organism* o_ptr;

            if(bug_count < DB_COUNT) {
                Doodlebug* d_ptr = new Doodlebug(x, y);
                o_ptr = d_ptr;
            } else {
                Ant* a_ptr = new Ant(x, y);
                o_ptr = a_ptr; 
            }

            bug_list.push_back(o_ptr);
            bug_count++;
            }
        }
}

Organism::Organism(): until_breed(-1) {}

Organism::Organism(int r, int c, string name) : coordinates(r, c), type(name), moved(false) {}

Doodlebug::Doodlebug(int r, int c): until_starve(3), Organism(r, c, DB_STR){ reset_breeding(8); }

Ant::Ant(int r, int c): Organism(r, c, ANT_STR){ reset_breeding(3); }

int Organism::get_row() { return coordinates.get_row(); }

int Organism::get_col(){ return coordinates.get_col(); }

void Organism::set_row_col(int x, int y) { coordinates.set_row_col(x, y); }

void Organism::reset_breeding(int x){ until_breed = x; }

void Organism::set_moved(bool bug_moved) { moved = bug_moved; }

