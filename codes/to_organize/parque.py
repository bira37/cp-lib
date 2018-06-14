d = {}
ans = []
for it in range(0, 3):
  n = int(input())
  l = [int(j) for j in input().split()]
  aux = {}
  for elem in l:
    if(d.__contains__(elem) == False):
       d[elem] = {}
    d[elem][it] = True
    aux[elem] = True
  ans.append(len(aux))
    
print('{:d} {:d} {:d}'.format(ans[0], ans[1], ans[2]))      
for i in sorted(d):
  print(str(i), end = ' ')

print()
for dic in d:
  if(len(d[dic]) > 1):
    print(str(dic), end = ' ') 
    
print()   
