#include "Vector.h"
#include <cmath>
#include <complex>
#include <cassert>
#include <iostream>

void testVector() {
	int initArray1[5] = { 1,2,3,4,5 };
	int initArray2[5] = { 0,2,-3,4,-6 };
	
	Vector<int> v1(initArray1, 5);
	Vector<int> v2(initArray2, 5);


	int scalarMult12 = 0;
	for (int i = 0; i < 5; ++i)
		scalarMult12 += initArray1[i] * initArray2[i];
	int sum12Array[5];
	for (int i = 0; i < 5; ++i)
		sum12Array[i] = initArray1[i] + initArray2[i];
	int dif12Array[5];
	for (int i = 0; i < 5; ++i)
		dif12Array[i] = initArray1[i] - initArray2[i];


	assert((v1 + v2) == (Vector<int>(sum12Array, 5)));
	assert((v1 - v2) == (Vector<int>(dif12Array, 5)));
	assert(v1.scalarMult(v2) == scalarMult12);
	assert(v2.scalarMult(v1) == scalarMult12);

	Vector<int> v5 = v1;
	assert(v5 == Vector<int>(initArray1, 5));

	assert(v1.getSize() == 5);
	assert(v1.get(0) == 1);
	assert(v1.get(1) == 2);
	assert(v1.get(4) == 5);

	v1.set(0, 2);
	v1.set(1, 3);
	v1.set(4, 10);

	assert(v1.get(0) == 2);
	assert(v1.get(1) == 3);
	assert(v1.get(4) == 10);	
	assert(v1.getNorm() == sqrt(4 + 9 + 9 + 16 + 100));

	int number = 15;
	int multipliedArray2[5];
	for (int i = 0; i < 5; ++i)
		multipliedArray2[i] = number * initArray2[i];
	

	std::complex<int> initArray3[3];
	initArray3[0] = std::complex<int>(1, 1);
	initArray3[1] = std::complex<int>(2, 2);
	initArray3[2] = std::complex<int>(3, 3);
	std::complex<int> initArray4[3];
	initArray4[0] = std::complex<int>(-1,-1);
	initArray4[1] = std::complex<int>(2, 2);
	initArray4[2] = std::complex<int>(-3, -3);
	

	Vector<std::complex<int>> v3(initArray3, 3);
	Vector<std::complex<int>> v4(initArray4, 3);

	std::complex<int> scalarMult34(0,0);
	for (int i = 0; i < 3; ++i)
		scalarMult34 += initArray3[i] * std::conj(initArray4[i]);
	std::complex<int> sum34Array[3];
	for (int i = 0; i < 3 ; ++i)
		sum34Array[i] = initArray3[i] + initArray4[i];
	std::complex<int> dif34Array[3];
	for (int i = 0; i < 3; ++i)
		dif34Array[i] = initArray3[i] - initArray4[i];

	assert((v3 + v4) == (Vector<std::complex<int>>(sum34Array, 3)));
	assert((v3 - v4) == (Vector<std::complex<int>>(dif34Array, 3)));
	assert(v3.scalarMult(v4) == scalarMult34);
	assert(v4.scalarMult(v3) == scalarMult34);

	double initArray5[5] = { 1.1,2.2,3.3,4.4,5.5 };
	double initArray6[5] = { -2.2,3.3,-4.4,15.3,-6 };
	
	Vector<double> v_5(initArray5, 5);
	Vector<double> v_6(initArray6, 5);

	double scalarMult56 = 0.0;

	for (int i = 0; i < 5; ++i)
		scalarMult56 += initArray5[i] * initArray6[i];
	double sum56Array[5];
	for (int i = 0; i < 5; ++i)
		sum56Array[i] = initArray5[i] + initArray6[i];
	double dif56Array[5];
	for (int i = 0; i < 5; ++i)
		dif56Array[i] = initArray5[i] - initArray6[i];

	assert((v_5 + v_6) == (Vector<double>(sum56Array, 5)));
	assert((v_5 - v_6) == (Vector<double>(dif56Array, 5)));
	assert(v_5.scalarMult(v_6) == scalarMult56);
	assert(v_6.scalarMult(v_5) == scalarMult56);


	double num = 15.5;
	double multipliedArray3[5];
	for (int i = 0; i < 5; ++i)
		multipliedArray3[i] = number * initArray5[i];

	assert(v_5 * number == (Vector<double>(multipliedArray3, 5)));
	assert(v_5.getSize() == 5);
	assert(v_5.get(0) == 1.1);
	assert(v_5.get(1) == 2.2);
	assert(v_5.get(4) == 5.5);

	v_5.set(0, 2.2);
	v_5.set(1, 3.3);
	v_5.set(4, 10.1);


	assert(v_5.get(0) == 2.2);
	assert(v_5.get(1) == 3.3);
	assert(v_5.get(4) == 10.1);

}

int main() {
	testVector();
}

