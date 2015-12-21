# 최적 Binary Search Tree 만들기

키 0~n-1에 대해 검색 빈도가 F[0...n-1]로 주어질 때 평균 검색 시간이 최소가 되도록 이진 검색 트리를 만들기

cost는 각 노드 i에 대해서 (depth(root,i)+1) * F[i] 의 합으로 계산한다.

C(i,j) = 키 i~j를 사용한 optimal BST의 cost

```
C(i,i) = F[i]
C(i,j) = 0, if i > j
C(i,j) = min(C(i,k-1) + C(k+1,j) + F[i] + F[i+1] + ... + F[j], for i <= k <= j), if i < j
```

Tree를 만들기 위해서는 C(i,j)를 계산할 때마다 R(i,j) = i~j 사이의 optimal BST의 root를 저장해야 한다.

시간 복잡도 O(N^3)

공간 복잡도 O(N^2)
