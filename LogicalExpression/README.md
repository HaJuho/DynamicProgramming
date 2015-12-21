# ���� ���� ��

true, false, and, or, xor�� ������ ���� ���� ���� �ǵ��� ����� ����� ����?

A[0..n]�� true, false�� �־���

B[0..n-1]�� �����ڰ� �־���

T(i,j) = A[i...j] ������ ����Ͽ� true�� ����� ����� ��

F(i,j) = A[i...j] ������ ����Ͽ� false�� ����� ����� ��

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

�ð� ���⵵ O(N^3)

���� ���⵵ O(N^2)
