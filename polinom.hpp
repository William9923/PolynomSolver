#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

#ifndef _POLINOM_HPP_
#define _POLINOM_HPP_

class Polinom {
public:
    Polinom(int);
    Polinom(const Polinom&);
    ~Polinom();
    void generateRandom(int);
    int panjangPolinom() const;
    int getKoefAt(int) const;
    void setKoefAt(int,int);
    int getDerajat() const;
    void setDerajat(int);
    void show();
    void resetPolinom();
protected:
	int n;
	int * koef;
};

Polinom::Polinom(int n) {
	this->n = n;
	this->koef = new int[n+1];

	for(int i = 0; i < n+1;i++){
		this->koef[i] = 0;
	}
}

Polinom::Polinom(const Polinom& p){
	this->n = p.n;
	this->koef = new int[p.n+1];

	for(int i = 0; i < p.n+1;i++){
		this->koef[i] = p.koef[i];
	}
}

Polinom::~Polinom(){
	delete[] this->koef;
}

void Polinom::generateRandom(int n){
	srand(n);
	int i = 0;
	int koefisien;
	while(i < this->n + 1){
		koefisien = (rand() % 100) + 1;
		if ((rand() % 10) < 5){
			koefisien *= -1;
		}
		this->koef[i] = koefisien;
		i++;
	}
}

int Polinom::panjangPolinom() const{
	return this->n+1;
}

int Polinom::getKoefAt(int index) const {
	return this->koef[index];
}

void Polinom::setKoefAt(int index, int val) {
	this->koef[index] = val;
}

int Polinom::getDerajat() const {
	return this->n;
}

void Polinom::setDerajat(int d) {
	this->n = d;
}

void Polinom::show(){
	for(int i=0; i < this->panjangPolinom(); i++){
		if (i == 0) {cout << this->koef[i];}
		else if (this->koef[i] > 0) {
			if (i==1){
				cout << "+" << this->koef[i] << "x";
			} else {
				cout << "+" << this->koef[i] << "x^" << i;
			}
		} else if (this->koef[i] < 0){
			if (i==1) {cout << this->koef[i] << "x";}
			else {
				cout << this->koef[i] << "x^" << i;
 			}
		}
	}
	cout << endl;
}

void Polinom::resetPolinom(){
	int i = 0;
	while(i < this->n + 1){
		this->koef[i] = 0;
		i++;
	}
}

#endif
