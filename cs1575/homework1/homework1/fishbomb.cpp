//Ethan Huneke
//Section A
using namespace std;
#include <iostream>

int main() {
    int row;
    int column;
    int numberOfArrays;
    int x;
    int y;
    int **grid;
    int sum;

    cin >> numberOfArrays;
    for (int i = 0; i < numberOfArrays; i++) {
        sum = 0;
        cin >> row;
        cin >> column;
        grid = new int *[row];
        for (int i = 0; i < row; i++)
          grid[i] = new int[column]; // aka columns
        // Get grid input
        for (int i = 0; i < row; i++)
          for (int j = 0; j < column; j++)
            cin >> grid[i][j];
        for (int k = 0; k < 3; k++) {
            cin >> y;
            cin >> x;
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    sum += grid[y + i - 2][x + j - 2];
                    grid[y + i - 2][x + j - 2] = 0;
                }
            }
        }
        cout << "#" << i << ": Bender catches " << sum << " fish." << endl;
        
        for (int i = 0; i < row; i++)
            delete[] grid[i];
        
        delete[] grid;
        grid = NULL;
    }
}
