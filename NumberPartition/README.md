# Number Partition

n/m partition: n�� m ������ �ڿ����� ������ ��Ÿ���� ���.

```
p(n,m) = p(n,n), if n < m
p(0,m) = 1
p(n,0) = 0, if n > 0
p(n,m) = p(n-m,m) + p(n,m-1), if n >= m, n > 0, m > 0
```

�ð����⵵ O(NM)

�������⵵ O(NM). �ݺ��� DP�� O(N) ����ȭ ����
