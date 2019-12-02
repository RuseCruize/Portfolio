#include "arraylist.h"

template <typename T>
ArrayList<T> ::~ArrayList(){
	delete[] m_data;	
}

template <typename T>
ArrayList<T>::ArrayList(int s, const T& x){
	m_size = s;
	m_max = s;
	m_data = new T[s];
	for(int i = 0; i < m_size; i++){
		m_data[i] = x;
	}
}

template <typename T>
ArrayList<T>&ArrayList<T>:: operator=(const ArrayList<T>& rhs){
	if(m_data){
		delete[] m_data;
	}
	m_data = new T [rhs.m_max];
	m_size = rhs.m_size;
	m_max = rhs.m_max;
	for(int i = 0; i < rhs.m_size; i++){
		m_data[i] = rhs.m_data[i];
	}

}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList<T>& cpy){
//	if(m_data){
//		delete[] m_data;
//	}	
	m_data = new T [cpy.m_max];
	m_size = cpy.m_size;
	m_max = cpy.m_max;
	for(int i = 0; i < cpy.m_size; i++){
		m_data[i] = cpy.m_data[i];
	}
}


template <typename T>
int ArrayList<T>::size() const{
	return m_size;
}

template <typename T>
const T& ArrayList<T>::first() const{
	return m_data[0];
}

template <typename T>
T& ArrayList<T>::operator[](int i){
	if(i <= m_size){
		return m_data[i];
	}
	else{
	    std::cout << "!-- ERROR : PANIC in ARRAYLIST!!" <<  "  (index out of bounds)" << std::endl;	
	}
}

template <typename T>
const T& ArrayList<T>::operator[](int i) const{
	return m_data[i];
}

template <typename T>
int ArrayList<T>::find(const T& x) const{
	for(int i = 0; i < m_size; i++){
		if(m_data[i] == x){
			return i;
		}
	}	
}


template <typename T>
void ArrayList<T>::grow(){ 
	//create new array of new size
	T* temp;
	m_max *= 2;		
	if(m_max == 0){
		m_max = 1;
	}	

	temp = new T [m_max];
	//copy elements from old array into new array
	for(int i = 0; i <  m_size; i++){
		temp[i] = m_data[i];
	}
	//delete old array
	if(m_data){
		delete[] m_data;
	}
//	m_data = new T[m_max];
//	for(int i = 0; i < m_size; i++){
//		m_data[i] = temp[i];
//	}	
	//point m_data to new array
	
	m_data = temp;
	temp = NULL;
}


template <typename T>
void ArrayList<T>::shrink(){
	//create new array of new size
	T* temp;		
	temp = new T [m_max / 2];
	//copy elements fromr equals old array into new array
	for(int i = 0; i < (m_max / 2); i++){
		temp[i] = m_data[i];
	}
	//delete old array
	delete []m_data;
	//point m_data to new array
	m_data = temp;
	m_max /= 2;	
//	delete temp;
}


template <typename T>
void ArrayList<T>::clear(){
	//delete m_data;
	m_size = 0;
	m_max = 0;
	if(m_data){
		delete m_data;
	}
	m_data = NULL;
}

template <typename T>
void ArrayList<T>::insert(const T& x, int i){
    	if(m_max == m_size){
		grow();
	}	
	
	T next;
	
	for(int j = 0; j < m_size - i; j++){
		//next = m_data[m_size + 1 - j];
		m_data[m_size - j] = m_data[m_size - j - 1];
	}
	m_size++;
	m_data[i] = x;
}

template <typename T>
void ArrayList<T>::insert_back(const T& x){
    if(m_size ==  m_max){
		(*this).grow();
	}
	m_size++;	
	m_data[m_size - 1] = x;

}

template<typename T>
void ArrayList<T>::remove(int i){
	for(int j = i; j < m_size; j++){
		m_data[j] = m_data[j + 1];
	}
//	m_data[m_size] = NULL;
	m_size--;
}

template <typename T>
void ArrayList <T>::swap(int i, int k){
	T temp;
	temp = m_data[i];
	m_data[i] = m_data[k];
	m_data[k] = temp;	
}

template <typename T>
void ArrayList<T>::append(const ArrayList<T>& alist){
	while((alist.m_size + m_size) > m_max)
	{
		(*this).grow();	
	}
	
	for(int i = 0; i < alist.m_size; i++){
		m_data[m_size + 1] = alist.m_data[i];
		m_size++;	
	}	
}


template <typename T>
void ArrayList<T>::reverse(){
	T* temp;
	temp = new T [m_max];	
	for(int i = 0; i  < m_size; i++){
		temp[i] = m_data[m_size - i]; 
	}
	for(int i = 0; i < m_size; i++){
		m_data[i] = temp[i];
	}	
	delete temp;
}




