# Longest Palindrome Substring

최장 회문 부분 연속 수열

Palindrome은 왼쪽에서 읽을 때와 오른쪽에서 읽을 때 같은 문자열(수열)

수열 A[0...n-1]이 있을 때, 최장 회문 부분 연속 수열의 길이는?

B(i,j) = A[i...j]이 회문이면 true, 아니면 false

```
B(i,i) = true
B(i,i+1) = A[i] == A[i+1] ? true : false
B(i,j) = B(i+1,j-1), if A[i] == A[j], i + 1 < j
B(i,j) = false, if A[i] != A[j], i + 1 < j
```

시간 복잡도 O(N^2)

공간 복잡도 O(N^2). 반복적 DP로 O(N) 가능하지만 복잡하다. (triple buffer?)
