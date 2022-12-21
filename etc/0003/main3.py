class Pocketmon:
    def __init__(self, name, _type, hp, damage):
        self.name = name
        self.type = _type
        self.hp = hp
        self.damage = damage

    def is_critical(self, other_pocketmon):
        if self.type == "Grassmon" and other_pocketmon.type == "Watermon":
            return True
        elif self.type == "Watermon" and other_pocketmon.type == "Firemon":
            return True
        elif self.type == "Firemon" and other_pocketmon.type == "Grassmon":
            return True
        return False

    def get_critical_damage(self):
        if self.type == "Watermon":
            return (self.damage * self.damage) / 2
        elif self.type == "Firemon":
            return self.damage + 5
        elif self.type == "Grassmon":
            return self.damage * 3

    def is_dead(self):
        return self.hp <= 0

    def attack(self, other_pocketmon):
        if self.is_critical(other_pocketmon):
            print(
                f"{self.name} critically attacked {other_pocketmon.name}! This attack did {self.get_critical_damage()} damage to {other_pocketmon.name}!"
            )
            other_pocketmon.hp -= self.get_critical_damage()
        else:
            print(
                f"{self.name} attacked {other_pocketmon.name}! This attack did {self.damage} damage to {other_pocketmon.name}!"
            )
            other_pocketmon.hp -= self.damage


player1 = []
player2 = []

for i in range(3):
    name, _type, hp, damage = input().split()
    player1.append(Pocketmon(name, _type, int(hp), int(damage)))
for i in range(3):
    name, _type, hp, damage = input().split()
    player2.append(Pocketmon(name, _type, int(hp), int(damage)))

turn = 1

while True:
    if len(player1) == 0:
        print("Player 2 Won!")
        break
    elif len(player2) == 0:
        print("Player 1 Won!")
        break

    if turn == 1:
        player1[0].attack(player2[0])
        if player2[0].is_dead():
            del player2[0]
        turn = 2
    elif turn == 2:
        player2[0].attack(player1[0])
        if player1[0].is_dead():
            del player1[0]
        turn = 1
