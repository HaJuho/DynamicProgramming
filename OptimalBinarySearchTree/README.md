# ���� Binary Search Tree �����

Ű 0~n-1�� ���� �˻� �󵵰� F[0...n-1]�� �־��� �� ��� �˻� �ð��� �ּҰ� �ǵ��� ���� �˻� Ʈ���� �����

cost�� �� ��� i�� ���ؼ� (depth(root,i)+1) * F[i] �� ������ ����Ѵ�.

C(i,j) = Ű i~j�� ����� optimal BST�� cost

```
C(i,i) = F[i]
C(i,j) = 0, if i > j
C(i,j) = min(C(i,k-1) + C(k+1,j) + F[i] + F[i+1] + ... + F[j], for i <= k <= j), if i < j
```

Tree�� ����� ���ؼ��� C(i,j)�� ����� ������ R(i,j) = i~j ������ optimal BST�� root�� �����ؾ� �Ѵ�.

�ð� ���⵵ O(N^3)

���� ���⵵ O(N^2)
