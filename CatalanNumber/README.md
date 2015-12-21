# Catalan 수 구하기

```
C(0) = 1
C(n) = sum(C(i) * C(n-1-i), for 0 <= i < n), if n > 0
```

시간복잡도 O(N^2)

공간복잡도 O(N)
