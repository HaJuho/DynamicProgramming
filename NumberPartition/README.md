# Number Partition

n/m partition: n을 m 이하의 자연수의 합으로 나타내는 방법.

```
p(n,m) = p(n,n), if n < m
p(0,m) = 1
p(n,0) = 0, if n > 0
p(n,m) = p(n-m,m) + p(n,m-1), if n >= m, n > 0, m > 0
```

시간복잡도 O(NM)

공간복잡도 O(NM). 반복적 DP로 O(N) 최적화 가능
