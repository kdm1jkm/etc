import time
from pyautogui import click, position
from PIL import ImageGrab
import keyboard

def get_position(prompt, key="q"):
    print(prompt)
    keyboard.wait(key)
    return position()

def get_area_position(prompt, key1="q", key2="q"):
    print(prompt)
    keyboard.wait(key1)
    left_top = position()
    keyboard.wait(key2)
    right_bottom = position()
    return left_top, right_bottom

def find_empty_seat(seat_area, colors, jump_pixel=7):
    screen = ImageGrab.grab()
    
    for y in range(seat_area[0][1], seat_area[1][1], jump_pixel):
        for x in range(seat_area[0][0], seat_area[1][0], jump_pixel):
            rgb = screen.getpixel((x, y))
            for color in colors:
                if all(abs(rgb[i] - color[i]) < 10 for i in range(3)):
                    return (x + 2, y + 2)
    return None

def perform_click_sequence(positions, interval=0.5):
    for pos in positions:
        click(pos)
        time.sleep(interval)
        if keyboard.is_pressed("a"):
            return False
    return True

def main():
    print("마우스 좌표 가져오기")
    time_select_list_pos = get_position("시간 선택 목록 좌표 입력")
    time_select_cancel_pos = get_position("시간 선택 취소 좌표 입력")
    time_select_pos = get_position("시간 선택 좌표 입력")
    reselect_pos = get_position("재선택 좌표 입력")
    seat_area = get_area_position("좌석 영역 입력")
    complete_pos = get_position("좌석 선택 완료 좌표 입력")
    
    color_count = 2
    colors = []
    for i in range(color_count):
        screen = ImageGrab.grab()
        pos  = get_position(f"{i+1}번 색상 좌표 입력")
        color = screen.getpixel(pos)
        colors.append(color)
    
    while True:
        click_positions = [
            time_select_list_pos,
            time_select_cancel_pos,
            time_select_list_pos,
            time_select_pos,
            reselect_pos
        ]

        if not perform_click_sequence(click_positions):
            break

        empty_seat = find_empty_seat(seat_area, colors)
        if empty_seat is None:
            continue

        perform_click_sequence([empty_seat, complete_pos])
        break

main()