# Maximum Submaxtrix

행렬 A[0...n-1][0...m-1]의 모든 요소의 값은 양 또는 음의 실수이다.

이 행렬의 부분 행렬 중 모든 요소의 합이 가장 큰 부분 행렬의 크기는? 위치는?

예) 다음 행렬에서 아래 밑줄 친 영역의 합이 12로 최대이다.
    3 -9  1  3
    7 -6  5 -5
    1  9 -4 -1

B(i,j) = A[0...i-1][j]의 모든 요소의 합

C(begin,end,j) = B(end,j) - B(begin,j) 는 A[begin...end-1][j]의 모든 원소의 합이다.

C(begin,end,j)를 이용하여 Maximum Subarray 문제를 풀면

A[begin...end-1][0...m-1]의 최대값을 구할 수 있다.

모든 0 <= begin < end <= n 조합에 대해서 수행하면 전체 Submatrix 중 최대값을 구할 수 있다.

시간복잡도 O(N^3) = O(N) * O(N^2)

공간복잡도 O(N^2) - 누적합 구하기 위해
