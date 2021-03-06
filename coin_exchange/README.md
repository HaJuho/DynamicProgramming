# 동전 환전

1. 가격 C를 n개의 동전 v[0...n-1]로 환전하는 방법의 수는?

수분할과 비슷하게 풀어도 된다.

B(i,k) = 동전 v[0...i]를 사용해 가격 k를 환전하는 방법의 수

```
B(0,k) = 1, if k % v[0] == 0
B(0,k) = 0, if k % v[0] != 0
B(i,k) = B(i-1,k), if k < v[i], i > 0
B(i,k) = B(i-1,k) + B(i,k-v[i]), if k >= v[i], i > 0
```

시간 복잡도 O(NC)

공간 복잡도 O(NC). 반복적 DP로 O(C) 최적화 가능

2. 최적 환전

가장 적은 수의 동전으로 환전하기. 배낭 문제와 같다?

D(i,k) = 동전 v[0...i]를 사용해 돈 k를 환전하는 가장 작은 동전의 수

```
D(0,k) = k / v[0], if k % v[0] == 0
D(0,k) = inf, if k % v[0] != 0
D(i,k) = D(i-1,k), if k < v[i], i > 0
D(i,k) = min(D(i-1,k), D(i,k-v[i]) + 1), if k >= v[i], i > 0
```

시간 복잡도 O(NC)

공간 복잡도 O(NC). 반복적 DP로 O(C) 최적화 가능

또는

E(k) = 돈 k를 환전하는 가장 작은 동전의 수

```
E(0) = 0
E(k) = inf, if k < 0
E(k) = min(E(k - v[i]), for 0 <= i < n) + 1, if k > 0
```

시간 복잡도 O(NC)

공간 복잡도 O(C)
