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
// M(k) = 크기 k인 배낭에 담을 수 있는 최대 가치
// M(0) = 0
// M(k) = max(0, max(M(k-w[i]) + v[i], for 0 <= i < n, w[i] <= k)), if k > 0
// 시간 복잡도 O(NC)
// 공간 복잡도 O(C)

// 1.
static int cache1[MAXC + 1];

int knapsack1(int W[], int V[], int n, int C)
{
	cache1[0] = 0;
	for (int i = 1; i <= C; ++i) {
		int m = 0;
		for (int j = 0; j < n; ++j) {
			if (W[j] <= i)
				m = max(m, cache1[i - W[j]] + V[j]);
		}
		cache1[i] = m;
	}
	return cache1[C];
}

#define NUMELEM(X) (sizeof(X) / sizeof(int))
int main(int argc, char* argv[])
{
	int ws[] = { 3, 5, 7, 4, 3, 9, 2, 9, 5, 10 };
	int vs[] = { 2, 3, 3, 4, 4, 5, 7, 8, 8, 9 };
	printf("%d\n", knapsack1(ws, vs, NUMELEM(ws), 28));
	return 0;
}
