// txt version of matOpen
// if fname has ".mat" extension, change to ".m"
// if fname does not have ".m" extension, append ".m"
// if fname include multiple ".", change all to "_"
// if fname start with number, prepend "data_"

typedef std::ofstream MATFile;

MATFile *matOpen(std::string fname, std::string rw)
{
	Int i, N = fname.size();

	// correct filename
	if (fname[N - 1] == 't' && fname[N - 2] == 'a') {
		fname.erase(fname.size() - 2, 2); N -= 2;
	}
	else if (fname[N - 1] != 'm' || fname[N - 1] != '.') {
		fname = fname + ".m"; N += 2;
	}
	for (i = 0; i < N - 3; ++i)
		if (fname[i] == '.') fname[i] = '_';
	if (fname[0] >= '0' && fname[0] <= '9')
		fname = "data_" + fname;

	// create output file
	MATFile* pfile = new ofstream;
	*pfile = ofstream(fname);
	return pfile;
}

void matClose(MATFile* pfile)
{
	pfile->close();
	delete pfile;
}

void matsave(const Uchar s, const std::string &varname, MATFile *pfile)
{
	*pfile << varname << " = uint8(" << (Int)s << ");\n\n" << endl;
}

void matsave(const Int s, const std::string &varname, MATFile *pfile)
{
	*pfile << varname << " = int32(" << s << ");\n\n" << endl;
}

void matsave(const Doub s, const string &varname, MATFile *pfile)
{
	*pfile << varname << " = " << s << ";\n\n" << endl;
}

void matsave(const Complex s, const string &varname, MATFile *pfile)
{
	*pfile << varname << " = " << real(s) << "+" << imag(s) << "i;\n\n" << endl;
}

void matsave(VecUchar_I &v, const std::string &varname, MATFile *pfile)
{
	Int i, N = v.size();
	if (N == 0) {
		*pfile << varname << " = uint8([]);\n\n" << endl; return;
	}
	*pfile << varname << " = uint8([";
	for (i = 0; i < N; ++i)
		*pfile << (Int)v[i] << ',';
	*pfile << "]);\n\n" << endl;
}

void matsave(VecInt_I &v, const std::string &varname, MATFile *pfile)
{
	Int i, N = v.size();
	if (N == 0) {
		*pfile << varname << " = int32([]);\n" << endl; return;
	}
	*pfile << varname << " = int32([";
	for (i = 0; i < N; ++i)
		*pfile << v[i] << ',';
	*pfile << "]);\n\n" << endl;
}

void matsave(VecDoub_I &v, const std::string &varname, MATFile *pfile)
{
	Int N = v.size();
	if (N == 0) {
		*pfile << varname << " = [];\n\n"; return;
	}
	*pfile << varname << " = [";
	for (Int i = 0; i < N; ++i)
		*pfile << v[i] << ',';
	*pfile << "];\n\n" << endl;
}

void matsave(VecComplex_I &v, const string &varname, MATFile *pfile)
{
	Int N = v.size();
	Doub cr, ci;
	if (N == 0) {
		*pfile << varname << " = [];\n\n"; return;
	}
	*pfile << varname << " = [";
	for (Int i = 0; i < N; ++i) {
		cr = real(v[i]); ci = imag(v[i]);
		if (ci == 0)
			*pfile << cr << ',';
		else
			*pfile << cr << '+' << ci << "i,";
	}
	*pfile << "];\n\n" << endl;
}

void matsave(MatUchar_I &a, const std::string &varname, MATFile *pfile,
	const Int step1, const Int step2)
{
	if (a.ncols() == 0 || a.nrows() == 0) {
		*pfile << varname << " = uint8([]);\n\n"; return;
	}
	Int i, j, m, n;
	*pfile << varname << " = uint8([";

	if (step1 > 1 || step2 > 1) {
		m = (a.nrows() + step1 - 1) / step1; n = (a.ncols() + step2 - 1) / step2;
		for (i = 0; i < m; ++i) {
			for (j = 0; j < n; ++j)
				*pfile << (Int)a[i][j] << ',';
			*pfile << ';';
		}
	}
	else {
		m = a.nrows(); n = a.ncols();
		for (i = 0; i < m; ++i) {
			for (j = 0; j < n; ++j)
				*pfile << (Int)a[i][j] << ',';
			*pfile << ';';
		}
	}
	*pfile << "]);\n\n" << endl;
}

void matsave(MatInt_I &a, const std::string &varname, MATFile *pfile,
	const Int step1, const Int step2)
{
	if (a.ncols() == 0 || a.nrows() == 0) {
		*pfile << varname << " = int32([]);\n\n"; return;
	}
	Int i, j, m, n;
	*pfile << varname << " = int32([";

	if (step1 > 1 || step2 > 1) {
		m = (a.nrows() + step1 - 1) / step1; n = (a.ncols() + step2 - 1) / step2;
		for (i = 0; i < m; ++i) {
			for (j = 0; j < n; ++j)
				*pfile << a[i][j] << ',';
			*pfile << ';';
		}
	}
	else {
		m = a.nrows(); n = a.ncols();
		for (i = 0; i < m; ++i) {
			for (j = 0; j < n; ++j)
				*pfile << a[i][j] << ',';
			*pfile << ';';
		}
	}
	*pfile << "]);\n\n" << endl;
}

void matsave(MatDoub_I &a, const string &varname, MATFile *pfile,
	const Int step1, const Int step2)
{
	if (a.ncols() == 0 || a.nrows() == 0) {
		*pfile << varname << " = [];\n\n"; return;
	}
	Int i, j, m, n;
	*pfile << varname << " = [";

	if (step1 > 1 || step2 > 1) {
		m = (a.nrows() + step1 - 1) / step1; n = (a.ncols() + step2 - 1) / step2;
		for (i = 0; i < m; ++i) {
			for (j = 0; j < n; ++j)
				*pfile << a[step1*i][step2*j] << ',';
			*pfile << ';';
		}
	}
	else {
		m = a.nrows(); n = a.ncols();
		for (i = 0; i < m; ++i) {
			for (j = 0; j < n; ++j)
				*pfile << a[i][j] << ',';
			*pfile << ';';
		}
	}
	*pfile << "];\n\n" << endl;
}

void matsave(MatComplex_I &a, const string &varname, MATFile *pfile,
	const Int step1, const Int step2)
{
	if (a.ncols() == 0 || a.nrows() == 0) {
		*pfile << varname << " = [];\n\n"; return;
	}
	Int i, j, m, n;
	Complex c;
	Doub cr, ci;
	*pfile << varname << " = [";
	if (step1 > 1 || step2 > 1) {
		m = (a.nrows() + step1 - 1) / step1; n = (a.ncols() + step2 - 1) / step2;
		for (i = 0; i < m; ++i) {
			for (j = 0; j < n; ++j) {
				c = a[step1*i][step2*j]; cr = real(c); ci = imag(c);
				if (ci != 0)
					*pfile << cr << '+' << ci << "i,";
				else
					*pfile << cr << ',';
			}
			*pfile << ';';
		}
	}
	else {
		m = a.nrows(); n = a.ncols();
		for (i = 0; i < m; ++i) {
			for (j = 0; j < n; ++j) {
				c = a[i][j]; cr = real(c); ci = imag(c);
				if (ci != 0)
					*pfile << cr << '+' << ci << "i,";
				else
					*pfile << cr << ',';
			}
			*pfile << ';';
		}
	}
	*pfile << "];\n\n" << endl;
}

void matsave(Mat3DDoub_I &a, const std::string &varname, MATFile *pfile,
	const Int step1, const Int step2, const Int step3)
{
	Int i, j, k, m, n, q, mn;
	m = a.dim1(); n = a.dim2(); q = a.dim3(); mn = m * n;
	if (step1 > 1 || step2 > 1 || step3 > 1) {
		m = (m + step1 - 1) / step1; n = (n + step2 - 1) / step2;
		q = (q + step3 - 1) / step3;
		for (k = q-1; k >= 0; --k) {
			*pfile << varname << "(:,:," << k+1 << ") = [";
			for (i = 0; i < m; ++i) {
				for (j = 0; j < n; ++j)
					*pfile << a[step1*i][step2*j][step3*k] << ',';
				*pfile << ';';
			}
			*pfile << "]; ";
		}
		*pfile << "\n\n" << endl;
	}
	else {
		m = (m + step1 - 1) / step1; n = (n + step2 - 1) / step2;
		q = (q + step3 - 1) / step3;
		for (k = q - 1; k >= 0; --k) {
			*pfile << varname << "(:,:," << k+1 << ") = [";
			for (i = 0; i < m; ++i) {
				for (j = 0; j < n; ++j)
					*pfile << a[i][j][k] << ',';
				*pfile << ';';
			}
			*pfile << "]; ";
		}
		*pfile << "\n\n" << endl;
	}
}

/* specify xyz = 'x','y' or 'z', and take Nslice at indslice[i]
if xyz = 'x', step1 is in y direction, step2 is in z direction, save pa[iy][iz][ix].
if xyz = 'y', step1 is in z direction, step2 is in x direction, save pa[iz][ix][iy].
if xyz = 'z', step1 is in x direction, step2 is in y direction, save pa[ix][iy][iz]. */
void matsave(Mat3DDoub_I &a, const std::string &varname, MATFile *pfile,
	const Char xyz, VecInt_I &slice, const Int step1, const Int step2)
{
	Int i, j, k, m, n, Nslice{ slice.size() };
	if (xyz == 'x') {
		Int ind;
		m = (a.dim2() + step1 - 1) / step1; n = (a.dim3() + step2 - 1) / step2;
		for (i = Nslice-1; i >= 0; --i) {
			*pfile << varname << "(:,:," << i+1 << ") = [";
			ind = slice[i];
			for (j = 0; j < m; ++j) {
				for (k = 0; k < n; ++k)
					*pfile << a[ind][step1*j][step2*k] << ',';
				*pfile << ';';
			}
			*pfile << "]; ";
		}
		*pfile << "\n\n" << endl;
	}
	else if (xyz == 'y') {
		Int ind;
		m = (a.dim3() + step1 - 1) / step1; n = (a.dim1() + step2 - 1) / step2;
		for (j = Nslice - 1; j >= 0; --j) {
			*pfile << varname << "(:,:," << j+1 << ") = [";
			ind = slice[j];
			for (k = 0; k < m; ++k) {
				for (i = 0; i < n; ++i)
					*pfile << a[step2*i][ind][step1*k] << ',';
				*pfile << ';';
			}
			*pfile << "]; ";
		}
		*pfile << "\n\n" << endl;
	}
	else if (xyz == 'z') {
		Int ind;
		m = (a.dim1() + step1 - 1) / step1; n = (a.dim2() + step2 - 1) / step2;
		for (k = Nslice-1; k >= 0; --k) {
			*pfile << varname << "(:,:," << k+1 << ") = [";
			ind = slice[k];
			for (i = 0; i < m; ++i) {
				for (j = 0; j < n; ++j)
					*pfile << a[step1*i][step2*j][ind] << ',';
				*pfile << ';';
			}
			*pfile << "]; ";
		}
		*pfile << "\n\n" << endl;
	}
	else {
		cout << "error! illegal value of xyz" << endl; return;
	}
}

void matsave(Mat3DComplex_I &a, const std::string &varname, MATFile *pfile,
	const Int step1, const Int step2, const Int step3)
{
	Int i, j, k, m, n, q;
	Complex c;
	Doub cr, ci;
	m = a.dim1(); n = a.dim2(); q = a.dim3();
	if (step1 > 1 || step2 > 1 || step3 > 1) {
		m = (m + step1 - 1) / step1; n = (n + step2 - 1) / step2;
		q = (q + step3 - 1) / step3;
		for (k = q - 1; k >= 0; --k) {
			*pfile << varname << "(:,:," << k+1 << ") = [";
			for (i = 0; i < m; ++i) {
				for (j = 0; j < n; ++j) {
					c = a[step1*i][step2*j][step3*k]; cr = real(c); ci = imag(c);
					if (ci == 0.)
						*pfile << cr << ',';
					else
						*pfile << cr << '+' << ci << "i,";
				}
				*pfile << ';';
			}
			*pfile << "]; ";
		}
		*pfile << "\n\n" << endl;
	}
	else {
		m = (m + step1 - 1) / step1; n = (n + step2 - 1) / step2;
		q = (q + step3 - 1) / step3;
		for (k = q - 1; k >= 0; --k) {
			*pfile << varname << "(:,:," << k+1 << ") = [";
			for (i = 0; i < m; ++i) {
				for (j = 0; j < n; ++j) {
					c = a[i][j][k]; cr = real(c); ci = imag(c);
					if (ci == 0.)
						*pfile << cr << ',';
					else
						*pfile << cr << '+' << ci << "i,";
				}
				*pfile << ';';
			}
			*pfile << "]; ";
		}
		*pfile << "\n\n" << endl;
	}
}

/* specify xyz = 'x','y' or 'z', and take Nslice at indslice[i]
if xyz = 'x', step1 is in y direction, step2 is in z direction, save pa[iy][iz][ix].
if xyz = 'y', step1 is in z direction, step2 is in x direction, save pa[iz][ix][iy].
if xyz = 'z', step1 is in x direction, step2 is in y direction, save pa[ix][iy][iz]. */
void matsave(Mat3DComplex_I &a, const std::string &varname, MATFile *pfile,
	const Char xyz, VecInt_I &slice, const Int step1, const Int step2)
{
	Int i, j, k, m, n, Nslice{ slice.size() };
	Complex c;
	Doub cr, ci;
	if (xyz == 'x') {
		Int ind;
		m = (a.dim2() + step1 - 1) / step1; n = (a.dim3() + step2 - 1) / step2;
		for (i = Nslice - 1; i >= 0; --i) {
			*pfile << varname << "(:,:," << i+1 << ") = [";
			ind = slice[i];
			for (j = 0; j < m; ++j) {
				for (k = 0; k < n; ++k)
				{
					c = a[ind][step1*j][step2*k]; cr = real(c); ci = imag(c);
					if (ci == 0.)
						*pfile << cr << ',';
					else
						*pfile << cr << '+' << ci << "i,";
				}
				*pfile << ';';
			}
			*pfile << "]; ";
		}
		*pfile << "\n\n" << endl;
	}
	else if (xyz == 'y') {
		Int ind;
		m = (a.dim3() + step1 - 1) / step1; n = (a.dim1() + step2 - 1) / step2;
		for (j = Nslice-1; j >= 0; --j) {
			*pfile << varname << "(:,:," << j+1 << ") = [";
			ind = slice[j];
			for (k = 0; k < m; ++k) {
				for (i = 0; i < n; ++i)
				{
					c = a[step2*i][ind][step1*k]; cr = real(c); ci = imag(c);
					if (ci == 0.)
						*pfile << cr << ',';
					else
						*pfile << cr << '+' << ci << "i,";
				}
				*pfile << ';';
			}
			*pfile << "]; ";
		}
		*pfile << "\n\n" << endl;
	}
	else if (xyz == 'z') {
		Int ind;
		m = (a.dim1() + step1 - 1) / step1; n = (a.dim2() + step2 - 1) / step2;
		for (k = Nslice - 1; k >= 0; --k) {
			*pfile << varname << "(:,:," << k+1 << ") = [";
			ind = slice[k];
			for (i = 0; i < m; ++i) {
				for (j = 0; j < n; ++j)
				{
					c = a[step1*i][step2*j][ind]; cr = real(c); ci = imag(c);
					if (ci == 0.)
						*pfile << cr << ',';
					else
						*pfile << cr << '+' << ci << "i,";
				}
				*pfile << ';';
			}
			*pfile << "]; ";
		}
		*pfile << "\n\n" << endl;
	}
	else {
		cout << "error! illegal value of xyz" << endl; return;
	}
}