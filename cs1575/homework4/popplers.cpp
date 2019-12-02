//Ethan Huneke
//Section A
#include "abstractqueue.h"
#include "randomengine.h"
#include <iostream>

using namespace std;

class customer{
	public:
		string name;
		int popplers;
		int totalEaten;
		customer(string who, int number){
			name = who;
			popplers = number;
		}		
		customer(){};

		
		void set_string(string s){
//			name = s;
		}

};

class queue : public AbstractQueue<customer>{
	public:	
		int size;
		customer* customers;

		bool isEmpty() const{
			if(size == 0){
				return true;
			}else{
				return false;
			}
		};
		
		const customer& front() const throw (Oops){
			return customers[0];
		}

		
		const customer& back() const throw (Oops){
			return customers[size];
		}


		void enqueue(const customer& x){
		//	customer* 1
		//	temp = new customer;
			customers[size + 1].name = x.name;
			customers[size + 1].popplers = x.popplers;
			customers[size + 1].totalEaten = x.totalEaten;
			size++;
			dequeue();			
		}


		void dequeue(){
			for(int i = 0; i <= size - 1; i++){
				customers[i] = customers[i + 1];
			}
//			delete &customers[size - 1];
			size--;
		}		


		void clear(){
			for(int i = 0; i < size - 1; i++){
				delete &customers[i];
			}
			size = 0;
		}

		~queue(){
			clear();

		}


		queue(int s){
			size = s - 1;
			customers = new customer[s];
		//	customers = new customer[s];
			for(int i = 0; i < size; i++){
			//	customers[i] = new customer;
			//	customers[i]->name = "                ";
			//	customers[i]->popplers = 0;
			}
		}
		

};

int main(){
	int size;
	cin >> size;	
	string name;
	int popplers;	
	queue customers(size + 1);
	customer* temp;
	randomEngine engine;
	int remaining;
	int eaten;
	int iterations;
	string  mostName;
	int mostAmount;
	string leastName;
	int leastAmount;
	int popplerTotal;
	
	for(int i = 0; i < size;  i++){
//		customers.customers[i] = new customer;
		cin >> name;
		customers.customers[i].name = name;
		cin >> popplers;
		customers.customers[i].popplers = popplers;
//		temp = new customer temper(name, popplers);
	}

	while(customers.size){
		//cout<<customers.customers[i].name +  " eats " + customers.customers[i].popplers + customers.customers[i].name<<endl; 
		if(customers.customers[0].name != ""){

		eaten = 0;
		cout << customers.customers[0].name;
		cout << " eats ";
	
		iterations = customers.customers[0].popplers/5;

		if((customers.customers[0].popplers%5) != 0){
			iterations++;
		}

		iterations *= 5;
		cout << iterations;
		cout << " popplers. ";
		cout << customers.customers[0].name;
//		cout << iterations;
		for(int i = 0; i < iterations; i++){	
			remaining = engine.rollD(6);
		//	cout << "iterating"<<endl;
			customers.customers[0].totalEaten++;
			if(remaining == 6){
				eaten++;
			}
		}

		if(eaten == 0){
			cout << " is satisfied after eating ";
			cout << customers.customers[0].totalEaten;
			cout << " popplers. " << endl;
			popplerTotal += customers.customers[0].totalEaten;
			if(customers.customers[0].totalEaten > mostAmount){
				mostAmount = customers.customers[0].totalEaten;
				mostName = customers.customers[0].name;
			}		
			if(customers.customers[0].totalEaten < leastAmount){
				leastAmount = customers.customers[0].totalEaten;
				leastName = customers.customers[0].name;
			}
			customers.dequeue();
		}

		if(eaten != 0){
			cout << " wants ";
			cout << eaten;
			cout << " more popplers" << endl;
			customers.customers[0].popplers = eaten;
			customers.enqueue(customers.customers[0]);
		}	
		}else{
			customers.enqueue(customers.customers[0]);
		}
	}
	popplerTotal -= 1;
	cout << endl << endl << "A total of " << popplerTotal << " popplers were eaten." << endl;
	cout << mostName << " ate the most popplers: " << mostAmount << endl;
	cout << leastName<< " ate the fewer popplers: " << leastAmount << endl;
	customers.clear();
}
