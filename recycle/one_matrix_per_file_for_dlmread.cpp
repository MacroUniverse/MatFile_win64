// ==========   Deprecated! Text Mode  ==================
// save data to text file, can be very slow for large matrices to be read.
// file name will be modified to obey matlab rules, extension will be ".m"
// all functions in binary mode is compatible in text mode and vise versa.
//
// ===========  Deprecated! Text Mode extra functions ==============
// in text mode, there are extra functions "void matsave(*, fname, ...)" to increase
//		reading speed for large matrices, basically these functions write a single
//		matrix/vector in each file, only separated by space and return.
// use "dlmread()" in matlab to read these files.
// for 3d matrices, the data format [A(:,:,1);A(:,:,2);...]

// declaration
void matsave(VecInt_I &v, const std::string &fname);

void matsave(VecDoub_I &v, const std::string &fname);

void matsave(VecComplex_I &v, const std::string &fname);

void matsave(MatDoub_I &a, const std::string &fname, const Int step1 = 1, const Int step2 = 1);

void matsave(MatComplex_I &a, const std::string &fname, const Int step1 = 1, const Int step2 = 1);

void matsave(Mat3DDoub_I &a, const std::string &fname, const Int step1 = 1, const Int step2 = 1, const Int step3 = 1);

void matsave(Mat3DDoub_I &a, const std::string &fname, const Char xyz, const VecInt_I &slice,
	const Int step1 = 1, const Int step2 = 1);

void matsave(Mat3DComplex_I &a, const std::string &fname, const Int step1 = 1, const Int step2 = 1, const Int step3 = 1);

void matsave(Mat3DComplex_I &a, const std::string &fname, const Char xyz, const VecInt_I &slice,
	const Int step1 = 1, const Int step2 = 1);

// implementation

// save large vector/matrix, fast reading
// use "dlmread()" function to load in matlab

void matsave(VecInt_I &v, const std::string &fname)
{
	Int i, N = v.size();
	ofstream fout(fname);
	for (i = 0; i < N; ++i) {
		fout << v[i] << ' ';
	}
	fout.close();
}

void matsave(VecDoub_I &v, const std::string &fname)
{
	Int i, N = v.size();
	ofstream fout(fname);
	for (i = 0; i < N; ++i) {
		fout << v[i] << ' ';
	}
	fout.close();
}

void matsave(VecComplex_I &v, const std::string &fname)
{
	Int i, N = v.size();
	Doub cr, ci;
	ofstream fout(fname);
	for (i = 0; i < N; ++i) {
		cr = real(v[i]); ci = imag(v[i]);
		if (ci == 0)
			fout << cr << ' ';
		else
			fout << cr << '+' << ci << "i ";
	}
	fout.close();
}

void matsave(MatDoub_I &a, const std::string &fname, const Int step1, const Int step2)
{
	Int i, j, m = (a.nrows()+step1-1)/step1, n = (a.ncols()+step2-1)/step2;
	ofstream fout(fname);
	for (i = 0; i < m; ++i) {
		for (j = 0; j < n; ++j)
			fout << a[step1*i][step2*j] << ' ';
		fout << '\n';
	}
	fout.close();
}

void matsave(MatComplex_I &a, const std::string &fname, const Int step1, const Int step2)
{
	Int i, j, m = (a.nrows()+step1-1)/step1, n = (a.ncols()+step2-1)/step2;
	Doub cr, ci;
	Complex c;
	ofstream fout(fname);
	for (i = 0; i < m; ++i) {
		for (j = 0; j < n; ++j) {
			c = a[step1*i][step2*j]; cr = real(c); ci = imag(c);
			if (ci == 0)
				fout << cr << ' ';
			else
				fout << cr << '+' << ci << "i ";
		}
		fout << '\n';
	}
	fout.close();
}

void matsave(Mat3DDoub_I &a, const std::string &fname, const Int step1, const Int step2, const Int step3)
{
	Int i, j, k, m, n, q;
	ofstream fout(fname);
	m = (a.dim1() + step1 - 1) / step1; n = (a.dim2() + step2 - 1) / step2;
	q = (a.dim3() + step3 - 1) / step3;
	for (k = 0; k < q; ++k) {
		for (i = 0; i < m; ++i) {
			for (j = 0; j < n; ++j) {
				fout << a[step1*i][step2*j][step3*k] << ' ';
			}
			fout << '\n';
		}
	}
	fout.close();
}

/* specify xyz = 'x','y' or 'z', and take Nslice at indslice[i]
if xyz = 'x', step1 is in y direction, step2 is in z direction, save pa[iy][iz][ix].
if xyz = 'y', step1 is in z direction, step2 is in x direction, save pa[iz][ix][iy].
if xyz = 'z', step1 is in x direction, step2 is in y direction, save pa[ix][iy][iz]. */
void matsave(Mat3DDoub_I &a, const std::string &fname, const Char xyz, VecInt_I &slice,
			const Int step1, const Int step2)
{
	Int i, j, k, m, n, Nslice{ slice.size() };
	ofstream fout(fname);
	if (xyz == 'x') {
		Int ind;
		m = (a.dim2() + step1 - 1) / step1; n = (a.dim3() + step2 - 1) / step2;
		for (i = 0; i < Nslice; ++i) {
			ind = slice[i];
			for (j = 0; j < m; ++j) {
				for (k = 0; k < n; ++k)
					fout << a[ind][step1*j][step2*k] << ' ';
				fout << '\n';
			}
		}
	}
	else if (xyz == 'y') {
		Int ind;
		m = (a.dim3() + step1 - 1) / step1; n = (a.dim1() + step2 - 1) / step2;
		for (j = 0; j < Nslice; ++j) {
			ind = slice[j];
			for (k = 0; k < m; ++k) {
				for (i = 0; i < n; ++i)
					fout << a[step2*i][ind][step1*k] << ' ';
				fout << '\n';
			}
		}
	}
	else if (xyz == 'z') {
		Int ind;
		m = (a.dim1() + step1 - 1) / step1; n = (a.dim2() + step2 - 1) / step2;
		for (k = Nslice - 1; k >= 0; --k) {
			ind = slice[k];
			for (i = 0; i < m; ++i) {
				for (j = 0; j < n; ++j)
					fout << a[step1*i][step2*j][ind] << ' ';
				fout << '\n';
			}
		}
	}
	else {
		cout << "error! illegal value of xyz" << endl; return;
	}
}

void matsave(Mat3DComplex_I &a, const std::string &fname, const Int step1, const Int step2, const Int step3)
{
	Int i, j, k, m, n, q;
	Complex c;
	Doub cr, ci;
	ofstream fout(fname);
	m = (a.dim1() + step1 - 1) / step1; n = (a.dim2() + step2 - 1) / step2;
	q = (a.dim3() + step3 - 1) / step3;
	for (k = 0; k < q; ++k) {
		for (i = 0; i < m; ++i) {
			for (j = 0; j < n; ++j) {
				c = a[step1*i][step2*j][step3*k]; cr = real(c); ci = imag(c);
				if (ci == 0)
					fout << cr << ' ';
				else
					fout << cr << '+' << ci << "i ";
			}
			fout << '\n';
		}
	}
	fout.close();
}

/* specify xyz = 'x','y' or 'z', and take Nslice at indslice[i]
if xyz = 'x', step1 is in y direction, step2 is in z direction, save pa[iy][iz][ix].
if xyz = 'y', step1 is in z direction, step2 is in x direction, save pa[iz][ix][iy].
if xyz = 'z', step1 is in x direction, step2 is in y direction, save pa[ix][iy][iz]. */
void matsave(Mat3DComplex_I &a, const std::string &fname, const Char xyz, VecInt_I &slice,
	const Int step1, const Int step2)
{
	Int i, j, k, m, n, Nslice{ slice.size() };
	Complex c;
	Doub cr, ci;
	ofstream fout(fname);
	if (xyz == 'x') {
		Int ind;
		m = (a.dim2() + step1 - 1) / step1; n = (a.dim3() + step2 - 1) / step2;
		for (i = 0; i < Nslice; ++i) {
			ind = slice[i];
			for (j = 0; j < m; ++j) {
				for (k = 0; k < n; ++k) {
					c = a[ind][step1*j][step2*k]; cr = real(c); ci = imag(c);
					if (ci == 0)
						fout << cr << ' ';
					else
						fout << cr << '+' << ci << "i ";
				}
				fout << '\n';
			}
		}
	}
	else if (xyz == 'y') {
		Int ind;
		m = (a.dim3() + step1 - 1) / step1; n = (a.dim1() + step2 - 1) / step2;
		for (j = 0; j < Nslice; ++j) {
			ind = slice[j];
			for (k = 0; k < m; ++k) {
				for (i = 0; i < n; ++i) {
					c = a[step2*i][ind][step1*k];  cr = real(c); ci = imag(c);
					if (ci == 0)
						fout << cr << ' ';
					else
						fout << cr << '+' << ci << "i ";
				}
				fout << '\n';
			}
		}
	}
	else if (xyz == 'z') {
		Int ind;
		m = (a.dim1() + step1 - 1) / step1; n = (a.dim2() + step2 - 1) / step2;
		for (k = Nslice - 1; k >= 0; --k) {
			ind = slice[k];
			for (i = 0; i < m; ++i) {
				for (j = 0; j < n; ++j) {
					c = a[step1*i][step2*j][ind]; cr = real(c); ci = imag(c);
					if (ci == 0)
						fout << cr << ' ';
					else
						fout << cr << '+' << ci << "i ";
				}
				fout << '\n';
			}
		}
	}
	else {
		cout << "error! illegal value of xyz" << endl; return;
	}
}