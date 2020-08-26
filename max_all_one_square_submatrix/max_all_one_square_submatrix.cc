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

// 행렬 A[0...n-1][0...m-1]의 모든 요소의 값은 0 또는 1이다.
// 이 행렬의 부분 행렬 중 모든 요소가 1인 최대 크기의 정사각 행렬의 크기는?
// B(i,j) = A[0...i][0...j]에서 A[i][j]를 포함하는 가장 큰 정사각 행렬의 크기
// B(0,j) = A[0][j]
// B(i,0) = A[i][0]
// B(i,j) = min(B(i,j-1),B(i-1,j),B(i-1,j-1)) + 1, if A[i][j] == 1, i > 0, j > 0
// B(i,j) = 0, if A[i][j] == 0, i > 0, j > 0
// B(i,j)의 최대값이 최대 정사각 행렬의 변의 길이
// 시간복잡도 O(NM)
// 공간복잡도 O(NM). 반복적 DP로 O(N) 또는 O(M) 최적화 가능

int max_all_one_sqaure_submatrix1(int A[], int n, int m)
{
	buffalgo2<int> b = buffalgo2<int>::rectangle(n, m);

	int max_so_far = 0;
	for (int j = 0; j < m; ++j) {
		b[0][j] = A[j];
		max_so_far = max(max_so_far, A[j]);
	}
	for (int i = 1; i < n; ++i) {
		b[i][0] = A[i * m];
		max_so_far = max(max_so_far, b[i][0]);
		for (int j = 1; j < m; ++j) {
			if (A[i * m + j]) {
				int m = min(b[i - 1][j], b[i][j - 1]);
				b[i][j] = min(m, b[i - 1][j - 1]) + 1;
				max_so_far = max(max_so_far, b[i][j]);
			}
			else
				b[i][j] = 0;
		}
	}
	return max_so_far;
}

#define NUMELEM(X) (sizeof(X) / sizeof(int))
int main(int argc, char* argv[])
{
	//int testset[][7] = {
	//	{ 1, 1, 0, 0, 1, 0, 0 },
	//	{ 0, 1, 1, 1, 1, 1, 1 },
	//	{ 1, 1, 1, 1, 1, 1, 0 },
	//	{ 0, 0, 1, 1, 1, 0, 0 }
	//};
	int testset[][4] = {
		{ 1, 0, 1, 0 },
		{ 0, 1, 0, 1 },
		{ 1, 0, 1, 0 }
	};
	printf("%d\n", max_all_one_sqaure_submatrix1(testset[0], NUMELEM(testset) / NUMELEM(testset[0]), NUMELEM(testset[0])));
	return 0;
}
