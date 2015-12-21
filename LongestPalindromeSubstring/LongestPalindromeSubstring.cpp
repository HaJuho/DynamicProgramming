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

// 최장 회문 부분 연속 수열
// Palindrome은 왼쪽에서 읽을 때와 오른쪽에서 읽을 때 같은 문자열(수열)
// 수열 A[0...n-1]이 있을 때, 최장 회문 부분 연속 수열의 길이는?
// B(i,j) = A[i...j]이 회문이면 true, 아니면 false
// B(i,i) = true
// B(i,i+1) = A[i] == A[i+1] ? true : false
// B(i,j) = B(i+1,j-1), if A[i] == A[j], i < j
// B(i,j) = false, if A[i] != A[j], i < j
// 시간 복잡도 O(N^2)
// 공간 복잡도 O(N^2). O(N)에 가능하지만 복잡하다. (triple buffer?)
static bool cache1[MAXN][MAXN];

int longest_palindrome_substring1(int A[], int n)
{
	int max_so_far = 1;
	cache1[0][0] = true;
	for (int i = 1; i < n; ++i) {
		cache1[i][i] = true;
		if (A[i - 1] == A[i]) {
			cache1[i - 1][i] = true;
			max_so_far = 2;
		}
		else
			cache1[i - 1][i] = false;
	}
	for (int d = 2; d < n; ++d) {
		for (int i = 0; i < n - d; ++i) {
			int j = i + d;
			if (A[i] == A[j] && cache1[i + 1][j - 1]) {
				cache1[i][j] = true;
				max_so_far = d + 1;
			}
			else
				cache1[i][j] = false;
		}
	}
	return max_so_far;
}

#define NUMELEM(X) (sizeof(X) / sizeof(int))
int main(int argc, char* argv[])
{
	int testset[] = { 'A', 'G', 'C', 'T', 'C', 'B', 'M', 'A', 'A', 'C', 'T', 'G', 'G', 'A', 'M' };
	printf("%d\n", longest_palindrome_substring1(testset, NUMELEM(testset)));
	return 0;
}
