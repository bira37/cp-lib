
copy

    /**
        This program used to to multiply two polynomials A and B have the same (M/2-1)-degree ( M is power of 2 )
        @result C is a polynomial with M-1 degree ( M is power of 2 )
    */
    #include <iostream>
    #include <cstdio>
    #include <cmath>
    #include <complex>
    using namespace std;
    const long double PI = acos(-1);
    const int M = (1<<3);
    typedef long double ld;
     
    complex<ld> getPrimitiveRootOfUnity(int gen) {
        return complex<ld>(cos(2*PI/gen), sin(2*PI/gen));
    }
    class Polynomial {
    private:
        int sz;
    public:
        complex<ld> *f;
        Polynomial(int sz) {
            this->sz = sz;
            this->f = new complex<ld>[this->sz];
            for(int i = 0; i < this->sz; i++) this->f[i] = complex<ld>(0,0);
        }
    };
    inline Polynomial FFT(Polynomial A, int m, complex<ld> w)
    {
        if (m==1) return A;
     
        Polynomial A_even(m/2);
        Polynomial A_odd(m/2);
        for(int i = 0; i < m; i+=2) {
            A_even.f[i/2] = A.f[i];
            A_odd.f[i/2] = A.f[i+1];
        }
        Polynomial F_even = FFT(A_even, m/2, w*w);    //w^2 is a primitive m/2-th root of unity
        Polynomial F_odd = FFT(A_odd, m/2, w*w);
        Polynomial F(m);
        complex<ld> x(1,0);
        for (int j=0; j < m/2; ++j) {
          F.f[j] = F_even.f[j] + x*F_odd.f[j];
          F.f[j+m/2] = F_even.f[j] - x*F_odd.f[j];
          x = x * w;
        }
        return F;
    }
    int main() {
        Polynomial A(M/2), B(M/2);
        // enter polynomial A and B both with M/2 degree
        enterPolynomial_A;
        enterPolynomial_B;
        complex<ld> w = getPrimitiveRootOfUnity(M);
        Polynomial F_A = FFT(A, M, w);
        Polynomial F_B = FFT(B, M, w);
        Polynomial F_C(M);
        for(int i = 0; i < M; i++) F_C.f[i] = F_A.f[i] * F_B.f[i];
        // w_ = w^{-1}
        complex<ld> w_(1,0);
        for(int i = 0; i < M-1; i++) w_ *= w;
        // 2 last statement to compute result polynomial, result going to be located in C
        Polynomial C = FFT(F_C, M, w_);
        for(int i = 0; i < M; i++) C.f[i] *= (ld)1.0/M;
    	return 0;
    }
