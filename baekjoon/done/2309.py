from itertools import combinations


heights = [int(input()) for _ in range(9)]
for comb in combinations(heights, 7):
    if sum(comb) == 100:
        comb = sorted(comb)
        print(*comb, sep="\n")
        break
