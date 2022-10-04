from collections import defaultdict


weeks: int = int(input())

table = [input().split() for _ in range(4 * weeks)]

times = (4, 6, 4, 10)

time_sum = defaultdict(lambda: 0)

for i, week in enumerate(table):
    for person in week:
        if person == "-":
            continue

        time_sum[person] += times[i % 4]


if len(time_sum) == 0:
    print("Yes")

elif max(time_sum.values()) - min(time_sum.values()) <= 12:
    print("Yes")

else:
    print("No")
