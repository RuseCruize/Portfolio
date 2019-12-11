#include <iostream>
#include <map> 
#include <fstream> 
#include <string> 

using namespace std;

template <class KTy, class Ty>
void PrintMap(map<KTy, Ty> map){
    typename std::map<KTy, Ty>::iterator iterator;
    for (iterator = map.begin(); iterator != map.end(); iterator++)
        cout << iterator->first << "-> " << iterator->second << endl;
}

int main(){
    
    static const char* fileName = "/usr/local/home/ehgdd/SDRIVE/cs1585/proj2/4507.txt.utf-8";

    map<string, unsigned int> wordsCount;{
        ifstream fileStream(fileName);
        if (fileStream.is_open())
            while (fileStream.good()){
                string word;
                fileStream >> word;

                if (wordsCount.find(word) == wordsCount.end()) 
                    wordsCount[word] = 1; 
                else{
                    wordsCount[word]++; 
         	} 
	}
        else{
            cerr << "Could not open file." << endl;
            return EXIT_FAILURE;
        }
        
	PrintMap(wordsCount);
    }

    return EXIT_SUCCESS;
}
