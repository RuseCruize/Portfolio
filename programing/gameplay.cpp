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

float RandFloat(void){
	srand (static_cast <unsigned> (time(0)));
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

class dropTable{
	public:
	//make an array with elements equal to drop table and then record drop rates
	//float dropRates [NUM_TREASURE_ITEMS] = {0};	
	float **dropRates;
	int numberOfTables;

	//allows monsters to initialize with any sized dropped tables
	dropTable(int numberOfDropTables){
		dropRates = new float* [numberOfDropTables];
		for(int i = 0; i < numberOfDropTables; i++){
			dropRates[i] = new float[NUM_TREASURE_ITEMS + 1];
			for(int j = 0; j < NUM_TREASURE_ITEMS; j++){
				dropRates[i][j] = 0;
			}
		}
		numberOfTables = numberOfDropTables;
	}
	
	//remove memory leaks when the data structure is destroyed
	~dropTable(){
		delete [] dropRates;
	}

	//allows 2 drop tables to be added together as well as an additional argument for the percntage of the added table
	//i.e. a Godly Sword (50%) OR whatever a Skeleton would normally drop (50%)
	void addTables(int column, dropTable a, int dropTableColumn){
		for(int i = 0; i < NUM_TREASURE_ITEMS + 1; i++){
			dropRates[column][i] += a.dropRates[dropTableColumn][i];
		}		
	}	
};

void SpawnLoot(dropTable killedMob){
	//needs to know all possible drops and percents
	float rng;
	bool itemDropped = false;
	for(int j = 0; j < killedMob.numberOfTables; j++){	
		itemDropped = false;	
		rng = RandFloat();
		for(int i = 0; i < NUM_TREASURE_ITEMS + 1; i++){
			rng -= killedMob.dropRates[j][i];
			if(rng < 0 && !itemDropped){
				itemDropped = true;
				SpawnTreasureItem((TreasureItem) i);
				cout << i << endl;
			}
		}if(itemDropped && killedMob.dropRates[j][NUM_TREASURE_ITEMS + 1] == 0){
			return;
		}
	}
	return;
}

int main(){
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
	SpawnLoot(dragon);
	
	return 0;
}
