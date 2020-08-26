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

// F(n) = n!
// F(1) = 1
// F(n) = n * F(n-1), if n > 1
// 시간복잡도 O(N)
// 공간복잡도 O(N). 반복적 DP로 O(1) 최적화 가능

// 1. memoization -> recursion overhead. stack overflow.
static int cache1[MAXN + 1];

void init_cache1()
{
	for (int i = 0; i <= MAXN; ++i)
		cache1[i] = -1;
}

int factorial1(int n)
{
	if (cache1[n] >= 0)
		return cache1[n];
	if (n == 1)
		return cache1[n] = 1;
	long long v = static_cast<long long>(n) * factorial1(n - 1);
	return cache1[n] = static_cast<int>(v % DEN);
}

// 2. 반복적 DP -> 공간 절약. 또는 직접 계산??. 여러 번 호출한다면 cache하는 것이 좋을 수도...
int factorial2(int n)
{
	long long f = 1;
	for (int i = 1; i <= n; ++i) {
		f *= i;
		f %= DEN;
	}
	return static_cast<int>(f);
}

int main(int argc, char* argv[])
{
	init_cache1();
	int ns[] = { 4, 0, 10, 1, 2, 12, 14, 16, 18, 20, 4000 };
	for (int n : ns) {
		printf("%d : %d %d\n", n, factorial1(n), factorial2(n));
	}
	return 0;
}
