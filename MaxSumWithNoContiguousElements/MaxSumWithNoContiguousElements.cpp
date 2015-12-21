#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cassert>

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

#define SELECT_AT_LEAST_ONE

static const int MAXN = 10000;

// A[0...n-1]에서 뽑은 요소들 합의 최대값은?
// 단 연속된 두 요소는 선택하지 않음.
// M(k) = A[0...k]의 연속이 아닌 부분 수열의 합의 최대값
// M(0) = A[0]
// M(1) = max(A[1],M(0))
// M(k) = max(A[k], A[k] + M(k-2), M(k-1))
// 시간복잡도 O(N)
// 공간복잡도 O(N). 반복적 DP로 O(1) 최적화 가능

// 1. 공간 O(N)
static int cache1[MAXN];

int max_sum_with_no_contiguous_elements1(int A[], int n)
{
#ifdef SELECT_AT_LEAST_ONE
	cache1[0] = A[0];
#else
	cache1[0] = max(A[0], 0);
#endif
	if (n > 1)
		cache1[1] = max(A[1], cache1[0]);
	for (int i = 2; i < n; ++i) {
		cache1[i] = max(A[i] + cache1[i - 2], cache1[i - 1]);
#ifdef SELECT_AT_LEAST_ONE
		cache1[i] = max(A[i], cache1[i]);
#endif
	}
	return cache1[n - 1];
}

// 2. 공간 O(1)
// TODO ...

#define NUMELEM(X) (sizeof(X) / sizeof(int))
int main(int argc, char* argv[])
{
	int testset[] = { 10, 1, 1, 7, 9, 5, 1, -9 };
	//int testset[] = { -5, -4, -3, -1, -2, -2, -3, -4, -5 };
	printf("%d\n", max_sum_with_no_contiguous_elements1(testset, NUMELEM(testset)));
	return 0;
}
