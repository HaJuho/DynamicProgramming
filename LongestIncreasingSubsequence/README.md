# Longest Increasing Subsequence

���� ���� �κ� ����

���� A[0...n-1]���� �����ϴ� �κ� ������ ������ �ִ밪��?

Subsequence�� �������� ������ �ʿ�� ����.

B(k) = A[0...k]���� A[k]�� ������ ���� �κ� ������ ����

```
B(0) = 1
B(k) = max(0, max(B(i), for 0 <= i < k, A[i] < A[k])) + 1, if k > 0
LIS(k) = max(B(i), for 0 <= i <= k)
```

�ð����⵵ O(N^2)

�������⵵ O(N)
