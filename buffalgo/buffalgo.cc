/*****************************************************************************
*****************************************************************************/
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

int main(int argc, char* argv[])
{
	buffalgo1<int> a(5, 2); // test constructor
	a[2] = 5;
	a = buffalgo1<int>(7, 1); // test assign operator
	a[3] = 7;
	buffalgo1<int> b(a); // test copy constructor
	b[1] = 4;
	a[7] = 9;
	buffalgo2<int> c = buffalgo2<int>::rectangle(3, 4, -1, 1); // test constructor
	c[-1][1] = 5;
	c[1][4] = 10;
	buffalgo2<int> d = c; // test copy constructor
	c = buffalgo2<int>::rectangle(3, 4, -1, 1); // test assign operator
	buffalgo2<int> e = buffalgo2<int>::square(5, 2, -2); // test square
	e[2][-2] = 15;
	e[6][2] = 20;
	int** ptrs = e.get();
	ptrs[3][-2] = 17;
	buffalgo2<int> f = buffalgo2<int>::triangle_upper_left(3, 3, 2);
	f[3][2] = 1;
	f[3][3] = 2;
	f[3][4] = 3;
	f[4][2] = 4;
	f[4][3] = 5;
	f[5][2] = 6;
	buffalgo2<int> g = buffalgo2<int>::triangle_lower_left(3, -3, 2);
	g[-3][2] = 1;
	g[-2][2] = 2;
	g[-2][3] = 3;
	g[-1][2] = 4;
	g[-1][3] = 5;
	g[-1][4] = 6;
	buffalgo2<int> h = buffalgo2<int>::triangle_upper_left(3, 1, -1);
	h[1][-1] = 1;
	h[1][0] = 2;
	h[1][1] = 3;
	h[2][-1] = 4;
	h[2][0] = 5;
	h[3][-1] = 6;
	buffalgo2<int> i = buffalgo2<int>::triangle_lower_right(3, -2, -2);
	i[-2][0] = 1;
	i[-1][-1] = 2;
	i[-1][0] = 3;
	i[0][-2] = 4;
	i[0][-1] = 5;
	i[0][0] = 6;
	return 0;
}
