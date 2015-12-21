#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <string>

static const int DEN = 1000000007;

static const int MAXN = 3000;
static const int MAXM = 3000;

// n/m partition: n을 m 이하의 자연수의 합으로 나타내는 방법.
// 방법 1
// p(n,m) = p(n,n) for n < m
// p(0,m) = 1
// p(n,m) = p(n-1,1) + p(n-2,2) + ... + p(n-m,m) for n >= m, n > 0
// 시간복잡도 O(NM^2) -> 최적 아님
// 공간복잡도 O(NM)
static int cache1[MAXN + 1][MAXM + 1];

void init_cache1()
{
	for (int i = 0; i <= MAXN; ++i)
		for (int j = 0; j <= MAXM; ++j)
			cache1[i][j] = -1;
}

int number_partition1(int n, int m)
{
	if (n < m)
		m = n;
	if (cache1[n][m] >= 0)
		return cache1[n][m];
	if (n == 0)
		return cache1[n][m] = 1;

	unsigned long long count = 0;
	for (int i = 1; i <= m; ++i)
		count += number_partition1(n - i, i);
	return cache1[n][m] = static_cast<int>(count % DEN);
}

// 방법 2
// p(n,m) = p(n,n) for n < m
// p(0,m) = 1
// p(n,0) = 0
// p(n,m) = p(n,m-1) + p(n-m,m-1) + p(n-2m,m-1) + ... + p(n-km,m-1) for n >= km, n > 0, m > 0, k > 0
// 시간복잡도 O(N^2M) ?? -> 최적 아님
// 공간복잡도 O(NM). Knapsack, CoinExchange 처럼 순차적 DP 사용하면 O(N) 가능
static int cache2[MAXN + 1][MAXM + 1];

void init_cache2()
{
	for (int i = 0; i <= MAXN; ++i)
		for (int j = 0; j <= MAXM; ++j)
			cache2[i][j] = -1;
}

int number_partition2(int n, int m)
{
	if (n < m)
		m = n;
	if (cache2[n][m] >= 0)
		return cache2[n][m];
	if (n == 0)
		return cache2[n][m] = 1;
	if (m == 0)
		return cache2[n][m] = 0;

	unsigned long long count = 0;
	for (int k = 0; k <= n; k += m)
		count += number_partition2(n - k, m - 1);
	return cache2[n][m] = static_cast<int>(count % DEN);
}

// 방법 3
// p(n,m) = p(n,n) for n < m
// p(0,m) = 1
// p(n,0) = 0
// p(n,m) = p(n-m,m) + p(n,m-1) for n >= m, n > 0, m > 0
// 시간복잡도 O(NM)
// 공간복잡도 O(NM). Knapsack, CoinExchange 처럼 순차적 DP 사용하면 O(N) 가능
static int cache3[MAXN + 1][MAXM + 1];

void init_cache3()
{
	for (int i = 0; i <= MAXN; ++i)
		for (int j = 0; j <= MAXM; ++j)
			cache3[i][j] = -1;
}

int number_partition3(int n, int m)
{
	if (n < m)
		m = n;
	if (cache3[n][m] >= 0)
		return cache3[n][m];
	if (n == 0)
		return cache3[n][m] = 1;
	if (m == 0)
		return cache3[n][m] = 0;
	int v = number_partition3(n - m, m) + number_partition3(n, m - 1);
	return cache3[n][m] = v > DEN ? v - DEN : v;
}

#define NUMELEM(X) (sizeof(X) / sizeof(int))
int main()
{
	init_cache1();
	init_cache3();
	init_cache2();
	//int testset[] = { 5, 3, 10, 7, 2, 5, 50, 30, 1000, 1000 };
	int testset[] = { 3000, 3000 };
	for (int i = 0; i < NUMELEM(testset); i += 2) {
		int n = testset[i];
		int m = testset[i + 1];
		printf("%d/%d: %d\n", n, m, number_partition1(n, m));
		printf("%d/%d: %d\n", n, m, number_partition2(n, m));
		printf("%d/%d: %d\n", n, m, number_partition3(n, m));
	}
	return 0;
}
