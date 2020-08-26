#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cassert>

#include <iostream>
#include <string>
#include <algorithm>

#include "buffalgo.h"

using namespace std;
using namespace juho;

// 각 격자를 지날 때마다 얻는 이익의 값 A[0...n-1][0...m-1]가 주어진다.
// 격자의 (0,0)에서 (n-1, m-1)까지 갈 때 얻을 수 있는 최대 이익은?
// 격자를 다음과 같이 갈 수 있다.
// 오른쪽과 아래쪽으로만 진행 가능
// 장애물이 있을 때 (장애물의 이익 값은 -1)
// 대각선으로도 갈 수 있음
// B(i,j) = (0,0)에서 (i,j)까지 갈 때 얻을 수 있는 최대 이익
// B(0,0) = A[0][0]
// B(0,j) = B(0,j-1) < 0 || A[0][j] < 0 ? -1 : B(0,j-1) + A[0][j], if j > 0
// B(i,0) = B(i-1,0) < 0 || A[i][0] < 0 ? -1 : B(i-1,0) + A[i][0], if i > 0
// B(i,j) = -1, if A[i][j] < 0, i > 0, j > 0
// B(i,j) = -1, if B(i-1,j) < 0, B(i,j-1) < 0, B(i-1,j-1) < 0, i > 0, j > 0
// B(i,j) = max(B(i-1,j), B(i,j-1), B(i-1,j-1)) + A[i][j], if A[i][j] >= 0, max(B(i-1,j), B(i,j-1), B(i-1,j-1)) >= 0
// 시간복잡도 O(NM)
// 공간복잡도 O(NM). 반복적 DP로 O(N) 또는 O(M) 최적화 가능
int max_profit_path1(int A[], int n, int m)
{
	buffalgo2<int> cache = buffalgo2<int>::rectangle(n, m);
	cache[0][0] = A[0];
	for (int i = 1; i < m; ++i)
		cache[0][i] = (A[i] < 0 || cache[0][i - 1] < 0) ? -1 : cache[0][i - 1] + A[i];
	for (int i = 1; i < n; ++i) {
		cache[i][0] = (A[i * m] < 0 || cache[i - 1][0] < 0) ? -1 : cache[i - 1][0] + A[i * m];
		for (int j = 1; j < m; ++j) {
			if (A[i * m + j] < 0)
				cache[i][j] = -1;
			else {
				int c = max(cache[i - 1][j], cache[i][j - 1]);
				//c = max(c, cache[i - 1][j - 1]); // 대각선으로 갈 수 있을 때만
				if (c < 0)
					cache[i][j] = -1;
				else
					cache[i][j] = c + A[i * m + j];
			}
		}
	}
	return cache[n - 1][m - 1];
}

#define NUMELEM(X) (sizeof(X) / sizeof(int))
int main(int argc, char* argv[])
{
	int testset[][4] = {
		{ 3, -9, 1, 3 },
		{ 7, 6, 5, -5 },
		{ 1, 9, 4, 2 }
	};
	//int testset[][4] = {
	//	{ -7, -8, -6, -3 },
	//	{ -4, -6, -5, -5 },
	//	{ -2, -9, -4, -3 }
	//};
	printf("%d\n", max_profit_path1(testset[0], NUMELEM(testset) / NUMELEM(testset[0]), NUMELEM(testset[0])));
	return 0;
}
