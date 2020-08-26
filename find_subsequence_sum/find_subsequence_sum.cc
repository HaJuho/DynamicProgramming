#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cassert>

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

static const int MAXN = 100;
static const int MAXT = 10000;

// A[0...n-1]가 자연수의 집합일 때 합이 T인 부분집합이 있는지 찾기
// B(k,t) = A[0...k-1]에서 합인 t인 부분집합이 있는지 여부
// B(0,0) = true
// B(0,t) = false, if t > 0
// B(k,t) = B(k-1,t), if t < A[k-1], k > 0
// B(k,t) = B(k-1,t) | B(k-1,t-A[k-1]), if t >= A[k-1], k > 0
// 시간복잡도 O(NT)
// 공간복잡도 O(NT). 반복적 DP로 O(T) 최적화 가능

// 1. 공간 O(NT)
static bool cache1[MAXN + 1][MAXT + 1];

bool find_subsequence_sum1(int A[], int n, int T)
{
	cache1[0][0] = true;
	for (int i = 1; i <= T; ++i)
		cache1[0][i] = false;
	for (int i = 1; i <= n; ++i) {
		int v = A[i - 1];
		for (int j = 0; j < v; ++j)
			cache1[i][j] = cache1[i - 1][j];
		for (int j = v; j <= T; ++j)
			cache1[i][j] = cache1[i - 1][j] | cache1[i - 1][j - v];
	}
	return cache1[n][T];
}

// 2. 공간 O(T)
static bool cache2[MAXT + 1];

bool find_subsequence_sum2(int A[], int n, int T)
{
	cache2[0] = true;
	for (int i = 1; i <= T; ++i)
		cache2[i] = false;
	for (int i = 1; i <= n; ++i) {
		int v = A[i - 1];
		for (int j = T; j >= v; --j)
			cache2[j] |= cache2[j - v];
	}
	return cache2[T];
}

#define NUMELEM(X) (sizeof(X) / sizeof(int))
int main(int argc, char* argv[])
{
	//int testset[] = { 11, 17, 45, 3 };
	int testset[] = { 6, 9, 13, 14, 20, 21, 22, 30, 49, 55 };
	printf("%d\n", find_subsequence_sum1(testset, NUMELEM(testset), 20));
	printf("%d\n", find_subsequence_sum2(testset, NUMELEM(testset), 20));
	printf("%d\n", find_subsequence_sum1(testset, NUMELEM(testset), 18));
	printf("%d\n", find_subsequence_sum2(testset, NUMELEM(testset), 18));
	printf("%d\n", find_subsequence_sum1(testset, NUMELEM(testset), 110));
	printf("%d\n", find_subsequence_sum2(testset, NUMELEM(testset), 110));
	return 0;
}
