# 부분 수열의 합 찾기

A[0...n-1]가 자연수의 집합일 때 합이 T인 부분집합이 있는지 찾기

예) A = {11, 17, 45, 3} 일 때, T = 20인 부분 수열 {17, 3}은 찾을 수 있고, T = 21인 부분 수열은 찾을 수 없다.

B(k,t) = A[0...k-1]에서 합인 t인 부분집합이 있는지 여부

```
B(0,0) = true
B(0,t) = false, if t > 0
B(k,t) = B(k-1,t), if t < A[k-1], k > 0
B(k,t) = B(k-1,t) | B(k-1,t-A[k-1]), if t >= A[k-1], k > 0
```

시간복잡도 O(NT)

공간복잡도 O(NT). 반복적 DP로 O(T) 최적화 가능

