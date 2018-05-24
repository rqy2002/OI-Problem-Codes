m, n, l, r = int(input()), int(input()), 0, 1
while r**m < n:
    l, r = r, r * 2
while l + 1 < r:
    mid = (l + r) // 2
    if mid**m < n:
        l = mid
    else:
        r = mid

if r**m < n:
    print(r)
else:
    print(l)
