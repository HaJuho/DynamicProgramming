#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cassert>

#include <iostream>
#include <string>
#include <algorithm>

#include "buffalgo.hpp"

using namespace std;
using namespace juho;

#define SELECT_AT_LEAST_ONE

// 행렬 A[0...n-1][0...m-1]의 모든 요소의 값은 양 또는 음의 실수이다.
// 이 행렬의 부분 행렬 중 모든 요소의 합이 가장 큰 부분 행렬의 크기는 ? 위치는 ?
// B(i,j) = A[0...i-1][j]의 모든 요소의 합
// 시작 row가 begin, 마지막 row가 end-1인 경우
// C(begin,end,j) = B(end,j) - B(begin,j) 는 A[begin...end-1][j]의 모든 원소의 합이다.
// C(begin,end,j)를 이용하여 Maximum Subarray 문제를 풀면
// A[begin...end-1][0...m-1]의 최대값을 구할 수 있다.
// 모든 0<=begin<end<=n 조합에 대해서 수행하면 전체 Submatrix 중 최대값을 구할 수 있다.
// 시간복잡도 O(N^3) - O(N) * O(N^2)
// 공간복잡도 O(N^2) - 누적합 구하기 위해.

int max_submatrix1(int A[], int n, int m)
{
	buffalgo2<int> b = buffalgo2<int>::rectangle(n + 1, m);
	for (int i = 0; i < m; ++i)
		b[0][i] = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
			b[i + 1][j] = b[i][j] + A[i * m + j];
	}
#ifdef SELECT_AT_LEAST_ONE
	int max_so_far = 0x80000000;
#else
	int max_so_far = 0;
#endif
	for (int begin = 0; begin < n; ++begin) {
		for (int end = begin + 1; end <= n; ++end) {
			// max_subarray for [begin, end-1]
			int sum_ending_here = 0;
			for (int j = 0; j < m; ++j) {
				int s = b[end][j] - b[begin][j];
				sum_ending_here += s;
#ifdef SELECT_AT_LEAST_ONE
				sum_ending_here = max(sum_ending_here, s);
#else
				sum_ending_here = max(sum_ending_here, 0);
#endif
				max_so_far = max(max_so_far, sum_ending_here);
			}
		}
	}
	return max_so_far;
}

#define NUMELEM(X) (sizeof(X) / sizeof(int))
int main(int argc, char* argv[])
{
	int testset[][4] = {
		{ 3, -9, 1, 3},
		{ 7, -6, 5, -5 },
		{ 1, 9, -4, -1 }
	};
	//int testset[][4] = {
	//	{ -7, -8, -6, -3 },
	//	{ -4, -6, -5, -5 },
	//	{ -2, -9, -4, -3 }
	//};
	printf("%d\n", max_submatrix1(testset[0], NUMELEM(testset) / NUMELEM(testset[0]), NUMELEM(testset[0])));
	return 0;
}
