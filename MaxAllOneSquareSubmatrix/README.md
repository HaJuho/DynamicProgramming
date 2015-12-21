# Maximum All One Square Submatrix

행렬 A[0...n-1][0...m-1]의 모든 요소의 값은 0 또는 1이다.

이 행렬의 부분 행렬 중 모든 요소가 1인 최대 크기의 정사각 행렬의 크기는?

B(i,j) = A[0...i][0...j] 에서 A[i][j]을 포함하는 가장 큰 정사각 행렬의 크기

B(0,j) = A[0][j]

B(i,0) = A[i][0]

B(i,j) = min(B(i,j-1),B(i-1,j),B(i-1,j-1)) + 1, if A[i][j]==1

B(i,j) = 0, otherwise

B(i,j)의 최대값이 최대 정사각 행렬의 변의 길이
