# Matrix Chain Multiplication

행렬의 곱 비용 최소화

행렬의 곱을 구할 때 최소 (스칼라) 곱셈의 회수는 ?

행렬 A_0 x A_1 x … x A_n-1 을 계산할 때 각 행렬 A_i의 행의 수는 a[i], 열의 수는 a[i+1]로 주어진다.

p x q 행렬과 q x r 행렬을 곱하면 스칼라 곱셈의 회수는 p*q*r이다.

B(i,j) = A_i ~ A_j 곱할 때의 최소 곱셈의 회수

```
B(i,i) = 0
B(i,j) = min(B(i,k) + B(k+1,j) + a[i] * a[k+1] * a[j+1], for i <= k < j), if i < j
```

시간 복잡도 O(N^3)

공간 복잡도 O(N^2)
