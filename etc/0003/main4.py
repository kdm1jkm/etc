class Team:
    def __init__(self, name):
        self.name = name
        self.point = 0
        self.goal_point = 0

    def win(self):
        self.point += 3

    def draw(self):
        self.point += 1

    def play(self, other_team, score, other_score):
        if score > other_score:
            self.win()
        elif score < other_score:
            other_team.win()
        else:
            self.draw()
            other_team.draw()

        self.goal_point += score - other_score
        other_team.goal_point += other_score - score

    def __str__(self):
        return f"{self.name} [{self.point}, {self.goal_point}]"


team_count = int(input())
teams = {}
for i in range(team_count):
    team = input()
    teams[team] = Team(team)

for i in range(team_count * (team_count - 1)):
    team1, team2 = input().split()
    score1, score2 = map(int, input().split())
    teams[team1].play(teams[team2], score1, score2)

teams = list(teams.values())
teams.sort(key=lambda team: team.goal_point, reverse=True)
teams.sort(key=lambda team: team.point, reverse=True)

for i, team in enumerate(teams):
    print(f"{i + 1}등: {team}")
