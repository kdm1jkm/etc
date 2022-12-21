import ast


class User:
    def __init__(self, name):
        self.name = name
        self.monitor_log = []
        self.chat_state = []

    def invite(self, user, room):
        user.chat_state.append(room)
        log = f"{self.name} invited {user.name} to the room"
        user.monitor_log.append(log)
        self.monitor_log.append(log)

    def create_room(self, users, room):
        log = f"{self.name} invited "
        for user in users:
            log += f"{user.name} "
        log += f"to the {room} room"

        for user in users:
            user.chat_state.append(room)
            user.monitor_log.append(log)

    def send(self, users, room, message):
        log = f"{self.name} send message"
        # log = f"{self.name} send message: '{message}'"

        for user in users:
            if room in user.chat_state:
                user.monitor_log.append(log)

    def exit_room(self, users, room):
        log = f"{self.name} leaved the room"

        for user in users:
            if room in user.chat_state:
                user.monitor_log.append(log)

        self.chat_state.remove(room)


class User_Server:
    def __init__(self):
        self.user_DB = []

    def create_user(self, user_name):
        self.user_DB.append(User(user_name))

    def find_user(self, user_name):
        for user in self.user_DB:
            if user.name == user_name:
                return user

    def invite_user(self, inviter_name, invitee_name, room):
        inviter = self.find_user(inviter_name)
        invitee = self.find_user(invitee_name)

        inviter.invite(invitee, room)

    def create_room(self, creator_name, invitee_names, room):
        creator = self.find_user(creator_name)
        invitees = [self.find_user(invitee_name) for invitee_name in invitee_names]

        creator.create_room(invitees, room)

    def exit_room(self, user_name, room):
        user = self.find_user(user_name)
        user.exit_room(self.user_DB, room)

    def send_message(self, sender_name, room, message):
        sender = self.find_user(sender_name)
        sender.send(self.user_DB, room, message)


class Chat_Server:
    def __init__(self):
        self.chat_room_DB = []
        self.system_log = []

    def create_room(self, room_name, user_count):
        self.system_log.append(f"(room_{len(self.chat_room_DB)}) generated")
        self.chat_room_DB.append({"name": room_name, "count": user_count})

    def find_room(self, room_name):
        for i in range(len(self.chat_room_DB)):
            if self.chat_room_DB[i]["name"] == room_name:
                return i

    def exit_room(self, room_name, user_name):
        room = self.find_room(room_name)
        self.system_log.append(f"(room_{room}) {user_name} exited")
        self.chat_room_DB[room]["count"] -= 1
        if self.chat_room_DB[room]["count"] == 0:
            self.system_log.append(f"(room_{room} removed")

    def invite_room(self, room_name, inviter_name, invitee_name):
        room = self.find_room(room_name)
        self.chat_room_DB[room]["count"] += 1
        self.system_log.append(f"(room_{room}) {invitee_name} invited")

    def send_message(self, room_name, user_name, message):
        room = self.find_room(room_name)
        self.system_log.append(f"(room_{room}) message send from {user_name}")


user_server = User_Server()
chat_server = Chat_Server()

for user_name in input().split():
    user_server.create_user(user_name)

command_count = int(input())
for _ in range(command_count):
    command = input().split()
    command_type = int(command[0])
    command_args = command[1:]
    if command_type == 1:
        room_name, creater_name = command_args
        invitee_names = ast.literal_eval(input())
        user_server.create_room(creater_name, invitee_names, room_name)
        chat_server.create_room(room_name, len(invitee_names))

    elif command_type == 2:
        room_name, user_name = command_args
        user_server.exit_room(user_name, room_name)
        chat_server.exit_room(room_name, user_name)

    elif command_type == 3:
        room_name, inviter_name, invitee_name = command_args
        user_server.invite_user(inviter_name, invitee_name, room_name)
        chat_server.invite_room(room_name, inviter_name, invitee_name)

    elif command_type == 4:
        room_name, sender, message = command_args
        user_server.send_message(sender, room_name, message)
        chat_server.send_message(room_name, sender, message)

user = user_server.find_user(input())
print("----------------------")
print("Chat server log:")
print(*chat_server.system_log, sep="\n")
print("----------------------")
print("test_user message log:")
print(*user.monitor_log, sep="\n")
print("----------------------")
print("test_user current room state:")
print(*user.chat_state, sep=" ")
