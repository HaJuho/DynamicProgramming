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

// 최장 회문 부분 수열
// Palindrome은 왼쪽에서 읽을 때와 오른쪽에서 읽을 때 같은 문자열(수열)
// 수열 A[0...n-1]이 있을 때, 최장 회문 부분 수열의 길이는 ?
// Subsequence는 연속으로 선택할 필요는 없다.
// B(i,j) = A[i...j]에서의 최장 회문 부분 수열
// B(i,i) = 1
// B(i,i+1) = A[i] == A[i+1] ? 2 : 1
// B(i,j) = B(i+1,j-1) + 2, if A[i] == A[j], i + 1 < j
// B(i,j) = max(B(i,j-1), B(i+1,j)), if A[i] != A[j], i + 1 < j
// 시간 복잡도 O(N^2)
// 공간 복잡도 O(N^2). 반복적 DP로 O(N) 가능하지만 복잡하다. (triple buffer?)
static int cache1[MAXN][MAXN];
static int path1[MAXN][MAXN]; // for reconstruction

int longest_palindrome_subseq1(int A[], int n)
{
	cache1[0][0] = 1;
	for (int i = 1; i < n; ++i) {
		cache1[i][i] = 1;
		if (A[i - 1] == A[i]) {
			cache1[i - 1][i] = 2;
			path1[i - 1][i] = 2;
		}
		else {
			cache1[i - 1][i] = 1;
			path1[i - 1][i] = 0;
		}
	}
	for (int d = 2; d < n; ++d) {
		for (int i = 0; i < n - d; ++i) {
			int j = i + d;
			if (A[i] == A[j]) {
				cache1[i][j] = cache1[i + 1][j - 1] + 2;
				path1[i][j] = 2;
			}
			else {
				if (cache1[i][j - 1] > cache1[i + 1][j]) {
					cache1[i][j] = cache1[i][j - 1];
					path1[i][j] = 0;
				}
				else {
					cache1[i][j] = cache1[i + 1][j];
					path1[i][j] = 1;
				}
			}
		}
	}
	return cache1[0][n - 1];
}

void print_palindrome(int A[], int first, int last)
{
	if (first > last)
		return;
	if (first == last) {
		printf("%c", A[first]);
		return;
	}
	int p = path1[first][last];
	if (p == 2) {
		printf("%c", A[first]);
		print_palindrome(A, first + 1, last - 1);
		printf("%c", A[last]);
	}
	else if (p == 0)
		print_palindrome(A, first, last - 1);
	else
		print_palindrome(A, first + 1, last);
}

#define NUMELEM(X) (sizeof(X) / sizeof(int))
int main(int argc, char* argv[])
{
	int testset[] = { 'A', 'G', 'C', 'T', 'C', 'B', 'M', 'A', 'A', 'C', 'T', 'G', 'G', 'A', 'M' };
	printf("%d\n", longest_palindrome_subseq1(testset, NUMELEM(testset)));
	print_palindrome(testset, 0, NUMELEM(testset) - 1); printf("\n");
	return 0;
}
