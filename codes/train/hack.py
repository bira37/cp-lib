def f(s,n):
  if s == 0:
    return 1
  if n == 0 and s != 0:
    return 0
  if L[n-1] > s:
    return f(s, n-1)
  return f(s, n-1) or f(s - L[n-1], n-1)

R = lambda: map(int, input().split())
n = int(input())
L = []
for i in range(n):
  L.append(int(input()))
s = sum(L)
if s%2:
  print("NO")
elif s % 360 == 0:
  print("YES")
else:
  s1 = s//2
  if f(s1, n):
    print("YES")
  else:
    print("NO")
