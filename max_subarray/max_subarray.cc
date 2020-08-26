#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <string>

using namespace std;

#define SELECT_AT_LEAST_ONE

static const int MAXN = 10000;

// A[0...n-1]에서 연속 부분 수열의 합의 최대값 구하기
// 방법 1
// M(k) = 수열 A[0...k]의 연속부분수열의 합 중 최대
// B(k) = A[0...k]에서 A[k]를 포함하는 연속부분수열의 합 중 최대
// B(0) = A[0]
// B(k) = max(A[k]+B(k-1), A[k]), if k > 1
// M(k) = max(B(i), for 0 <= i <= k)
// 시간복잡도 O(N)
// 공간복잡도 O(N). 반복적 DP로 O(1) 최적화 가능.
static int cache1[MAXN];

int max_subarray1(int A[], int n)
{
	// caching
#ifdef SELECT_AT_LEAST_ONE
	cache1[0] = A[0];
#else
	cache1[0] = max(A[0], 0); // cache1 >= 0
#endif
	for (int i = 1; i < n; ++i)
#ifdef SELECT_AT_LEAST_ONE
		cache1[i] = max(A[i] + cache1[i - 1], A[i]);
#else
		cache1[i] = max(A[i] + cache1[i - 1], 0); // cache1 >= 0
#endif

	return *max_element(cache1, cache1 + n);
}

// 방법 2
// 방법1과 다르지 않음. B(k)를 cache에 저장하지 않고 바로 M(k)를 계산하는 방식임.
// 최소 하나의 원소를 고르는 방식일 때 조금 헷갈림.
// 시간복잡도 O(N)
// 공간복잡도 O(1)
int max_subarray2(int s[], int n)
{
#ifdef SELECT_AT_LEAST_ONE
	int max_so_far = 0x80000000;
#else
	int max_so_far = 0;
#endif
	int sum_ending_here = 0;
	for (int i = 0; i < n; ++i) {
		sum_ending_here += s[i];
#ifdef SELECT_AT_LEAST_ONE
		sum_ending_here = max(sum_ending_here, s[i]);
#else
		sum_ending_here = max(sum_ending_here, 0);
#endif
		max_so_far = max(max_so_far, sum_ending_here);
	}
	return max_so_far;
}

#define NUMELEM(X) (sizeof(X) / sizeof(int))
int main()
{
	//int testset[] = {33, 36, -73, 15, 43, -17, 36, -28, -1, 21};
	//int testset[] = {20, 30, -70, 15, 40};
	//int testset[] = {-5, -4, -3, -2, -1, -2, -3, -4, -5};
	//int testset[] = {-1, -4, -3, -2, -1, -2, -3, -4, -5};
	//int testset[] = { -1 };
	int testset[] = { -1, 2 };

	int mval1 = max_subarray1(testset, NUMELEM(testset));
	int mval2 = max_subarray2(testset, NUMELEM(testset));
	printf("%d %d\n", mval1, mval2);

	return 0;
}
