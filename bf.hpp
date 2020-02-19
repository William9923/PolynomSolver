#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include "polinom.hpp"

using namespace std;

#ifndef _BF_HPP_
#define _BF_HPP_

Polinom multiply_brute(Polinom p1, Polinom p2);
int count_multiply_operation(Polinom p1, Polinom p2);
int count_addition_operation(Polinom p1, Polinom p2);


/* Implementasi Algoritma Brute Force pada perkalian polinomial */
Polinom multiply_brute(Polinom p1, Polinom p2){
	Polinom p3(p1.getDerajat() * 2);
	for(int i = 0; i < p1.panjangPolinom(); i++){
		for (int j = 0; j < p2.panjangPolinom(); j++){
			p3.setKoefAt(i+j, p3.getKoefAt(i+j) + (p1.getKoefAt(i) * p2.getKoefAt(j)));
		}
	}
	return p3;
}

/* Fungsi untuk menghitung jumlah Operasi perkalian pada strategi brute force */
int count_multiply_operation(Polinom p1, Polinom p2){
	return (p1.getDerajat()+1) * (p2.getDerajat()+1);
}

/* Fungsi untuk menghitung jumlah operasi penjumlahan pada strategi brute force */
int count_addition_operation(Polinom p1, Polinom p2) {
	return count_multiply_operation(p1,p2) -1;
}

#endif
