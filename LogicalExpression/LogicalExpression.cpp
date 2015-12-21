#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cassert>

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

static const int MAXN = 100;

// true, false, and, or, xor로 구성된 식의 값이 참이 되도록 만드는 방법의 수는?
// A[0..n]에 true, false가 주어짐
// B[0..n-1]에 연산자가 주어짐
// T(i,j) = A[i...j]를 계산하여 true로 만드는 방법의 수
// F(i,j) = A[i...j]를 계산하여 false로 만드는 방법의 수
// L(i,j) = T(i,j) + F(i,j)
// T(i,i) = A[i] == true ? 1 : 0
// F(i,i) = A[i] == false ? 0 : 1
// T(i,j) = sum(T(i,k) * T(k+1,j), for i <= k < j, B[k] == 'and')
//        + sum(L(i,k) * L(k+1,j) - F(i,k) * F(k+1,j), for i <= k < j, B[k] == 'or')
//        + sum(T(i,k) * F(k+1,j) + F(i,k) * T(k+1,j), for i <= k < j, B[k] == 'xor'), if i < j
// F(i,j) = sum(F(i,k) * F(k+1,j), for i <= k < j, B[k] == 'or')
//        + sum(L(i,k) * L(k+1,j) - T(i,k) * T(k+1,j), for i <= k < j, B[k] == 'and')
//        + sum(T(i,k) * F(k+1,j) + F(i,k) * T(k+1,j), for i <= k < j, B[k] == 'xor'), if i < j
// 시간 복잡도 O(N^3)
// 공간 복잡도 O(N^2)
static int cache1_t[MAXN + 1][MAXN + 1];
static int cache1_f[MAXN + 1][MAXN + 1];

int true_logical_expressions1(bool A[], char B[], int n)
{
	for (int i = 0; i <= n; ++i) {
		cache1_t[i][i] = A[i] ? 1 : 0;
		cache1_f[i][i] = A[i] ? 0 : 1;
	}
	for (int d = 1; d <= n; ++d) {
		for (int i = 0; i <= n - d; ++i) {
			int j = i + d;
			int t = 0;
			int f = 0;
			for (int k = i; k < j; ++k) {
				char op = B[k];
				int ta = cache1_t[i][k];
				int tb = cache1_t[k + 1][j];
				int fa = cache1_f[i][k];
				int fb = cache1_f[k + 1][j];
				if (op == 'a') { // AND
					t += ta * tb;
					f += fa * fb + fa * tb + ta * fb;
				}
				else if (op == 'o') { // OR
					t += ta * tb + ta * fb + fa * tb;
					f += fa * fb;
				}
				else { // XOR
					t += ta * fb + fa * tb;
					f += ta * tb + fa * fb;
				}
			}
			cache1_t[i][j] = t;
			cache1_f[i][j] = f;
		}
	}
	return cache1_t[0][n];
}

int main(int argc, char* argv[])
{
	//bool A[] = { true, false, true };
	//char B[] = "ax";
	bool A[] = { true, false, true, true };
	char B[] = "oax";
	printf("%d\n", true_logical_expressions1(A, B, strlen(B)));

	return 0;
}
