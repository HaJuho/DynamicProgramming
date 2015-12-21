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

// 0에서 n-1까지의 각 위치에서 점프할 수 있는 최대 거리가 A[0...n-1]로 주어진다.
// 0번 위치에서 n번 위치까지 가기 위한 최소의 점프 회수는?
// B(k) = k 위치에 도달하기 위해 필요한 최소 점프 회수
// B(0) = 0
// B(k) = min(B(i), for 0 <= i < k, k - i <= A[i]) + 1, if k > 0
// 시간 복잡도 O(N^2)
// 공간 복잡도 O(N)
static int cache1[MAXN + 1];
int min_jumps1(int A[], int n)
{
	cache1[0] = 0;
	for (int i = 1; i <= n; ++i) {
		int m = 0x70000000;
		for (int j = 0; j < i; ++j) {
			if (i - j <= A[j] && cache1[j] < m)
				m = cache1[j];
		}
		cache1[i] = m + 1;
	}
	return cache1[n];
}

#define NUMELEM(X) (sizeof(X) / sizeof(int))
int main(int argc, char* argv[])
{
	int testset[] = { 2, 3, 1, 1, 4 };
	printf("%d\n", min_jumps1(testset, NUMELEM(testset)));

	return 0;
}
