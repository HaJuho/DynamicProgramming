# Longest Palindrome Subsequence

최장 회문 부분 수열

Palindrome은 왼쪽에서 읽을 때와 오른쪽에서 읽을 때 같은 문자열(수열)

수열 A[0...n-1]에서 최장 회문 부분 수열의 길이는?

Subsequence는 연속으로 선택할 필요는 없다.

B(i,j) = A[i...j]에서의 최장 회문 부분 수열

```
B(i,i) = 1
B(i,i+1) = A[i] == A[i+1] ? 2 : 1
B(i,j) = B(i+1,j-1) + 2, if A[i] == A[j], i + 1 < j
B(i,j) = max(B(i,j-1), B(i+1,j)), if A[i] != A[j], i + 1 < j
```

시간 복잡도 O(N^2)

공간 복잡도 O(N^2). 반복적 DP로 O(N) 가능하지만 복잡하다. (triple buffer?)
