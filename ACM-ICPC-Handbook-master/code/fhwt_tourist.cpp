//references taken :- https://www.hackerearth.com/challenges/competitive/june-circuits-19/algorithm/xor-paths-dd39904a/submission/27540843/
namespace fwht {
template<typename T>
void hadamard(vector<T> &a) {
  int n = a.size();
  for (int k = 1; k < n; k <<= 1) {
    for (int i = 0; i < n; i += 2 * k) {
      for (int j = 0; j < k; j++) {
        T x = a[i + j];
        T y = a[i + j + k];
        a[i + j] = x + y;
        a[i + j + k] = x - y;
      }
    }
  }
}
template<typename T>
vector<T> multiply(vector<T> a, vector<T> b) {
  int eq = (a == b);
  int n = 1;
  while (n < (int) max(a.size(), b.size())) {
    n <<= 1;
  }
  a.resize(n);
  b.resize(n);
  hadamard(a);
  if (eq) b = a; else hadamard(b);
  for (int i = 0; i < n; i++) {
    a[i] *= b[i];
  }
  hadamard(a);
  T q = 1 / static_cast<T>(n);
  for (int i = 0; i < n; i++) {
    a[i] *= q;
  }
  return a;
}
}  // namespace fwht
/*****USAGE**********
	vector<Mint> cc(1 << 17, 0);
	for (int i = 0; i < n; i++) {
		cc[mark[i]]++;
	}
	cc = fwht::multiply(cc, cc);
********************/
/**********************
Ref :- https://www.hackerearth.com/problem/algorithm/submatrix-queries-7e459f97/editorial/
If you have a hard time understanding the editorial, this may help you.
Let's talk a little about FFT (Fast Fourier Transform) first. FFT aims to multiply two n-degree polynomials A and B in nlogn using these steps:
1) Calculate FFT of A and B, let them be A' and B'.
2) Calculate array C' where C'[i] = A'[i]*B'[i].
3) Calculate inverse FFT of C' to get the answer (A*B)=C.
Assuming that C[i] = coefficient of of x^i in A*B, then the procedure above adds A[j]*B[k] to C[j+k] for every j and k.
Now returning to the question, if we observe carefully, we notice that we want to modify the procedure above to add Cnt[j]*Cnt[k]*Cnt[m] to C[j AND k AND m] for every j, k, m, where Cnt[i] = count of value i in range from l to r. So basically we can imagine Cnt as a polynomial where Cnt[i] is coefficient of x^i which is the count of value i in range from l to r.
Fast Walsh–Hadamard transform is a variation of FFT which can be used with two polynomials A and B to add A[j]*B[k] to C[j AND k] for every j and k. So what we want to do with Cnt, is to calculate Cnt^3, which adds Cnt[j]*Cnt[k]*Cnt[m] to C[j AND k AND m] for every j, k, m. That is, C[i] = number of all triplets which have bitwise AND = i. So our answer is obviously C[X]. The steps to do this are very close to FFT:
1) Calculate Fast Walsh–Hadamard transform of Cnt, let it be Cnt'.
2) Calculate array C' where C'[i] = Cnt'[i]^3.
3) Calculate inverse Fast Walsh–Hadamard transform of C' to get C.
**********************/
