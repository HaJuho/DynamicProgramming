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

// Catalan 수 구하기
// C(0) = 1
// C(n) = sum(C(i) * C(n-1-i), for 0 <= i < n), if n > 0
// 시간복잡도 O(N^2)
// 공간복잡도 O(N)

// 1. memoization -> recursion overhead. stack overflow.
static int cache1[MAXN + 1];

void init_cache1()
{
	for (int i = 0; i <= MAXN; ++i)
		cache1[i] = -1;
}

int catalan1(int n)
{
	if (cache1[n] >= 0)
		return cache1[n];
	if (n == 0 || n == 1)
		return cache1[n] = 1;
	long long count = 0;
	for (int i = 0; i < n; ++i) {
		count += static_cast<long long>(catalan1(i)) * catalan1(n - 1 - i);
		count %= DEN;
	}
	return cache1[n] = static_cast<int>(count);
}

// 2. 반복적 DP -> memoization의 초기화 생략 가능.
static int cache2[MAXN + 1];
static int initialized2 = 0;

int catalan2(int n)
{
	if (initialized2 < n) {
		cache2[0] = 1;
		cache2[1] = 1;
		for (int i = max(initialized2 + 1, 2); i <= n; ++i) {
			long long count = 0;
			for (int j = 0; j < i; ++j) {
				count += static_cast<long long>(cache2[j]) * cache2[i - 1 - j];
				count %= DEN;
			}
			cache2[i] = static_cast<int>(count);
		}
		initialized2 = n;
	}
	return cache2[n];
}

int main(int argc, char* argv[])
{
	init_cache1();
	int ns[] = { 4, 0, 10, 1, 2, 3, 14, 16, 18, 20, 3000 };
	for (int n : ns) {
		printf("%d : %d\n", n, catalan1(n));
		printf("%d : %d\n", n, catalan2(n));
	}
	return 0;
}
