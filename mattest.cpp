#include <iostream>
#include "mat.h"
#include "nr3.h"

using namespace std;

mxArray * writemat(MatDoub_I &a)
{
	int i, j, m, n;
	mxArray *pa;
	m = a.nrows(); n = a.ncols();
	pa = mxCreateDoubleMatrix(m, n, mxREAL);
	auto ppa = mxGetPr(pa);
	for (i = 0; i < m; ++i) {
		for (j = 0; j < n; ++j) {
			ppa[m*j + i] = a[i][j];
		}
	}
	return pa;
}

int main() {
	MATFile *pmat;
	mxArray *pa1, *pa3;

	double data[9] = { 1.0, 4.0, 7.0, 2.0, 5.0, 8.0, 3.0, 6.0, 9.0 };
	const char *file = "mattest.mat";

	pmat = matOpen(file, "w");

	pa1 = mxCreateDoubleMatrix(3, 3, mxREAL);
	memcpy((void *)(mxGetPr(pa1)), (void *)data, sizeof(data));
	
	pa3 = mxCreateString("MATLAB: the language of technical computing");

	matPutVariable(pmat, "A", pa1);
	matPutVariable(pmat, "str", pa3);

	/* clean up */
	mxDestroyArray(pa1);
	mxDestroyArray(pa3);

	matClose(pmat);

	// use with NR3 matrices
	MatDoub a;
	mxArray *pa;
	a.assign(2, 3, 0.);
	a[0][0] = 1.; a[0][1] = 2.; a[0][2] = 3.; a[1][2] = 6;
	a.print();
	MATFile *pfile;
	pfile = matOpen("nrMat.mat", "w");
	pa = writemat(a);
	matPutVariable(pfile, "a", pa);
	matClose(pfile);
}

