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

// 최장 공통 부분 수열
// 수열 A[0...m-1]과 수열 B[0...n-1]이 있을 때, 두 수열의 공통 부분 수열의 길이의 최대값은?
// Subsequence는 연속으로 선택할 필요는 없다.
// LCS(i,j) = A[0...i-1]와 B[0...j-1] 사이의 LCS 길이
// LCS(0,j) = 0
// LCS(i,0) = 0
// LCS(i,j) = 1 + LCS(i-1,j-1), if A[i-1] == B[j-1], i > 0, j > 0
// LCS(i,j) = max(LCS(i-1,j), LCS(i,j-1)), if A[i-1] != B[j-1], i > 0, j > 0
// 시간복잡도 O(NM)
// 공간복잡도 O(NM). 반복적 DP로 O(N) 또는 O(M) 최적화 가능

// 1. 공간 O(NM)
static int cache1[MAXN + 1][MAXM + 1];

int lcs1(int A[], int n, int B[], int m)
{
	for (int i = 0; i <= n; ++i)
		cache1[i][0] = 0;
	for (int i = 0; i <= m; ++i)
		cache1[0][i] = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (A[i - 1] == B[j - 1])
				cache1[i][j] = 1 + cache1[i - 1][j - 1];
			else
				cache1[i][j] = max(cache1[i - 1][j], cache1[i][j - 1]);
		}
	}
	return cache1[n][m];
}

// 2. 공간 O(M)
static int cache2[2][MAXM + 1]; // double buffer
int lcs2(int A[], int n, int B[], int m)
{
	int* cur = cache2[0];
	int* prev = cache2[1];
	for (int i = 0; i <= m; ++i)
		cur[i] = 0;
	for (int i = 1; i <= n; ++i) {
		swap(cur, prev);
		for (int j = 1; j <= m; ++j) {
			if (A[i - 1] == B[j - 1])
				cur[j] = 1 + prev[j - 1];
			else
				cur[j] = max(prev[j], cur[j - 1]);
		}
	}
	return cur[m];
}

#define NUMELEM(X) (sizeof(X) / sizeof(int))
int main(int argc, char* argv[])
{
	int testset1[] = { 1, 2, 3, 2, 4, 1, 2 };
	int testset2[] = { 2, 4, 3, 1, 2, 1 };
	printf("%d\n", lcs1(testset1, NUMELEM(testset1), testset2, NUMELEM(testset2)));
	printf("%d\n", lcs2(testset1, NUMELEM(testset1), testset2, NUMELEM(testset2)));

	return 0;
}
