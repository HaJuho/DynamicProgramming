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

// 가격 C를 n개의 동전 v[0...n-1]로 환전하는 방법의 수는?
// 수분할과 비슷하게 풀어도 된다.
// 여기서는 순차적 DP로 푼다.
// B(i,k) = v[0...i] 까지의 동전을 사용해 가격 k를 환전하는 방법의 수
// B(0,k) = 1, if k % v[0] == 0
// B(0,k) = 0, if k % v[0] != 0
// B(i,k) = B(i-1,k), if k < v[i], i > 0
// B(i,k) = B(i-1,k) + B(i,k-v[i]), if k >= v[i], i > 0
// 시간 복잡도 O(NC)
// -> 모든 table을 순차적으로 다 채우므로 사실 불필요한 계산도 포함
// -> 필요한 계산만 하려면 수분할에서 처럼 recursion과 memoization을 사용하면 됨.
// -> 대신 함수 호출 overhead와 stack overflow 등의 문제 있음.
// 공간 복잡도 O(NC). 반복적 DP로 O(C) 최적화 가능

// 1. 공간 O(NC)
static int cache1[MAXN][MAXC + 1];
int exchanges1(int V[], int n, int C)
{
	int v = V[0];
	for (int i = 0; i <= C; ++i) {
		cache1[0][i] = (i % v) ? 0 : 1;
	}
	for (int i = 1; i < n; ++i) {
		int v = V[i];
		for (int j = 0; j < v; ++j) {
			cache1[i][j] = cache1[i - 1][j];
		}
		for (int j = v; j <= C; ++j) {
			cache1[i][j] = cache1[i - 1][j] + cache1[i][j - v];
		}
	}
	return cache1[n - 1][C];
}

// 2. 공간 O(C)
static int cache2[MAXC + 1];
int exchanges2(int V[], int n, int C)
{
	int v = V[0];
	for (int i = 0; i <= C; ++i) {
		cache2[i] = (i % v) ? 0 : 1;
	}
	for (int i = 1; i < n; ++i) {
		int v = V[i];
		for (int j = v; j <= C; ++j) {
			cache2[j] += cache2[j - v];
		}
	}
	return cache2[C];
}

// 최적 환전
// 가장 적은 수의 동전으로 환전하기. 배낭 문제와 같다?
// 3.
// D(i,k) = v[0...i] 까지의 동전을 사용해서 돈 k를 환전하는 가장 작은 동전의 수
// D(0,k) = k / v[0], if k % v[0] == 0
// D(0,k) = inf, if k % v[0] != 0
// D(i,k) = D(i-1,k), if k < v[i], i > 0
// D(i,k) = min(D(i-1,k), D(i,k-v[i]) + 1), if k >= v[i], i > 0
// 시간 복잡도 O(NC)
// 공간 복잡도 O(NC). 반복적 DP로 O(C) 최적화 가능
static int cache3[MAXC + 1];
int optimal_exchange3(int V[], int n, int C)
{
	int v = V[0];
	for (int i = 0; i <= C; ++i) {
		cache3[i] = (i % v) ? (C + 1) : (i / v);
	}
	for (int i = 1; i < n; ++i) {
		int v = V[i];
		for (int j = v; j <= C; ++j) {
			cache3[j] = min(cache3[j], cache3[j - v] + 1);
		}
	}

	return cache3[C];
}

// 4.
// E(k) = 돈 k를 환전하는 가장 작은 동전의 수
// E(0) = 0
// E(k) = inf, if k < 0
// E(k) = min(E(k - v[i]), for 0 <= i < n) + 1, if k > 0
// 시간 복잡도 O(NC)
// 공간 복잡도 O(C)
static int cache4[MAXC + 1];

void init_cache4()
{
	for (int i = 0; i < MAXN; ++i)
		cache4[i] = -1;
}

int optimal_exchange4(int V[], int n, int C)
{
	if (C < 0)
		return 0x70000000;
	if (cache4[C] >= 0)
		return cache4[C];
	if (C == 0)
		return cache4[0] = 0;
	int m = 0x70000000;
	for (int i = 0; i < n; ++i) {
		m = min(m, optimal_exchange4(V, n, C - V[i]));
	}

	return cache4[C] = m + 1;
}

#define NUMELEM(X) (sizeof(X) / sizeof(int))
int main(int argc, char* argv[])
{
	init_cache4();
	int vs[] = { 5, 2 };
	//int vs[] = { 5, 2 };
	printf("%d\n", exchanges1(vs, NUMELEM(vs), 24));
	printf("%d\n", exchanges2(vs, NUMELEM(vs), 24));
	printf("%d\n", optimal_exchange3(vs, NUMELEM(vs), 24));
	printf("%d\n", optimal_exchange4(vs, NUMELEM(vs), 24));
	return 0;
}
