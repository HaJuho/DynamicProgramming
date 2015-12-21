# Longest Increasing Subsequence

최장 증가 부분 수열

수열 A[0...n-1]에서 증가하는 부분 수열의 길이의 최대값은?

Subsequence는 연속으로 선택할 필요는 없다.

B(k) = A[0...k]에서 A[k]로 끝나는 최장 부분 수열의 길이

```
B(0) = 1
B(k) = max(0, max(B(i), for 0 <= i < k, A[i] < A[k])) + 1, if k > 0
LIS(k) = max(B(i), for 0 <= i <= k)
```

시간복잡도 O(N^2)

공간복잡도 O(N)
