import time
from pyautogui import click, position
from PIL import ImageGrab
import keyboard

def get_position(str_msg, key="q"):
    print(str_msg)
    keyboard.wait(key)
    return position()

def get_area_position(str_msg, key1="q", key2="q"):
    print(str_msg)
    keyboard.wait(key1)
    left_top = position()
    keyboard.wait(key2)
    right_bottom = position()
    return left_top, right_bottom

def check_empty_seat(seat_area):
    criteria_value = 100
    jump_pixel = 7
    
    screen = ImageGrab.grab()
    
    def get_empty():
        for j in range(seat_area[0][1], seat_area[1][1], jump_pixel):
            for i in range(seat_area[0][0], seat_area[1][0], jump_pixel):
                rgb = screen.getpixel((i, j))
                
                br = False
                for ii in range(3):
                    if rgb[ii] <= criteria_value:
                        br = True

                if not br:
                    continue
                return i, j
        return None
    empty_seat = get_empty()
    if empty_seat is None:
        return None
    return empty_seat[0] + 2, empty_seat[1] + 2



def main():
    print("마우스 좌표 가져오기")
    time_select_list_pos = get_position("시간 선택 목록 좌표 입력")
    time_select_cancel_pos = get_position("시간 선택 취소 좌표 입력")
    time_select_pos = get_position("시간 선택 좌표 입력")

    reselect_pos = get_position("재선택 좌표 입력")

    seat_area = get_area_position("좌석 영역 입력")

    complete_pos = get_position("좌석 선택 완료 좌표 입력")
    
    interval = 0.5
    
    while True:
        def perform_click_sequence(positions):
            for pos in positions:
                click(pos)
                time.sleep(interval)
                if keyboard.is_pressed("a"):
                    return False
            return True

        click_positions = [
            time_select_list_pos,
            time_select_cancel_pos,
            time_select_list_pos,
            time_select_pos,
            reselect_pos
        ]

        if not perform_click_sequence(click_positions):
            break

        empty_seat = check_empty_seat(seat_area)
        if empty_seat is None:
            continue

        perform_click_sequence([empty_seat, complete_pos])
        break

main()