for _ in range(int(input())):
    n,k = map(int,input().split())
    mx = max(list(map(int,input().split())))

    print(k*mx-1 if mx > 1 else k*mx)