# Number Partition

n/m partition: n을 m 이하의 자연수의 합으로 나타내는 방법.

예) n=5, m=3 일 때, 5 = 1+1+1+1+1 = 2+1+1+1 = 2+2+1 = 3+1+1 = 3+2 와 같이 5가지 방법으로 나타낼 수 있다.

```
p(n,m) = p(n,n), if n < m
p(0,m) = 1
p(n,0) = 0, if n > 0
p(n,m) = p(n-m,m) + p(n,m-1), if n >= m, n > 0, m > 0
```

시간복잡도 O(NM)

공간복잡도 O(NM). 반복적 DP로 O(N) 최적화 가능
