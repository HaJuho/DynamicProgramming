# �κ� ������ �� ã��

A[0...n-1]�� �ڿ����� ������ �� ���� T�� �κ������� �ִ��� ã��

��) A = {11, 17, 45, 3} �� ��, T = 20�� �κ� ���� {17, 3}�� ã�� �� �ְ�, T = 21�� �κ� ������ ã�� �� ����.

B(k,t) = A[0...k-1]���� ���� t�� �κ������� �ִ��� ����

```
B(0,0) = true
B(0,t) = false, if t > 0
B(k,t) = B(k-1,t), if t < A[k-1], k > 0
B(k,t) = B(k-1,t) | B(k-1,t-A[k-1]), if t >= A[k-1], k > 0
```

�ð����⵵ O(NT)

�������⵵ O(NT). �ݺ��� DP�� O(T) ����ȭ ����
