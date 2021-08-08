N = int(input())
ar = []
res = []

for _ in range(N):
    sub_ar = list(map(str, input().split()))
    title, year = sub_ar[0], int(sub_ar[1])
    ar.append((title, year))

ar = sorted(ar)
cur = ""
prev = ar[0][0][0]

new = []
add = [ar[0]]

for i in range(1, len(ar)):
    cur = ar[i][0][0]
    if (prev == cur):
        add.append(ar[i])
        continue
    else:
        new.append(add)
        prev = cur
        add = []

    add.append(ar[i])

new.append(add)

for j in range(len(new)):
    new[j] = sorted(new[j], key=lambda x: x[1])

for tup in new:
    for thing in tup:
        print(thing[0])











