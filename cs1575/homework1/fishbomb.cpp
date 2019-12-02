//Ethan Huneke
//Section A
using namespace std;
#include <iostream>

int **create_array(int column, int row){
    int **p;
    p = new int* [column];

    for(int i = 0; i < column; i++){
        p[i] = new int[row];
    }

    return p;
}

int **fill_array(int row, int column, int **array){
    for (int i = 0; i < row; i++){
	for(int j = 0; j < column; j++){
	    cin >> array[i][j];
	}
    }
    return array;
}

int check_fish(int column, int row, int **array){
    int total = 0;
    for(int i = 0; i < 5; i++){
	for(int j = 0; j < 5; j++){
	    total += array[row - 2 + i][column - 2 + j];
	    array[row - 2 + i][column - 2 + j] = 0;
	}
    } 
    return total;
}


int main(){
    int row;
    int column;
    int numberOfArrays;
    int x;
    int y;
    int **array;
    int sum;
    
    cin >> numberOfArrays;
    for(int i = 0; i < numberOfArrays; i ++){
	sum = 0;
	cin >> row;
	cin >> column;
//	array = new int*[column];
	array = create_array(column, row);
	array = fill_array(row, column, array);
	for(int k = 0; k < 3; k++){
	    cin >> y;
	    cin >> x;
	    for(int i = 0; i < 5; i++){
		for(int j = 0; j < 5; j++){
		    sum += array[y + i - 2][x + j - 2];
		    array[y + i - 2][x + j - 2] = 0;
		}
	    }
	    
    }	
	cout << "#" << i << ": Bender catches " << sum << " fish." << endl;
	for(int l = 0; l < row; l++){    
	    cout << ";lasdhjflk jasdlkf j;alskdjf poiajsdf;lk jmas;lkjf poaisjf ;oeaj" << endl;
	    delete[] array[l];
	}

	delete [] array;
	//array = NULL;
    }
}
