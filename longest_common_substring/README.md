# Longest Common Substring

최장 공통 연속 부분 수열

수열 A[0...m-1]와 수열 B[0...n-1]가 있을 때, 두 수열의 공통 연속 부분 수열의 길이의 최대값은?

예) A = {1, 2, 3, 2, 4, 1, 2}, B = {2, 4, 1, 1, 2, 1} 일 때, {2, 4, 1}이 가장 긴 substring이고 길이는 3이다.

C(i,j) = A[0...i-1]와 B[0...j-1]에서 A[i-1], B[j-1]를 각각 포함한 연속 수열의 최대 길이

M(i,j) = A[0...i-1]와 B[0...j-1]에서 최장 공통 부분 연속 수열의 길이

```
C(0,j) = 0
C(i,0) = 0
C(i,j) = 1 + C(i-1,j-1), if A[i-1] == B[j-1], i > 0, j > 0
C(i,j) = 0, if A[i-1] != B[j-1], i > 0, j > 0
M(i,j) = max(C(a,b), for 0 <= a <= i, 0 <= b <= j)
```

시간복잡도 O(NM)

공간복잡도 O(NM). 반복적 DP로 O(N) 또는 O(M) 최적화 가능