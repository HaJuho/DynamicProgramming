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

// 상자가 n개 있고, 각각의 높이, 폭, 깊이가 주어진다.
// 상자를 쌓는데 위층의 상자는 아래층 상자보다 폭과 깊이가 각각 더 작아야 한다.
// 쌓은 상자의 최대 높이는?

// 1. 상자를 돌릴 수 없는 경우
// H(i) = i번째 상자를 가장 아래에 두고 쌓을 수 있는 가장 높은 높이
// 시간 복잡도 O(N^2)
// 공간 복잡도 O(N)
static int cache1[MAXN];

void init_cache1()
{
	for (int i = 0; i < MAXN; ++i)
		cache1[i] = 0;
}

int box_stacking1_r(int W[], int D[], int H[], int n, int bottom)
{
	if (cache1[bottom])
		return cache1[bottom];
	int w = W[bottom];
	int d = D[bottom];
	int m = 0;
	for (int i = 0; i < n; ++i) {
		if (W[i] < w && D[i] < d) {
			m = max(m, box_stacking1_r(W, D, H, n, i));
		}
	}
	return cache1[bottom] = m + H[bottom];
}

int box_stacking1(int W[], int D[], int H[], int n)
{
	int h = 0;
	for (int i = 0; i < n; ++i)
		h = max(h, box_stacking1_r(W, D, H, n, i));
	return h;
}

// 2. 상자를 돌릴 수 없는 경우 LIS 응용
// H(i) = i번째 상자를 가장 아래에 두고 쌓을 수 있는 가장 높은 높이
// 시간 복잡도 O(N^2)
// 공간 복잡도 O(N)
struct Box {
	int w;
	int d;
	int h;
};

struct SortBox {
	bool operator()(const Box& a, const Box& b) const {
		return a.w < b.w;
	}
};

static Box boxes2[MAXN];
static int cache2[MAXN];

int box_stacking2(int W[], int D[], int H[], int n)
{
	for (int i = 0; i < n; ++i)
		boxes2[i] = { W[i], D[i], H[i] };
	sort(boxes2, boxes2 + n, SortBox());
	int max_so_far = 0;
	for (int i = 0; i < n; ++i) {
		int w = boxes2[i].w;
		int d = boxes2[i].d;
		int h = 0;
		for (int j = 0; j < i; ++j) {
			if (boxes2[j].d < d && boxes2[j].w < w)
				h = max(h, cache2[j]);
		}
		h += boxes2[i].h;
		cache2[i] = h;
		max_so_far = max(max_so_far, h);
	}
	return max_so_far;
}

// 3. 상자를 돌릴 수 있는 경우
// 상자를 돌려서 여러 번 사용할 수 있다면 최대 6가지의 상자가 된다.
// w <= d가 되도록 강제하면 최대 3가지의 상자가 된다.
// 시간 복잡도 O(N^2) * 9
// 공간 복잡도 O(N) * 3
static Box boxes3[MAXN * 3];
static int cache3[MAXN * 3];

int init_rotated_boxes3(int W[], int D[], int H[], int n)
{
	int idx = 0;
	for (int i = 0; i < n; ++i) {
		int wdh[3] = { W[i], D[i], H[i] };
		sort(wdh, wdh + 3);
		boxes3[idx++] = { wdh[0], wdh[1], wdh[2] };
		while (next_permutation(wdh, wdh + 3)) {
			if (wdh[0] <= wdh[1]) {
				boxes3[idx++] = { wdh[0], wdh[1], wdh[2] };
			}
		}
	}
	//fprintf(stderr, "%d rotated boxes from %d boxes\n", idx, n);
	return idx;
}

int box_stacking3(int W[], int D[], int H[], int n)
{
	int n2 = init_rotated_boxes3(W, D, H, n);
	// 여기부터는 box_stacking2와 같음
	sort(boxes3, boxes3 + n2, SortBox());
	int max_so_far = 0;
	for (int i = 0; i < n2; ++i) {
		int w = boxes3[i].w;
		int d = boxes3[i].d;
		int h = 0;
		for (int j = 0; j < i; ++j) {
			if (boxes3[j].d < d && boxes3[j].w < w)
				h = max(h, cache3[j]);
		}
		h += boxes3[i].h;
		cache3[i] = h;
		max_so_far = max(max_so_far, h);
	}
	return max_so_far;
}

#define NUMELEM(X) (sizeof(X) / sizeof(int))
int main(int argc, char* argv[])
{
	init_cache1();
	int ws[] = { 7, 5, 3, 2, 8, 4, 3, 2, 1, 9 };
	int ds[] = { 4, 7, 1, 2, 7, 3, 2, 4, 5, 7 };
	int hs[] = { 2, 3, 4, 5, 6, 7, 6, 5, 3, 4 };
	printf("%d\n", box_stacking1(ws, ds, hs, NUMELEM(ws)));
	printf("%d\n", box_stacking2(ws, ds, hs, NUMELEM(ws)));
	printf("%d\n", box_stacking3(ws, ds, hs, NUMELEM(ws)));
	return 0;
}
