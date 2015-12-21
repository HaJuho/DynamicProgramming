#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cassert>

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

static const int DEN = 1000000007;

static const int MAXN = 10000;

// 이항 계수 구하기
// C(n,0) = 1
// C(n,n) = 1
// C(n,r) = C(n-1,r-1) + C(n-1,r), if 0 < r < n
// 시간복잡도 O(N^2)
// 공간복잡도 O(N^2). 반복적 DP로 O(N) 최적화 가능

// 1. memoization -> recursion overhead. stack overflow.
static int cache1[MAXN + 1][MAXN + 1];

void init_cache1()
{
	for (int i = 0; i <= MAXN; ++i)
		for (int j = 0; j <= MAXN; ++j)
			cache1[i][j] = -1;
}

int binomial1(int n, int r)
{
	if (cache1[n][r] >= 0)
		return cache1[n][r];
	if (r == 0 || r == n)
		return cache1[n][r] = 1;
	int v = binomial1(n - 1, r - 1) + binomial1(n - 1, r);
	return cache1[n][r] = v > DEN ? v - DEN : v;
}

// 2. 반복적 DP -> memoization의 초기화 생략 가능. 꼭 필요하지 않은 계산 포함.
static int cache2[MAXN + 1][MAXN + 1];
static int initialized2 = 0;

int binomial2(int n, int r)
{
	if (n > initialized2) {
		for (int i = initialized2 + 1; i <= n; ++i) {
			cache2[i][0] = 1;
			for (int j = 1; j < i; ++j) {
				int v = cache2[i - 1][j - 1] + cache2[i - 1][j];
				cache2[i][j] = v > DEN ? v - DEN : v;
			}
			cache2[i][i] = 1;
		}
		initialized2 = n;
	}
	return cache2[n][r];
}

#define NUMELEM(X) (sizeof(X) / sizeof(int))
int main(int argc, char* argv[])
{
	init_cache1();
	int testset[] = { 5, 3, 10, 7, 2, 2, 50, 25, 1000, 500 };
	for (int i = 0; i < NUMELEM(testset); i += 2) {
		int n = testset[i];
		int r = testset[i + 1];
		printf("%d/%d: %d %d\n", n, r, binomial1(n, r), binomial2(n, r));
	}
	return 0;
}
