n = int(input())
ar = [(i + 1, int(input())) for i in range(n)]
ar.sort(key=lambda a: a[1], reverse=True)
br = []
for i, a in enumerate(ar):
    br.append((i, len([0 for b in ar[: i + 1] if b[0] <= a[0]])))
br.sort(key=lambda a: a[0])
br = [b[1] for b in br]
print(*br, sep="\n")
