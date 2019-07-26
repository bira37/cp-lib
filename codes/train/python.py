t = int(input())
n = int(input())
k = int(input())

l = []
for lalalal in range(t):
    d = k//n
    for i in range(n):
        if k-d >= 0:
            l.append(d)
            k -= k-d
        else:
            l.append(k)
            k = 0
    
    ans = 0
    a = 1
    b = len(l)-1
    lst = l[0]
    while a <= b:
        ans += abs(lst - l[a])
        if b != a:
            ans += abs(l[a] - l[b])
        lst = l[b]
        a+= 1
        b -= 1
    
    print(ans)
