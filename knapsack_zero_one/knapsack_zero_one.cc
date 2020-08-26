#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cassert>

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

static const int MAXC = 10000;
static const int MAXN = 100;

// 배낭의 용량이 C이고, n개의 물품 각각의 무게가 w[0...n-1], 가치가 v[0...n-1] 일 때, 배낭에 담을 수 있는 물품의 최대 가치는?
// 물건은 최대 하나만 담을 수 있다.
// B(i,k) = 물품 v[0...i-1]를 사용해 크기 k인 배낭에 담을 수 있는 최대 가치
// B(0,k) = 0
// B(i,0) = 0
// B(i,k) = B(i-1,k), if i > 0, k < w[i-1]
// B(i,k) = max(B(i-1,k), B(i-1,k-w[i-1]) + v[i-1]), if i > 0, k >= w[i-1]
// 시간 복잡도 O(NC)
// 공간 복잡도 O(NC). 반복적 DP로 O(C) 최적화 가능

// 1. 공간 O(NC)
static int cache1[MAXN + 1][MAXC + 1];

int knapsack01_1(int W[], int V[], int n, int C)
{
	for (int i = 0; i <= n; ++i)
		cache1[i][0] = 0;
	for (int i = 0; i <= C; ++i)
		cache1[0][i] = 0;
	for (int i = 1; i <= n; ++i) {
		int w = W[i - 1];
		int v = V[i - 1];
		for (int j = 1; j < w; ++j)
			cache1[i][j] = cache1[i - 1][j];
		for (int j = w; j <= C; ++j)
			cache1[i][j] = max(cache1[i - 1][j], cache1[i - 1][j - w] + v);
	}
	return cache1[n][C];
}

// 2. 공간 O(C)
static int cache2[MAXC + 1];

int knapsack01_2(int W[], int V[], int n, int C)
{
	for (int i = 0; i <= C; ++i)
		cache2[i] = 0;
	for (int i = 1; i <= n; ++i) {
		int w = W[i - 1];
		int v = V[i - 1];
		for (int j = C; j >= w; --j) // backward. be careful of optimization
			cache2[j] = max(cache2[j], cache2[j - w] + v);
	}
	return cache2[C];
}

#define NUMELEM(X) (sizeof(X) / sizeof(int))
int main(int argc, char* argv[])
{
	int ws[] = { 3, 5, 7, 4, 3, 9, 2, 9, 5, 10 };
	int vs[] = { 2, 3, 3, 4, 4, 5, 7, 8, 8, 9 };
	printf("%d\n", knapsack01_1(ws, vs, NUMELEM(ws), 20));
	printf("%d\n", knapsack01_2(ws, vs, NUMELEM(ws), 20));
	return 0;
}
