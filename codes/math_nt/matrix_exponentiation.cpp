/* Matrix Exponentiation Implementation */

typedef vector< vector<int> > Matrix;

Matrix operator *(const Matrix & a, const Matrix & b){
	Matrix c(a.size(), vector<int>(b[0].size()));
	for(int i = 0; i<a.size(); i++){
		for(int j = 0; j<b[0].size(); j++){
			for(int k = 0; k<b.size(); k++){
				c[i][j] += (a[i][k]*b[k][j]);
			}
		}
	}
	return c;
}

Matrix exp(Matrix & a, int k){
	if(k == 1) return a;
	Matrix c = exp(a, k/2);
	c = c*c;
	if(k%2) c = c*a;
	return c;
}

