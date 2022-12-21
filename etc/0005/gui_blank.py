"""
gui 모듈을 사용하기 위한 기본 구조를 미리 적어 둔 파일입니다.

- 여러분은 이 아래에 있는, 함수 initialize()와 update()에 대한
  함수 정의 내용물을 구성함으로써 프로그램을 구성해야 해요

- 중간중간 F5를 눌러 interactive를 켜 둔 다음 진행하면
  IDLE이 함수 호출식 적을 때마다 적당한 툴팁을 읽어 보여줄 거예요
"""

## 2022099143 김도현
## 만나면 안되는 게임
## 사용 방법 : 게임 시작 후 무작위 시간에 생성되는 네모를 좌클릭하여 없애고 점수를 얻거나 우클릭하여 네모를 없애지 않고 점수를 늘린다.  s 누르면 일시정지 가능, 네모가 겹치면 게임오버, escape 누르면 게임 끝낼 수 있음
## w 누르면 제목이 이겼습니다로 바뀜 ( 실제로 이긴 기분을 느낄 수 있음)
##


### 사각형끼리 만날 때 게임 패배
### 사각형 없애면 점수 _ 시간 추가
## 사각형 생성될때 전 위치랑 다른데서 생성됐으면
## 우클릭시 색깔 바뀌고 점수 2

import gui_core as gui
import random
from itertools import combinations, product

INCREASE_SPEED = 0.4
DECREASE_AMOUNT = 1
GAME_PERIOD = 10

SCREEN_SIZE = (800, 600)
PADDING = (50, 30)

w = gui.Window()


def initialize(timestamp):
    w.data.last_stamp = timestamp
    w.data.start_stamp = timestamp
    w.data.rectangles = []
    w.data.circles = []
    w.data.t = random.random() + 0.2
    w.data.added_time = 0
    w.data.score = 0.0
    w.data.prev_clicked = False

    # state
    # 0 -> 게임 진행
    # 1 -> 개임 끝남
    w.data.state = 0
    w.setTitle("s누르고 있는동안  멈춰요")


def distance(pos1, pos2):
    return ((pos1[0] - pos2[0]) ** 2 + (pos1[1] - pos2[1]) ** 2) ** 0.5


def is_in_rectangle(mouse_pos, rectangle):
    mouse_x, mouse_y = mouse_pos
    pos_x, pos_y = w.getPosition(rectangle)
    width, height = w.getSize(rectangle)

    return (
        pos_x <= mouse_x
        and mouse_x <= pos_x + width
        and pos_y <= mouse_y
        and mouse_y <= pos_y + height
    )


def is_in_circle(mouse_pos, circle):
    width, height = w.getSize(circle)
    r = width / 2
    x, y = w.getPosition(circle)

    return distance(mouse_pos, (x + width / 2, y + height / 2)) < r


def get_not_collapsed_pos():
    while True:
        x = random.randint(PADDING[0], SCREEN_SIZE[0] - PADDING[1])
        y = random.randint(PADDING[1], SCREEN_SIZE[1] - PADDING[1])
        if len(w.data.rectangles) == 0 or not is_in_rectangle(
            (x, y), w.data.rectangles[-1]
        ):
            return (x, y)


def is_rectangle_collide(rectangle1, rectangle2):
    x1, y1 = w.getPosition(rectangle1)
    w1, h1 = w.getSize(rectangle1)

    x2, y2 = w.getPosition(rectangle2)
    w2, h2 = w.getSize(rectangle2)

    return (x1 - w2 < x2 and x2 < x1 + w1) and (y1 - h2 < y2 and y2 < y1 + h1)


def is_circle_collide(circle1, circle2):
    x1, y1 = w.getPosition(circle1)
    w1, h1 = w.getSize(circle1)
    r1 = w1 / 2

    x2, y2 = w.getPosition(circle2)
    w2, h2 = w.getSize(circle2)
    r2 = w2 / 2

    length = distance((x1 + w1 / 2, y1 + h1 / 2), (x2 + w2 / 2, y2 + h2 / 2))
    r = r1 + r2

    return length < r


def is_rectangle_circle_collide(rectangle, circle):
    if not is_rectangle_collide(rectangle, circle):
        return False

    x, y = w.getPosition(circle)
    width, height = w.getSize(circle)
    mid_x = x + width / 2
    mid_y = y + height / 2
    r = width / 2

    rect_x, rect_y = w.getPosition(rectangle)
    rect_w, rect_h = w.getSize(rectangle)

    if (mid_x - rect_x) * (mid_x - (rect_x + rect_w)) < 0 or (mid_y - rect_y) * (
        mid_y - (rect_y + rect_h)
    ) < 0:
        return True

    vertex = [
        (rect_x, rect_y),
        (rect_x + rect_w, rect_y),
        (rect_x, rect_y + rect_h),
        (rect_x + rect_w, rect_y + rect_h),
    ]
    for pos in vertex:
        if distance(pos, (mid_x, mid_y)) < r:
            return True
    return False


def update(timestamp):
    if w.keys["Escape"]:
        w.stop()
        return

    if w.keys["w"]:
        w.data.score = 314159265358979
        w.data.state = 1

    if w.keys["s"]:
        t = 3

    if w.data.state == 0:
        left_time = GAME_PERIOD + w.data.added_time - (timestamp - w.data.start_stamp)
        w.setTitle(f"남은 시간: {left_time:.05f}, 점수: {w.data.score: .03f}")

        if left_time < 0:
            w.data.state = 1

        # 도형 생성할 시간
        if timestamp - w.data.last_stamp >= w.data.t:
            w.data.t = random.random()
            x, y = get_not_collapsed_pos()

            choice = random.randint(1, 2)
            if choice == 1:
                w.data.rectangles.append(w.newRectangle(x, y, 1, 1))
            elif choice == 2:
                w.data.circles.append(w.newOval(x, y, 1, 1))
            w.data.last_stamp = timestamp

        for rectangle in w.data.rectangles:
            width, height = w.getSize(rectangle)
            x, y = w.getPosition(rectangle)
            w.resizeObject(rectangle, width + INCREASE_SPEED, height + INCREASE_SPEED)
            w.moveObject(rectangle, x - INCREASE_SPEED / 2, y - INCREASE_SPEED / 2)

        for circle in w.data.circles:
            width, height = w.getSize(circle)
            x, y = w.getPosition(circle)
            w.resizeObject(circle, width + INCREASE_SPEED, height + INCREASE_SPEED)
            w.moveObject(circle, x - INCREASE_SPEED / 2, y - INCREASE_SPEED / 2)

        for rectangle1, rectangle2 in combinations(w.data.rectangles, 2):
            if is_rectangle_collide(rectangle1, rectangle2):
                w.data.state = 1

        for circle1, circle2 in combinations(w.data.circles, 2):
            if is_circle_collide(circle1, circle2):
                w.data.state = 1

        for rectangle, circle in product(w.data.rectangles, w.data.circles):
            if is_rectangle_circle_collide(rectangle, circle):
                w.data.state = 1

        clicked = w.mouse_buttons[1]
        if not w.data.prev_clicked and clicked:
            delete_rectangles = []
            mouse_pos = (w.mouse_position_x, w.mouse_position_y)
            for rectangle in w.data.rectangles:
                if is_in_rectangle(mouse_pos, rectangle):
                    delete_rectangles.append(rectangle)
                    w.data.added_time += 0.7
                    width, _ = w.getSize(rectangle)
                    w.data.score += width**2

            for rectangle in delete_rectangles:
                w.deleteObject(rectangle)
                w.data.rectangles.remove(rectangle)

            delete_circles = []

            for circle in w.data.circles:
                if is_in_circle(mouse_pos, circle):
                    delete_circles.append(circle)
                    w.data.added_time += 0.7
                    width, _ = w.getSize(circle)
                    w.data.score += width**2

            for circle in delete_circles:
                w.deleteObject(circle)
                w.data.circles.remove(circle)
        w.data.prev_clicked = clicked

        if w.mouse_buttons[3]:
            for rectangle in w.data.rectangles:
                if is_in_rectangle((w.mouse_position_x, w.mouse_position_y), rectangle):
                    width, height = w.getSize(rectangle)
                    x, y = w.getPosition(rectangle)

                    if width - DECREASE_AMOUNT < 1 or height - DECREASE_AMOUNT < 1:
                        w.resizeObject(rectangle, 1)
                        w.moveObject(rectangle, (x + width) / 2, (y + height) / 2)
                    else:
                        w.resizeObject(
                            rectangle, width - DECREASE_AMOUNT, height - DECREASE_AMOUNT
                        )
                        w.moveObject(
                            rectangle, x + DECREASE_AMOUNT / 2, y + DECREASE_AMOUNT / 2
                        )

            for circle in w.data.circles:
                if is_in_circle((w.mouse_position_x, w.mouse_position_y), circle):
                    width, height = w.getSize(circle)
                    x, y = w.getPosition(circle)

                    if width - DECREASE_AMOUNT < 1 or height - DECREASE_AMOUNT < 1:
                        w.resizeObject(circle, 1)
                        w.moveObject(circle, (x + width) / 2, (y + height) / 2)
                    else:
                        w.resizeObject(
                            circle, width - DECREASE_AMOUNT, height - DECREASE_AMOUNT
                        )
                        w.moveObject(
                            circle, x + DECREASE_AMOUNT / 2, y + DECREASE_AMOUNT / 2
                        )

    elif w.data.state == 1:
        w.setTitle(f"점수: {w.data.score:.03f}")

        w.newText(
            SCREEN_SIZE[0] / 2, SCREEN_SIZE[1] / 2, 300, f"점수: {w.data.score:.03f}"
        )


w.initialize = initialize
w.update = update

w.start()
