﻿#include <cstdio>
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

// 텍스트 A[0...n-1]와 패턴 P[0...m-1]가 주어질 때 A에서 패턴 P를 찾을 수 있는가?
// 패턴 P에 와일드 카드 '*'와 '?'이 포함될 수 있다.
// C(i,j) = A[0...i]와 P[0...j]가 매칭되는지 여부
// C(-1,-1) = true
// C(i,-1) = false, if i >= 0
// C(-1,j) = C(-1,j-1) && P[j] == '*', if j >= 0
// C(i,j) = C(i-1,j-1), if (A[i] == P[j] || P[j] == '?'), i >= 0, j >= 0
// C(i,j) = C(i-1,j) | C(i,j-1), if P[j] == '*', i >= 0, j >= 0
// C(i,j) = false, if A[i] != P[j], P[j] != '?', P[j] != '*', i >= 0, j >= 0
// 시간 복잡도 O(NM)
// 공간 복잡도 O(NM). 반복적 DP로 O(M) 최적화 가능
bool wildcard_matching1(char* A, char* P)
{
	int n = strlen(A);
	int m = strlen(P);
	buffalgo2<bool> b = buffalgo2<bool>::rectangle(n + 1, m + 1, -1, -1);
	bool** c = b.get();
	c[-1][-1] = true;
	for (int j = 0; j < m; ++j)
		c[-1][j] = c[-1][j - 1] & (P[j] == '*');
	for (int i = 0; i < n; ++i) {
		c[i][-1] = false;
		for (int j = 0; j < m; ++j) {
			if (A[i] == P[j] || P[j] == '?')
				c[i][j] = c[i - 1][j - 1];
			else if (P[j] == '*')
				c[i][j] = c[i - 1][j] | c[i][j - 1];
			else
				c[i][j] = false;
		}
	}
	
	return c[n - 1][m - 1];
}

int main(int argc, char* argv[])
{
	char* testA = "hello";
	char* testB = "*o";

	printf("%s %s %d\n", testA, testB, wildcard_matching1(testA, testB));

	return 0;
}
