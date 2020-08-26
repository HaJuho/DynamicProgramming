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

// Fibonacci 수열 구하기
// F(0) = 0
// F(1) = 1
// F(n) = F(n-1) + F(n-2), if n > 1
// 시간복잡도 O(N)
// 공간복잡도 O(N). 반복적 DP로 O(1) 최적화 가능

// 1. memoization -> recursion overhead. stack overflow.
static int cache1[MAXN + 1];

void init_cache1()
{
	for (int i = 0; i <= MAXN; ++i)
		cache1[i] = -1;
}

int fibonacci1(int n)
{
	if (cache1[n] >= 0)
		return cache1[n];
	if (n == 0)
		return cache1[0] = 0;
	if (n == 1)
		return cache1[1] = 1;
	int v = fibonacci1(n - 1) + fibonacci1(n - 2);
	return cache1[n] = v > DEN ? v - DEN : v;
}

// 2. 반복적 DP -> 공간 절약. 또는 직접 계산??. 여러 번 호출한다면 cache하는 것이 좋을 수도...
int fibonacci2(int n)
{
	if (n == 0)
		return 0;
	int fn1 = 1;
	int fn2 = 0;
	for (int i = 2; i <= n; ++i) {
		int fn = fn1 + fn2;
		fn = fn > DEN ? fn - DEN : fn;
		fn2 = fn1;
		fn1 = fn;
	}
	return fn1;
}

int main(int argc, char* argv[])
{
	init_cache1();

	int ns[] = { 4, 0, 10, 1, 2, 5, 3, 60, 80, 100, 1000 };
	for (int n : ns) {
		printf("%d : %d %d\n", n, fibonacci1(n), fibonacci2(n));
	}
	return 0;
}
