class Manager:
    def __init__(self, name, age, team):
        self.name = name
        self.age = age
        self.team = team

    def information(self):
        return f"{self.name} ({self.age}, {self.team})"


def add_score(score1, score2):
    return [s1 + s2 for s1, s2 in zip(score1, score2)]


def count_first(votes):
    vote_sum = [0 for _ in range(len(votes))]
    for vote, count in votes:
        vote_sum[vote[0]] += count

    return vote_sum


def get_max_index(vote_sum):
    max_index = 0
    for i in range(len(vote_sum)):
        if vote_sum[i] > vote_sum[max_index]:
            max_index = i

    return max_index


def get_min_index(vote_sum):
    min_index = 0
    for i in range(len(vote_sum)):
        if vote_sum[i] < vote_sum[min_index]:
            min_index = i

    return min_index


def calc_by_first(votes):
    vote_sum = count_first(votes)
    return get_max_index(vote_sum)


def calc_by_score(votes):
    vote_sum = [0 for _ in range(len(votes))]
    scores = [3, 2, 1]
    for vote, count in votes:
        for i in range(3):
            vote_sum[vote[i]] += scores[i] * count

    return get_max_index(vote_sum)


def calc_by_preference(votes):
    vote_count = 0
    for _, count in votes:
        vote_count += count

    while True:
        result = count_first(votes)
        first = get_max_index(result)
        if result[first] > (vote_count / 2):
            return first
        last = get_min_index(result)

        for vote, count in votes:
            if last in vote:
                vote.remove(last)


manager_count = int(input())
managers = []
for i in range(manager_count):
    name, age, team = input().split()
    managers.append(Manager(name, int(age), team))

vote_count = int(input())
votes = []
for i in range(vote_count):
    vote_info = list(map(int, input().split()))
    vote = list(map(lambda a: a - 1, vote_info[:-1]))
    count = vote_info[-1]
    votes.append((vote, count))

vote_kind = int(input())
voted = 0
if vote_kind == 1:
    voted = calc_by_first(votes)
elif vote_kind == 2:
    voted = calc_by_score(votes)
elif vote_kind == 3:
    voted = calc_by_preference(votes)

print(managers[voted].information())
