#include "bf.hpp"
#include "polinom.hpp"
#include "dac.hpp"
#include <time.h>

using namespace std;

/* Start Up logo & procedure */
void start() {
	for (int i = 0; i < 34; i++){
		cout << "═";
	}
	cout << "WELCOME" ;
	for (int i = 0; i < 34; i++){
		cout << "═";
	}
	cout << endl;
	cout << "╔" << "════════════════════════════════════" << "╗" << endl;
	cout << "║" << "	               __            " << "║" << endl;
	cout << "║" << "\\    /o||o _.._ _/ _ (_  _ |   _ ._ " << "║" << endl;
	cout << "║" << " \\/\\/ ||||(_|| | |_> __)(_)|\\/(/_|  " << "║" << endl;
	cout << "╚" << "════════════════════════════════════" << "╝" << endl;

}

/* Function to output the polynomial results */
void printResult(string algo, Polinom p) {
	cout << "=============================" << endl;
	cout << "Hasil Perkalian Polinomial dengan strategi " << algo << " adalah: " << endl;
	p.show();
	cout << endl;
}

/* END PROGRAM Procedure */
void end(){
	for (int i = 0; i < 36; i++){
		cout << "═";
	}
	cout << "END" ;
	for (int i = 0; i < 36; i++){
		cout << "═";
	}
	cout << endl;
}

/* Procedure to output time taken for certain process */
void printTimeTaken(string algo, double time){
	cout << "Waktu yang dibutuhkan untuk algoritma " << algo << " adalah : " << time << " mikro detik" << endl;
}

/* Procedure to output number of certain operation */
void printOperasi(int tambah, int kali){
	cout << "Jumlah operasi perkalian : " << kali << endl;
	cout << "Jumlah operasi penjumlahan : " << tambah << endl; 
}

int main(){
	clock_t t1;
	clock_t t2;
	double time_taken;
	
	/* Mulai Program */
	start();
	
	int n;
	cout << "Please Enter A Number : ";
	cin >> n;

	Polinom p1(n);
	Polinom p2(n);

	/* Generate Random Number */
	srand(time(NULL));
	p1.generateRandom(rand() * 100);
	p2.generateRandom(rand() * 200);

	/* Pencetakan Informasi */
	cout << "Nilai Polinom: " << endl;
	cout << "P1 : "; p1.show();
	cout << "P2 : "; p2.show();

	/* Divide and Conquer Polynom Multiplication Implementation */
	int plus = 0; int mult = 0;
	t1= clock();
	Polinom p3(multiply_div(p1,p2,&plus, &mult));
	t1 = clock() - t1;
	time_taken = ((double)t1)/CLOCKS_PER_SEC * 1000000;
	printResult("Divide and Conquer",p3);
	printOperasi(plus,mult);
	printTimeTaken("Divide and Conquer",time_taken);

	/* Brute Force Polynom Multiplication Implementation */
	t2=clock();
	Polinom p4(multiply_brute(p1,p2));
	t2 = clock() - t2;
	time_taken=(((double)t2)/CLOCKS_PER_SEC) * 1000000;
	printResult("Brute Force", p4);
	printOperasi(count_addition_operation(p1,p2),count_multiply_operation(p1,p2));
	printTimeTaken("Brute Force", time_taken);

	/* Akhir Program */
	end();
	return 0;
}