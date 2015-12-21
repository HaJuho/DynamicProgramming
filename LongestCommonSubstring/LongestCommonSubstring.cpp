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

// 최장 공통 부분 연속 수열
// 수열 A[0...m-1]과 수열 B[0...n-1]이 있을 때, 두 수열의 최장 공통 부분 연속 수열의 길이는 ?
// C(i,j) = A[0...i-1]과 B[0...j-1]에서 A[i-1], B[j-1]을 각각 포함한 연속 수열의 최대 길이
// M(i,j) = A[0...i-1]과 B[0...j-1]에서 최장 공통 부분 연속 수열의 길이
// C(0,j) = 0
// C(i,0) = 0
// C(i,j) = 1 + C(i-1,j-1), if A[i-1] == B[j-1], i > 0, j > 0
// C(i,j) = 0, if A[i-1] != B[j-1], i > 0, j > 0
// M(i,j) = max(C(a,b), for 0 <= a <= i, 0 <= b <= j)
// 시간복잡도 O(NM)
// 공간복잡도 O(NM). 반복적 DP로 O(N) 또는 O(M) 최적화 가능

// 1. 공간 O(NM)
static int cache1[MAXN + 1][MAXM + 1];

int lcsubstring1(int A[], int n, int B[], int m)
{
	for (int i = 0; i <= n; ++i)
		cache1[i][0] = 0;
	for (int i = 0; i <= m; ++i)
		cache1[0][i] = 0;
	int lcss = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cache1[i][j] = A[i - 1] == B[j - 1] ? 1 + cache1[i - 1][j - 1] : 0;
			lcss = max(lcss, cache1[i][j]);
		}
	}
	return lcss;
}

// 2. 공간 O(M)
static int cache2[MAXM + 1];
int lcsubstring2(int A[], int n, int B[], int m)
{
	for (int i = 0; i <= m; ++i)
		cache2[i] = 0;
	int lcss = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = m; j > 0; --j) { // backward. be careful of optimization
			cache2[j] = A[i - 1] == B[j - 1] ? 1 + cache2[j - 1] : 0;
			lcss = max(lcss, cache2[j]);
		}
	}
	return lcss;
}

#define NUMELEM(X) (sizeof(X) / sizeof(int))
int main(int argc, char* argv[])
{
	int testset1[] = { 1, 2, 3, 2, 4, 1, 2 };
	int testset2[] = { 2, 4, 1, 1, 2, 1 };
	printf("%d\n", lcsubstring1(testset1, NUMELEM(testset1), testset2, NUMELEM(testset2)));
	printf("%d\n", lcsubstring2(testset1, NUMELEM(testset1), testset2, NUMELEM(testset2)));

	return 0;
}
