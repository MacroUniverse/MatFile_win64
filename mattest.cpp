#include <iostream>
#include "mat.h"

#define BUFSIZE 256
using namespace std;

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
}