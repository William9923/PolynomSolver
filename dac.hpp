#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include "polinom.hpp"
#include "bf.hpp"

using namespace std;

#ifndef _DAC_HPP_
#define _DAC_HPP_

vector<int> getDerajatPartition(Polinom p);
vector<Polinom> getPartition(Polinom p);
int getPembagiDerajat(Polinom p);
Polinom naikDerajat(Polinom p, int n);
Polinom addPolinom(Polinom p1, Polinom p2);
Polinom subtractPolinom(Polinom p1, Polinom p2);
Polinom multiply_div(Polinom p1, Polinom p2,int * count1, int * count2);

/* Fungsi untuk menemukan letak derajat pembagi polinom menjadi 2 bagian polinom 
   A(x) = Ao(x) + A1(x)
   , menemukan derajat pembagi antara A0(x) dan A1(x)
*/
vector<int> getDerajatPartition(Polinom p){
	int derajat = p.getDerajat();
	vector<int> derajatVec = {};
	derajatVec.push_back((derajat / 2) - 1); 
	derajatVec.push_back(derajat - (derajat / 2)); 

	return derajatVec;
}

/*	Fungsi untuk membagi suatu polinom menjadi 2 bagian
	Contoh :
	A(x) => Ao(x) dan A1(x)
*/
vector<Polinom> getPartition(Polinom p){
	vector<int> partition = getDerajatPartition(p);
	int left = partition[0];
	int right = partition[1];

	Polinom p1(left);
	Polinom p2(right);

	for (int i = 0; i < p.panjangPolinom(); i++){
		if (i <= left){
			p1.setKoefAt(i, p.getKoefAt(i));
		}
		else {
			if ((p.panjangPolinom() % 2) != 0) {
				p2.setKoefAt(i-right, p.getKoefAt(i));
			} else {
				p2.setKoefAt(i-right+1, p.getKoefAt(i));
			}
		}
	}
	vector<Polinom> returnee = {};
	returnee.push_back(p1);
	returnee.push_back(p2);

	return returnee;
}


int getPembagiDerajat(Polinom p){
	return p.getDerajat() / 2;
}

/* Fungsi untuk mengalikan suatu polinom dengan nilai x tertentu 
   naikDerajat(p,2) => p * x^2
*/
Polinom naikDerajat(Polinom p, int n){
	Polinom p_after(p.getDerajat() + n);
	for (int i = 0; i < p.panjangPolinom(); i++){
		p_after.setKoefAt(i+n, p.getKoefAt(i));
	}
	return p_after;
}

/* Fungsi untuk melakukan penjumlahan polinom */
Polinom addPolinom(Polinom p1, Polinom p2){
	int maxDerajat = (p1.getDerajat() >= p2.getDerajat()) ? p1.getDerajat() : p2.getDerajat();
	Polinom p3(maxDerajat);

	int count = 0;
	while(count < p1.panjangPolinom() and count < p2.panjangPolinom()) {
		p3.setKoefAt(count, p1.getKoefAt(count) + p2.getKoefAt(count));
		count++;
	}

	while (count < p1.panjangPolinom()){
		p3.setKoefAt(count, p1.getKoefAt(count));
		count++;
	}

	while(count < p2.panjangPolinom()){
		p3.setKoefAt(count, p2.getKoefAt(count));
		count++;
	}
	return p3;
}

/* Fungsi untuk melakukan pengurangan polinom */
Polinom subtractPolinom(Polinom p1, Polinom p2){
	int maxDerajat = (p1.getDerajat() >= p2.getDerajat()) ? p1.getDerajat() : p2.getDerajat();
	Polinom p3(maxDerajat);

	int count = 0;
	while(count < p1.panjangPolinom() and count < p2.panjangPolinom()) {
		p3.setKoefAt(count, p1.getKoefAt(count) - p2.getKoefAt(count));
		count++;
	}

	while (count < p1.panjangPolinom()){
		p3.setKoefAt(count, p1.getKoefAt(count));
		count++;
	}

	while(count < p2.panjangPolinom()){
		p3.setKoefAt(count, p2.getKoefAt(count) * -1);
		count++;
	}

	return p3;
}

/* Fungsi untuk melakukan perkalian antar polinom dengan menggunakan algoritma divide and conquer 
   Notes : Prekondisi -> kedua polinom memiliki tingkat derajat yang sama.
*/
Polinom multiply_div(Polinom p1, Polinom p2, int * count1, int * count2){
	if (p1.getDerajat() < 2){
		(*count1) += count_addition_operation(p1,p2);
		(*count2) += count_multiply_operation(p1,p2);
		return multiply_brute(p1,p2);
	}

	int n = getPembagiDerajat(p1);
	
	vector<Polinom> partitions = getPartition(p1);
	Polinom a0(partitions[0]);
	Polinom a1(partitions[1]);

	vector<Polinom> partitions2 = getPartition(p2);
	Polinom b0(partitions2[0]);
	Polinom b1(partitions2[1]);

	Polinom x1(addPolinom(a0,a1)); 
	Polinom x2(addPolinom(b0,b1));
	(*count1) +=2;

	Polinom y(multiply_div(x1,x2,count1,count2));
	(*count2)++;

	Polinom z(multiply_div(a1,b1,count1,count2));
	(*count2)++;

	Polinom u(multiply_div(a0,b0,count1,count2));
	(*count2)++;

	Polinom mid(subtractPolinom(subtractPolinom(y,u),z));
	(*count1)+=2;

	Polinom mid2(naikDerajat(mid,n));

	Polinom z2(naikDerajat(z,n*2));
	(*count1)+=2;

	return addPolinom(addPolinom(u,mid2),z2);
}

#endif

