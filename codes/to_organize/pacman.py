n,m = input().split()
n = int(n)
m = int(m)
ans = []
for i in range(0, n):
  v = [int(j) for j in input().split()]
  
  if(i%2 == 1):
    v.reverse()
  
  for x in v:
    if(x > 0):
      ans.append(x)
    elif(x < 0):
      x = abs(x)
      while (x > 0 and len(ans) > 0):
        ans.pop()
        x = x - 1
  
        
print(sum(ans))
