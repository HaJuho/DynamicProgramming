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
static const int MAXM = 1000;

static const int CR = 1;
static const int CI = 1;
static const int CD = 1;

// 문자열 A[0...n-1]과 B[0...m-1]이 주어질 때, 문자열 A를 B로 변경하는 최소 비용은?
// 각 문자의 치환, 삽입, 삭제에 따른 비용이 CR, CI, CD로 주어진다.
// C(i,j) = A[0...i-1]을 B[0...j-1]로 변경할 때의 최소 비용
// C(0,0) = 0
// C(0,j) = C(0,j-1) + CI = j * CI, if j > 0
// C(i,0) = CD + C(i-1,0) = i * CD, if i > 0
// C(i,j) = min(CD+C(i-1,j), C(i,j-1)+CI, C(i-1,j-1)), if A[i-1] == B[j-1], i > 0, j > 0
// C(i,j) = min(CD+C(i-1,j), C(i,j-1)+CI, C(i-1,j-1)+CR), if A[i-1] != B[j-1], i > 0, j > 0
// 시간 복잡도 O(NM)
// 공간 복잡도 O(NM). 반복적 DP로 O(M) 또는 O(N) 최적화 가능

// 1. 공간 O(NM)
int cache1[MAXN + 1][MAXM + 1];

int edit_distance1(char* A, int n, char* B, int m)
{
	cache1[0][0] = 0;
	for (int i = 1; i <= m; ++i)
		cache1[0][i] = cache1[0][i - 1] + CI;
	for (int i = 1; i <= n; ++i) {
		cache1[i][0] = CD + cache1[i - 1][0];
		for (int j = 1; j <= m; ++j) {
			int m = cache1[i - 1][j - 1];
			if (A[i - 1] != B[j - 1])
				m += CR;
			m = min(m, CD + cache1[i - 1][j]);
			cache1[i][j] = min(m, cache1[i][j - 1] + CI);
		}
	}
	return cache1[n][m];
}

// 2. 공간 O(M)
int cache2[2][MAXM + 1];

int edit_distance2(char* A, int n, char* B, int m)
{
	int* cur = cache2[0];
	int* prev = cache2[1];
	cur[0] = 0;
	for (int i = 1; i <= m; ++i)
		cur[i] = cur[i - 1] + CI;
	for (int i = 1; i <= n; ++i) {
		swap(cur, prev);
		cur[0] = CD + prev[0];
		for (int j = 1; j <= m; ++j) {
			int m = prev[j - 1];
			if (A[i - 1] != B[j - 1])
				m += CR;
			m = min(m, CD + prev[j]);
			cur[j] = min(m, cur[j - 1] + CI);
		}
	}
	return cur[m];
}

#define NUMELEM(X) (sizeof(X) / sizeof(char))
int main(int argc, char* argv[])
{
	char testa[] = "abcde";
	char testb[] = "bxdfe";
	printf("%d\n", edit_distance1(testa, NUMELEM(testa), testb, NUMELEM(testb)));
	printf("%d\n", edit_distance2(testa, NUMELEM(testa), testb, NUMELEM(testb)));
	return 0;
}
