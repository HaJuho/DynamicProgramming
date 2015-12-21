#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cassert>

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

static const int MAXN = 1000;

// 최장 증가 부분 수열
// 수열 A[0...n-1]에서 증가하는 부분 수열의 길이의 최대값은?
// Subsequence는 연속으로 선택할 필요는 없다.
// B(k) = A[0...k]에서 A[k]로 끝나는 최장 부분 수열의 길이
// B(0) = 1
// B(k) = max(0, max(B(i), for 0 <= i < k, A[i] < A[k])) + 1, if k > 0
// LIS(k) = max(B(i), for 0 <= i <= k)
// 시간복잡도 O(N^2)
// 공간복잡도 O(N)

// 1. 공간 O(N)
static int cache1[MAXN];

int lis1(int A[], int n)
{
	int lis = 0;
	for (int i = 0; i < n; ++i) {
		int m = 0;
		for (int j = 0; j < i; ++j) {
			if (A[j] < A[i] && m < cache1[j]) // A[i] <= A[j]로 바꾸면??
				m = cache1[j];
		}
		++m;
		cache1[i] = m;
		lis = max(lis, m);
	}
	return lis;
}

#define NUMELEM(X) (sizeof(X) / sizeof(int))
int main(int argc, char* argv[])
{
	int testset[] = { 1, 2, 3, 2, 4, 1, 2 };
	//int testset[] = { 1, 0, 4, 3, 5, 7, 6 };
	//int testset[] = { 5, 4, 3, 3, 1 };
	//int testset[] = { 2, 4, 3, 1, 2, 1 };
	printf("%d\n", lis1(testset, NUMELEM(testset)));

	return 0;
}
