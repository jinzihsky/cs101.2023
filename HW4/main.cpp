#include <iostream>
#include <string>

using namespace std;

class TicTacToc{
    public:
        void run(){
            cout << "--- Tic Tac Toe --- CSIECGU\n";
            cout << "Player 1 (X) - Player 2 (O)" << endl;
        }
};

int main(){
    TicTacToc game;
    game.run();
    return 0;
}
