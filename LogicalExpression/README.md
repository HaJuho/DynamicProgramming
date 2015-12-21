# 논리식 조합 수

true, false, and, or, xor로 구성된 식의 값이 참이 되도록 만드는 방법의 수는?

A[0..n]에 true, false가 주어짐

B[0..n-1]에 연산자가 주어짐

T(i,j) = A[i...j] 까지를 계산하여 true로 만드는 방법의 수

F(i,j) = A[i...j] 까지를 계산하여 false로 만드는 방법의 수

L(i,j) = T(i,j) + F(i,j)

```
T(i,i) = A[i] == true ? 1 : 0
F(i,i) = A[i] == false ? 0 : 1
T(i,j) = sum(T(i,k) * T(k+1,j), for i <= k < j, B[k] == 'and')
       + sum(L(i,k) * L(k+1,j) - F(i,k) * F(k+1,j), for i <= k < j, B[k] == 'or')
       + sum(T(i,k) * F(k+1,j) + F(i,k) * T(k+1,j), for i <= k < j, B[k] == 'xor'), if i < j
F(i,j) = sum(F(i,k) * F(k+1,j), for i <= k < j, B[k] == 'or')
       + sum(L(i,k) * L(k+1,j) - T(i,k) * T(k+1,j), for i <= k < j, B[k] == 'and')
       + sum(T(i,k) * F(k+1,j) + F(i,k) * T(k+1,j), for i <= k < j, B[k] == 'xor'), if i < j
```

시간 복잡도 O(N^3)

공간 복잡도 O(N^2)
