#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cassert>

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

static const int MAXN = 1000;
static const int MAXM = 1000;

// 수열 A[0...n-1]에서 B[0...m-1]과 같은 Subsequence의 개수는?
// Subsequence는 연속으로 선택될 필요는 없다.
// C(i,j) = A[0...i-1]에서 찾은 B[0...j-1]와 같은 Subsuquence의 개수
// C(0,0) = 1
// C(i,0) = 1
// C(0,j) = 0, if j > 0
// C(i,j) = C(i-1,j-1) + C(i-1,j), if A[i-1] == B[j-1], i > 0, j > 0
// C(i,j) = C(i-1,j), if A[i-1] != B[j-1], i > 0, j > 0
// 시간 복잡도 O(NM)
// 공간 복잡도 O(NM). 반복적 DP로 O(M) 최적화 가능

// 1. 공간 O(NM)
static int cache1[MAXN + 1][MAXM + 1];

int find_subsequence1(int A[], int n, int B[], int m)
{
	cache1[0][0] = 1;
	for (int i = 1; i <= m; ++i)
		cache1[0][i] = 0;
	for (int i = 1; i <= n; ++i) {
		cache1[i][0] = 1;
		for (int j = 1; j <= m; ++j) {
			if (A[i - 1] == B[j - 1])
				cache1[i][j] = cache1[i - 1][j - 1] + cache1[i - 1][j];
			else
				cache1[i][j] = cache1[i - 1][j];
		}
	}
	return cache1[n][m];
}

// 2. 공간 O(M)
static int cache2[MAXM + 1];

int find_subsequence2(int A[], int n, int B[], int m)
{
	cache2[0] = 1;
	for (int i = 1; i <= m; ++i)
		cache2[i] = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = m; j > 0; --j) {
			if (A[i - 1] == B[j - 1])
				cache2[j] += cache2[j - 1];
		}
		cache2[0] = 1;
	}
	return cache2[m];
}

#define NUMELEM(X) (sizeof(X) / sizeof(int))
int main(int argc, char* argv[])
{
	int testseta[] = { 1, 2, 1, 4, 3, 2 };
	int testsetb[] = { 1, 2 };
	printf("%d\n", find_subsequence1(testseta, NUMELEM(testseta), testsetb, NUMELEM(testsetb)));
	printf("%d\n", find_subsequence2(testseta, NUMELEM(testseta), testsetb, NUMELEM(testsetb)));
	return 0;
}
