def diff(a, b):
    change = 0
    idx = 0
    if len(a) != len(b):
        return 0
    
    while idx < len(a):
        if a[idx] != b[idx]:
            change += 1
        idx += 1
    
    return change

N = int(input())
arr = []

for _ in range(N):
    res = ""
    bevnum = int(input())
    ar = input().split()
    wrong = input().split()
    size, bev = wrong[0], wrong[1]
    
    if diff(size, "small") == 1:
        res = "small"
    elif diff(size, "medium") == 1:
        res = "medium"
    else:
        res = "large"

    for word in ar:
        if diff(word, bev) == 1:
            arr.append(res + " " + word)
            break

for s in arr:
    print(s)


