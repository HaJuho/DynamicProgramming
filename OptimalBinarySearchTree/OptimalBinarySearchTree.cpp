#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cassert>

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

static const int MAXN = 100;

// 0~n-1 까지의 키에 대해 검색 빈도가 F[0...n-1]으로 주어질 때 평균 검색 시간이 최소가 되도록 이진 검색 트리를 만들기
// cost는 각 노드 i에 대해서 (depth(root,i)+1)*F[i] 의 합으로 계산한다.
// C(i,j) = i~j 사이의 키를 사용한 optimal BST의 cost
// C(i,i) = F[i]
// C(i,j) = 0 for i > j
// C(i,j) = min(C(i,k-1) + C(k+1,j) + F[i] + F[i+1] + ... + F[j] for i <= k <= j) for i < j
// Tree를 만들기 위해서는 C(i,j)를 계산할 때마다 R(i,j) = i~j 사이를 사용한 optimal BST의 root를 저장해야 한다.
// 시간 복잡도 O(N^3)
// 공간 복잡도 O(N^2)
struct Node {
	int key;
	Node* left;
	Node* right;
	Node(int _key) : key(_key), left(NULL), right(NULL) {}
	Node(int _key, Node* l, Node* r) : key(_key), left(l), right(r) {}
	~Node() { if (left) delete left; if (right) delete right; }
};

static int acc[MAXN + 1];
static int local_cost[MAXN][MAXN];
static int local_root[MAXN][MAXN];

void updateOptimal(int F[], int n)
{
	acc[0] = 0;
	for (int i = 0; i < n; ++i) {
		acc[i + 1] = acc[i] + F[i];
		local_cost[i][i] = F[i];
		local_root[i][i] = i;
	}
	for (int d = 1; d < n; ++d) {
		for (int i = 0; i < n - d; ++i) {
			int j = i + d;
			int r = i;
			int m = local_cost[i + 1][j];
			for (int k = i + 1; k < j; ++k) {
				int v = local_cost[i][k - 1] + local_cost[k + 1][j];
				if (v < m) {
					m = v;
					r = k;
				}
			}
			int v = local_cost[i][j - 1];
			if (v < m) {
				m = v;
				r = j;
			}
			local_cost[i][j] = m + acc[j + 1] - acc[i];
			local_root[i][j] = r;
		}
	}
}

Node* buildBst(int first, int last)
{
	if (first > last)
		return NULL;
	int r = local_root[first][last];
	return new Node(r, buildBst(first, r - 1), buildBst(r + 1, last));
}

Node* buildOptimalBst(int F[], int n)
{
	updateOptimal(F, n);
	return buildBst(0, n - 1);
}

void printTree(Node* root, int depth, int F[])
{
	if (!root)
		return;
	printTree(root->left, depth + 1, F);
	for (int i = 1; i < depth; ++i)
		printf("  ");
	printf("%d(%d,%d)\n", root->key, depth, F[root->key]);
	printTree(root->right, depth + 1, F);
}

#define NUMELEM(X) (sizeof(X) / sizeof(int))
int main(int argc, char* argv[])
{
	int testset[] = { 1, 2, 3, 4, 5, 6, 7 };
	Node* root = buildOptimalBst(testset, NUMELEM(testset));
	printf("%d\n", local_cost[0][NUMELEM(testset) - 1]);
	printTree(root, 1, testset);
	delete root;
	return 0;
}
