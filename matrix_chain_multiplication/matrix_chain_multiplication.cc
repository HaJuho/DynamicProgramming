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

// 행렬의 곱 비용 최소화
// 행렬의 곱을 구할 때 최소 (스칼라) 곱셈의 회수는 ?
// 행렬 A_0 x A_1 x … x A_n-1 을 계산할 때, 각 행렬 A_i의 행의 수는 a[i], 열의 수는 a[i+1]로 주어진다.
// p x q 행렬과 q x r 행렬을 곱하면 스칼라 곱셈의 회수는 p*q*r이다.
// B(i,j) = A_i ~ A_j 곱할 때의 최소 곱셈의 회수
// B(i,i) = 0
// B(i,j) = min(B(i,k) + B(k+1,j) + a[i] * a[k+1] * a[j+1], for i <= k < j), if i < j
// 시간 복잡도 O(N^3)
// 공간 복잡도 O(N^2)
static int cache1[MAXN][MAXN];

int mat_chain_multiplication1(int A[], int n)
{
	for (int i = 0; i < n; ++i)
		cache1[i][i] = 0;
	for (int d = 1; d < n; ++d) {
		for (int i = 0; i < n - d; ++i) {
			int j = i + d;
			int m = 0x7fffffff;
			for (int k = i; k < j; ++k) {
				int v = cache1[i][k] + cache1[k + 1][j] + A[i] * A[k + 1] * A[j + 1];
				m = min(m, v);
			}
			cache1[i][j] = m;
		}
	}
	return cache1[0][n - 1];
}

#define NUMELEM(X) (sizeof(X) / sizeof(int))
int main(int argc, char* argv[])
{
	int testset[] = { 3, 100, 2, 2 };
	//int testset[] = { 2, 2, 100, 3 };
	printf("%d\n", mat_chain_multiplication1(testset, NUMELEM(testset) - 1));
	return 0;
}
