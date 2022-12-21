class Account:
    def __init__(self, id, pw, logged):
        self.id = id
        self.pw = pw
        self.logged = logged


class Database:
    def __init__(self, accounts, condition):
        self.accounts = accounts
        self.condition = condition

    def add_account(self, id, pw):
        self.accounts.append(Account(id, pw, False))

    def del_account(self, id):
        self.accounts = [ac for ac in self.accounts if ac.id != id]

    def validate_id(self, id):
        if len(id) <= 5:
            return False
        elif id in self.accounts:
            return False
        else:
            return True

    def validate_pw(self, id, pw):
        if len(pw) <= 5:
            return False
        for i in pw:
            if i in list(map(str, self.condition["number"])):
                break
        else:
            return False
        for i in pw:
            if i in self.condition["special"]:
                break
        else:
            return False
        if id not in pw:
            return True
        else:
            return False

    def sign_up(self, id, pw):
        if self.validate_id(id) == False:
            print("Signup failed: Invalid id")
        elif self.validate_pw(id, pw) == False:
            print("Signup failed: Invalid pw")
        else:
            print("Signup succeeded")
            self.add_account(id, pw)

    def withdraw(self, id):
        if id not in self.accounts:
            print("Withdraw failed: No such account")
        else:
            print("Withdraw succeeded")
            self.del_account(id)

    def sign_in(self, id):
        if id not in self.accounts:
            print("Signin failed: No such account")
        else:
            for i in range(len(self.accounts)):
                if self.accounts[i][0] == id and self.accounts[i][2] == False:
                    print("Signin succeeded")
                    self.accounts[i][2] = True
                elif self.accounts[i][0] == id and self.accounts[i][2] == True:
                    print("Signin failed: Already signed in")

    def sign_out(self, id):
        if id not in self.accounts:
            print("Signin failed: No such account")
        else:
            for i in range(len(self.accounts)):
                if self.accounts[i][0] == id and self.accounts[i][2] == True:
                    print("Signout succeeded")
                    self.accounts[i][2] = True
                elif self.accounts[i][0] == id and self.accounts[i][2] == False:
                    print("Signout failed: Already signed in")


accounts = []
condition = {
    "number": [0, 1, 2, 3, 4, 5, 6, 7, 8, 9],
    "special": ["!", "@", "#", "$", "%", "^", "&", "*"],
}
database = Database(accounts=accounts, condition=condition)
n = int(input())
for i in range(n):
    op = int(input())
    if op == 0:  # signup
        input_id = input()
        input_pw = input()
        database.sign_up(input_id, input_pw)
        pass
    elif op == 1:  # withdraw
        input_id = input()
        database.withdraw(input_id)
        pass
    elif op == 2:  # signin
        input_id = input()
        database.sign_in(input_id)
        pass
    elif op == 3:  # signout
        input_id = input()
        database.sign_out(input_id)
        pass
    elif op == 4:  # reset
        database.accounts = []
        pass
    else:
        print("Not supported")
