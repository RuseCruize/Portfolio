//overall implementation is designed for general case solutions
using namespace std;
#include <cstdlib>
#include <ctime>
#include <iostream>

enum TreasureItem{
		TREASURE_NONE = -1,
		TREASURE_GOLD_PILE = 0,
		TREASURE_RUSTY_SWORD,
		TREASURE_SHARP_SWORD,
		TREASURE_GODLY_SWORD,
		TREASURE_SMALL_SHIELD,
		TREASURE_HEATER_SHIELD,
		TREASURE_KITE_SHIELD,
		TREASURE_REGENERATION_RING,
		TREASURE_CURSED_RING,
		NUM_TREASURE_ITEMS
};

//this array is for converting integers into the equivalent items
char *Treasures[] = {
	"TREASURE_GOLD_PILE",
	"TREASURE_RUSTY_SWORD",
	"TREASURE_SHARP_SWORD",
	"TREASURE_GODLY_SWORD",
	"TREASURE_SMALL_SHIELD",
	"TREASURE_HEATER_SHIELD",
	"TREASURE_KITE_SHIELD",
	"TREASURE_REGENERATION_RING",
	"TREASURE_CURSED_RING"
};

void SpawnTreasureItem(TreasureItem eItem){

}


//RandFloat was implemented for testing purposes
float RandFloat(void){
	srand (static_cast <unsigned> (time(0)));
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

//The main data structure for holding drop tables. Stores drops in dynamically allocated 2 dimensional arrays
class dropTable{
	public:
	float **dropRates;
	int numberOfTables;

	//allows monsters to initialize with any sized dropped tables
	//for example, the skeleton drops 2 times, each with a different table. This constructor creates the specified amount of dropRates arrays
	dropTable(int numberOfDropTables){
		dropRates = new float* [numberOfDropTables];
		for(int i = 0; i < numberOfDropTables; i++){
			//adding an extra row to be used later
			dropRates[i] = new float[NUM_TREASURE_ITEMS + 1];
			for(int j = 0; j < NUM_TREASURE_ITEMS; j++){
				dropRates[i][j] = 0;
			}
		}
		numberOfTables = numberOfDropTables;
	}
	
	//remove memory leaks when the data structure is destroyed
	~dropTable(){
		for(int i = 0; i == numberOfTables - 1; i++){
			delete [] dropRates[i];
		}
		delete [] dropRates;
	}

	//allows 2 drop tables to be added together, such as with the dragon who shares drop tables with the skeleton
	void addTables(int column, dropTable &a, int dropTableColumn){
		for(int i = 0; i < NUM_TREASURE_ITEMS + 1; i++){
			dropRates[column][i] += a.dropRates[dropTableColumn][i];
		}		
	}	
};

//the function used for determining which items are dropped
//used pass by reference to avoid problems with pointers
void SpawnLoot(dropTable &killedMob){
	float rng;
	bool itemDropped = false;
	for(int j = 0; j < killedMob.numberOfTables; j++){	
		itemDropped = false;	
		rng = RandFloat();
		//after rolling a random number 1-0 it iterates through the first dropRate array, checking to see which item drops
		for(int i = 0; i < NUM_TREASURE_ITEMS + 1; i++){
			rng -= killedMob.dropRates[j][i];
			if(rng < 0 && !itemDropped){
				itemDropped = true;
				SpawnTreasureItem((TreasureItem) i);
				cout << Treasures[i] << endl;
			}
		//here is where the addittional row comes into play. when it equals 0 it is treated as an OR, if its a 1 it treats it as an AND
		//this allows for control over how many drops occur and allows for having multiple possible drop tables that only occur exclusively
		}if(itemDropped && killedMob.dropRates[j][NUM_TREASURE_ITEMS + 1] == 0){
			return;
		}
	}
	return;
}

int main(){
	//it seems best to declare drop tables like this, since it would always be manual
	dropTable goblin(1);
	dropTable skeleton(2);
	dropTable dragon(3);	
	goblin.dropRates[0][TREASURE_GOLD_PILE] = 0.2;
	goblin.dropRates[0][TREASURE_RUSTY_SWORD] = 0.5;
	goblin.dropRates[0][TREASURE_CURSED_RING] = 0.3;
	skeleton.dropRates[0][TREASURE_HEATER_SHIELD] = 0.1;
	skeleton.dropRates[0][TREASURE_KITE_SHIELD] = 0.9;
	skeleton.dropRates[1][TREASURE_REGENERATION_RING] = 0.05;
	skeleton.dropRates[1][TREASURE_CURSED_RING] = 0.1;
	skeleton.dropRates[0][NUM_TREASURE_ITEMS + 1] = 1;
	dragon.dropRates[0][TREASURE_GODLY_SWORD] = 0.5;
	dragon.dropRates[0][NUM_TREASURE_ITEMS + 1] = 0;
	dragon.addTables(1, skeleton, 0);
	dragon.addTables(2, skeleton, 1);
	dragon.dropRates[1][NUM_TREASURE_ITEMS + 1] = 1;
	//while a cout like this would not be used it is added for testing and demonstration purposes
	cout << "A Goblin died and dropped: ";
	SpawnLoot(goblin);
	cout << endl << "A Skeleton died and dropped: ";
	SpawnLoot(skeleton);	
	cout << endl << "A Dragon died and dropped: ";
	SpawnLoot(dragon);
	
	return 0;
}
