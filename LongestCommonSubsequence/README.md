# Longest Common Subsequence

최장 공통 부분 수열

수열 A[0...m-1]과 수열 B[0...n-1]이 있을 때, 두 수열의 공통 부분 수열의 길이의 최대값은?

Subsequence는 연속으로 선택할 필요는 없다.

LCS는 여럿이 있을 수 있다.

LCS(i,j) = A[0...i-1]와 B[0...j-1] 사이의 LCS 길이

```
LCS(0,j) = 0
LCS(i,0) = 0
LCS(i,j) = 1 + LCS(i-1,j-1), if A[i-1] == B[j-1], i > 0, j > 0
LCS(i,j) = max(LCS(i-1,j), LCS(i,j-1)), if A[i-1] != B[j-1], i > 0, j > 0
```

시간복잡도 O(NM)

공간복잡도 O(NM). 반복적 DP로 O(N) 또는 O(M) 최적화 가능
