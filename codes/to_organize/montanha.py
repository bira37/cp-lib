from collections import deque

n,m,x = [int(i) for i in input().split()]

dq1 = deque()
dq2 = deque()
for i in range(0, n):
  jid, jm = [int(i) for i in input().split()]
  if(jm < x):
    continue
  dq1.append(jid)
  dq2.append(jm)
  
while(m > 0 and len(dq1) > 0):
  m -= 1
  
  jid = dq1.popleft()
  jm = dq2.popleft()
  
  jm -= x
  if(jm >= x):
    dq1.append(jid)
    dq2.append(jm)
    
l = []
while(len(dq1) > 0):
  l.append([dq1.popleft(), dq2.popleft()])

if(len(l) <= 0):
  print ('SEM FILA')
else:
  for elem in l:
    print('{:d} {:d}'.format(elem[0], elem[1]))
