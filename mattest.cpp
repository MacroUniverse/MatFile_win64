#include <iostream>
#include "mat.h"
#include "nr3.h"
#include "nr3plus.h"
#include "matsave.h"

using namespace std;

int main() {

	MATFile *pfile = matOpen("nrMat.mat", "w");
	Complex I(0, 1);

	// scalars
	Doub s(3.1415926535897932384626);
	matsave(s, "s", pfile);
	Complex sc(3.1, 3.2);
	matsave(sc, "sc", pfile);

	// vectors
	VecDoub v(3);
	v[0] = 1.; v[1] = 2.; v[2] = 3.;
	matsave(v, "v", pfile);
	VecComplex vc(3);
	for (Int i = 0; i < 3; ++i)
		vc[i] = 1 + (Doub)i + I * (Doub)i;
	matsave(vc, "vc", pfile);

	// matrices
	MatDoub A;
	A.assign(2, 3, 0.);
	A[0][0] = 1.; A[0][1] = 3.; A[0][2] = 5.; A[1][2] = 11;
	matsave(A, "A", pfile);
	
	MatComplex C(3, 3);
	Complex *pC{ &C[0][0] };
	for (Int i = 0; i < 9; ++i) {
		pC[i] = 1 + (Doub)i + I * (Doub)i;
	}
	matsave(C, "C", pfile);

	matClose(pfile);

	// read test

	// scalars
	pfile = matOpen("nrMat.mat", "r");
	s = 0.;
	matload(s, "s", pfile);
	cout.precision(16);
	cout << s << endl;

	sc = 0.;
	matload(sc, "sc", pfile);
	cout << sc << endl;

	// vectors
	v.resize(0);
	matload(v, "v", pfile);
	disp(v, 16);

	vc.resize(0);
	matload(vc, "vc", pfile);
	disp(vc, 16);

	// matrices
	A.resize(0, 0);
	matload(A, "A", pfile);
	disp(A, 16);

	C.resize(0, 0);
	matload(C, "C", pfile);
	disp(C, 16);

	matClose(pfile);
}

