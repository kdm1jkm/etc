"""
Version 0.8.13

공학도를위한창의적컴퓨팅 수업에서

간단한 gui 프로그램을 만들어 보기 위한 모듈입니다.

- 파일 내용은 안 봐도 무방해요.

- 복잡한 프로그램을 만들 때는 이거보다 더 정교한 모듈을 사용하게 될 거예요.
  이 모듈은 '간단한 동작을, 내 손으로 직접' 만들어 보는 것을 목표로 구성되어 있고,
  그렇다 보니 일반적인 라이브러리들에 비해 제공하는 서비스(함수들 등)가 별로 없어요.
  잘 안 된다 싶으면, 인터넷 검색보다는(해봤자 잘 안 나옴) 조금 더 고민해 보는 것을 권장해요.
  
"""

import tkinter
import time


class Window:
    """
    title: 시작할 때 창 맨 위에 어떤 메시지를 표시할 것인지
    width, height: 창의 가로, 세로 길이
    interval: 두 프레임 사이의 시간 간격(float 형식, 단위는 초)
    printKeysyms: 실행 도중 사용자가 각 키를 누르거나 뗄 때마다 interactive에 해당 키의 명칭을 출력할 것인지
    printMouseButtonIdxs: 실행 도중 사용자가 각 마우스 버튼을 누르거나 뗄 때마다 interactive에 해당 버튼에 대한 index 값을 출력할 것인지
    isDebugMode: ☆ 이건 강사가 혼자 쓰려고 만들었어요.

    각 인수 값을 여러분이 지정하지 않는 경우 함수 정의 적은 사람이 정해 둔 것을 대신 사용합니다.
    """

    # 본문 Code 실행을 시작하거나 중단하기 위한 함수들

    def start(self):
        """
        '계속 실행되는 프로그램의 큰 while문'을 실행하기 시작합니다.
        일반적으로 이 함수에 대한 호출식은 여러분이 작성하는 .py 파일의 맨 마지막 문장 안에 적어 두면 됩니다. 예시 코드들을 참고해 주세요.
        """
        if self.initialize == None or self.update == None:
            print(
                "Window.start()를 호출하기 전에 먼저 Window.initialize, Window.update를 지정해 주세요."
            )
            return

        try:
            self.initialize(time.perf_counter())

            while not self.internals얘는안봐도돼요.isClosing:
                time_startFrame = time.perf_counter()

                self.internals얘는안봐도돼요.acceptInputs()

                self.update(time_startFrame)

                if self.internals얘는안봐도돼요.isClosing:
                    self.internals얘는안봐도돼요.master.destroy()
                    return

                self.internals얘는안봐도돼요.refreshWindow()
                time_endFrame = time.perf_counter()

                while time_endFrame - time_startFrame < self.interval:
                    self.internals얘는안봐도돼요.master.update()
                    time_endFrame = time.perf_counter()

        except Exception as e:
            if not self.internals얘는안봐도돼요.isClosing:
                self.setTitle(
                    "["
                    + type(e).__name__
                    + " 발생으로 중단됨] - "
                    + self.internals얘는안봐도돼요.master.title()
                )
            print("창을 닫으려면 interactive에서 Ctrl + F6을 누르세요")
            raise e
        else:
            self.internals얘는안봐도돼요.master.destroy()

    def stop(self):
        """
        호출하면 모니터 화면에서 이 창을 지우고 '큰 while문'의 실행을 중단합니다.
        일반적으로는 호출하지 않아도 됩니다. 특정 시점에 창을 강제로 끄고 싶은 경우 그 시점에 실행될 문장 안에 이 함수에 대한 호출식을 적어 주세요.
        """
        self.internals얘는안봐도돼요.isClosing = True

    # gui 창 자체를 다루기 위한 함수들

    def setTitle(self, new_title):
        """
        창의 제목을 새로 지정합니다.

        new_title: 이 창의 맨 위에 표시할 메시지
        """

        self.internals얘는안봐도돼요.master.title(new_title)

    def moveWindow(self, new_x, new_y):
        """
        게임 화면 자체의 위치를 새로 지정합니다. 화면상의 마우스 포인터의 위치 또한 새 위치에 맞게 보정됩니다.

        new_x, new_y: 모니터 상에서의 창의 새 좌표(좌상단 점 기준)
        """
        self.offset_x = new_x - self.internals얘는안봐도돼요.window_position_x
        self.offset_y = new_y - self.internals얘는안봐도돼요.window_position_y

        self.internals얘는안봐도돼요.window_position_x = new_x
        self.internals얘는안봐도돼요.window_position_y = new_y

        self.mouse_position_x -= self.offset_x
        self.mouse_position_y -= self.offset_y

        self.internals얘는안봐도돼요.isWindowMoved = True

    def getWindowPosition(self):
        """
        게임 화면 자체의 현재 위치(좌상단 좌표) 값을 return합니다.

        return값: 게임 화면 자체의 x, y 값
        """

        return (
            self.internals얘는안봐도돼요.window_position_x,
            self.internals얘는안봐도돼요.window_position_y,
        )

    # 게임 화면에 표시할 요소들을 다루기 위한 함수들

    def makeColorCode(self, red, green, blue):
        """
        게임 화면에 표시할 요소들을 다룰 때 사용할 색을 커스터마이즈하고 싶을 때 사용하는 함수입니다.

        red, green, blue: 색상 값을 얻기 위한 RGB 값. 범위는 [0, 256), 256보다 크거나 같은 경우 256으로 나눈 나머지를 사용.

        return값: 지정한 RGB 값이 적용된 색상 값(str 형식)
        """

        return f"#{int(red) % 256:02x}{int(green) % 256:02x}{int(blue) % 256:02x}"

    def newRectangle(
        self,
        x,
        y,
        width,
        height,
        fill_color="black",
        outline_thickness=0,
        outline_color="",
        isVisible=True,
    ):
        """
        지정한 위치, 크기, 색상 값을 토대로 새 네모를 추가합니다.

        x, y: 새 네모의 좌상단 점의 좌표
        width, height: 새 네모의 가로/세로 길이
        fill_color: 새 네모를 채울 색상
        outline_thickness: 세 네모의 외곽선의 두께(0보다 작은 경우 0으로 간주해요)
        outline_color: 새 네모의 외곽선을 칠할 색상
        isVisible: 처음부터 새 네모를 화면에 보여줄 것인지 여부

        return값: 새 네모에 대한 일련번호

        색상 관련 도움말:
        > 영어 단어로 대강 적으면 알아들을 거예요
        > Window.getColorCode()를 사용하여 원하는 색상 값을 만들어 사용할 수 있어요
        > '투명 색'을 쓰고 싶을 때는 ''를 적으면 돼요
        """

        if outline_thickness < 0:
            outline_thickness = 0

        number = self.internals얘는안봐도돼요.canvas.create_rectangle(
            x,
            y,
            x + width,
            y + height,
            fill=fill_color,
            width=outline_thickness,
            outline=outline_color,
            state=tkinter.NORMAL if isVisible else tkinter.HIDDEN,
        )

        newInfo = self.internals얘는안봐도돼요.RectangleInfo(
            self.internals얘는안봐도돼요.canvas,
            number,
            x,
            y,
            width,
            height,
            fill_color,
            outline_thickness,
            outline_color,
            isVisible,
        )
        self.internals얘는안봐도돼요.objectInfos_list.insert(0, newInfo)
        self.internals얘는안봐도돼요.objectInfos_dict[number] = newInfo

        return number

    def newOval(
        self,
        x,
        y,
        width,
        height,
        fill_color="black",
        outline_thickness=0,
        outline_color="",
        isVisible=True,
    ):
        """
        지정한 위치, 크기, 색상 값을 토대로 새 동그라미를 추가합니다.

        x, y: 새 동그라미의 좌상단 점의 좌표
        width, height: 새 동그라미의 가로/세로방향 지름(두 값이 같은 경우 원이 돼요)
        fill_color: 새 동그라미를 채울 색상
        outline_thickness: 세 동그라미의 외곽선의 두께(0보다 작은 경우 0으로 간주해요)
        outline_color: 새 동그라미의 외곽선을 칠할 색상
        isVisible: 처음부터 새 동그라미를 화면에 보여줄 것인지 여부

        return값: 새 동그라미에 대한 일련번호

        색상 관련 도움말:
        > 영어 단어로 대강 적으면 알아들을 거예요
        > Window.getColorCode()를 사용하여 원하는 색상 값을 만들어 사용할 수 있어요
        > '투명 색'을 쓰고 싶을 때는 ''를 적으면 돼요
        """

        if outline_thickness < 0:
            outline_thickness = 0

        number = self.internals얘는안봐도돼요.canvas.create_oval(
            x,
            y,
            x + width,
            y + height,
            fill=fill_color,
            width=outline_thickness,
            outline=outline_color,
            state=tkinter.NORMAL if isVisible else tkinter.HIDDEN,
        )

        newInfo = self.internals얘는안봐도돼요.OvalInfo(
            self.internals얘는안봐도돼요.canvas,
            number,
            x,
            y,
            width,
            height,
            fill_color,
            outline_thickness,
            outline_color,
            isVisible,
        )
        self.internals얘는안봐도돼요.objectInfos_list.insert(0, newInfo)
        self.internals얘는안봐도돼요.objectInfos_dict[number] = newInfo

        return number

    def newImage(self, x, y, filename, isVisible=True):
        """
        주어진 위치에 새 그림을 추가합니다.

        x, y: 새 그림의 좌상단 점의 좌표
        filename: 그림 파일의 이름
        isVisible: 처음부터 새 그림을 화면에 보여줄 것인지 여부

        return값: 새 그림에 대한 일련번호

        그림 관련 주의할 점:
        > 그림의 크기를 코드로 직접 지정할 수는 없어요. 미리 적절한 크기의 그림을 그려서 준비해 주세요
        > 그림 파일들은 지금 작성중인 프로그램을 구성하는 .py 파일들이 담겨 있는 폴더에 넣어 두면 돼요
        """

        if not filename in self.internals얘는안봐도돼요.images:
            img = tkinter.PhotoImage(file=filename)
            self.internals얘는안봐도돼요.images[filename] = img
        else:
            img = self.internals얘는안봐도돼요.images[filename]

        number = self.internals얘는안봐도돼요.canvas.create_image(
            x,
            y,
            anchor=tkinter.NW,
            image=img,
            state=tkinter.NORMAL if isVisible else tkinter.HIDDEN,
        )

        newInfo = self.internals얘는안봐도돼요.ImageInfo(
            self.internals얘는안봐도돼요.canvas, number, x, y, img, isVisible
        )
        self.internals얘는안봐도돼요.objectInfos_list.insert(0, newInfo)
        self.internals얘는안봐도돼요.objectInfos_dict[number] = newInfo

        return number

    def newText(
        self, x, y, width, text="", fill_color="black", anchor="center", isVisible=True
    ):
        """
        주어진 위치에 새 텍스트를 추가합니다.

        x, y: 새 텍스트를 배치할 기준 좌표
        width: 새 텍스트의 최대 가로 길이(세로 길이는 자동으로 늘어나요)
        text: 새 텍스트에 보여줄 글자들
        fill_color: 새 텍스트의 글자색
        anchor: 기준 좌표를 배치할 조건
        isVisible: 처음부터 새 텍스트를 화면에 보여줄 것인지 여부

        return값: 새 텍스트에 대한 일련번호

        색상 관련 도움말:
        > 영어 단어로 대강 적으면 알아들을 거예요
        > Window.getColorCode()를 사용하여 원하는 색상 값을 만들어 사용할 수 있어요
        > '투명 색'을 쓰고 싶을 때는 ''를 적으면 돼요

        Anchor 관련 도움말:
        > 동서남북 같은 느낌으로, 'n', 'ne', 'e', 'se', 's', 'sw', 'w', 'nw', 그리고 'center' 중에 고를 수 있어요
        > 'nw'를 고른다면 텍스트의 x, y좌표는 그 텍스트의 좌상단 좌표로 간주돼요
        """
        number = self.internals얘는안봐도돼요.canvas.create_text(
            x,
            y,
            width=width,
            text=text,
            fill=fill_color,
            anchor=anchor,
            state=tkinter.NORMAL if isVisible else tkinter.HIDDEN,
        )

        newInfo = self.internals얘는안봐도돼요.TextInfo(
            self.internals얘는안봐도돼요.canvas,
            number,
            x,
            y,
            width,
            text,
            fill_color,
            anchor,
            isVisible,
        )
        self.internals얘는안봐도돼요.objectInfos_list.insert(0, newInfo)
        self.internals얘는안봐도돼요.objectInfos_dict[number] = newInfo

        return number

    def deleteObject(self, number):
        """
        일련번호가 number인 요소를 완전히 제거합니다.

        number: 제거할 요소의 일련번호
        """

        info = self.internals얘는안봐도돼요.objectInfos_dict[number]
        info.isMarkedForDelete = True

    def moveObject(self, number, new_x=None, new_y=None):
        """
        일련번호가 number인 요소의 위치를 변경합니다.
        인수 값을 None으로 지정하면 해당 값은 변경하지 않습니다.

        number: 옮길 요소의 일련번호
        new_x, new_y: 새 위치
        """

        info = self.internals얘는안봐도돼요.objectInfos_dict[number]

        if new_x == None:
            new_x = info.x

        if new_y == None:
            new_y = info.y

        if info.x != new_x or info.y != new_y:
            info.x = new_x
            info.y = new_y
            info.invalidation_flag |= info.flag_moved_resized

    def resizeObject(
        self, number, new_width=None, new_height=None, new_outline_thickness=None
    ):
        """
        일련번호가 number인 요소의 크기 또는 외곽선 두께를 변경합니다.
        인수 값을 None으로 지정하면 해당 값은 변경하지 않습니다.

        number: 변경할 요소의 일련번호
        new_width: 새 가로 길이(그림에는 적용되지 않아요)
        new_height: 새 세로 길이(그림과 텍스트에는 적용되지 않아요)
        new_outline_thickness: 새 외곽선 두께(그림과 텍스트에는 적용되지 않아요. 0보다 작은 경우 0으로 간주해요)
        """

        if new_outline_thickness != None and new_outline_thickness < 0:
            new_outline_thickness = 0

        info = self.internals얘는안봐도돼요.objectInfos_dict[number]
        if new_width != None and info.width != new_width:
            info.width = new_width
            info.invalidation_flag |= info.flag_moved_resized

        if new_height != None and info.height != new_height:
            info.height = new_height
            info.invalidation_flag |= info.flag_moved_resized

        if (
            new_outline_thickness != None
            and info.outline_thickness != new_outline_thickness
        ):
            info.outline_thickness = new_outline_thickness
            info.invalidation_flag |= info.flag_outline_changed

    def recolorObject(self, number, new_fill_color=None, new_outline_color=None):
        """
        일련번호가 number인 요소의 색상을 변경합니다.
        인수 값을 None으로 지정하면 해당 값은 변경하지 않습니다.

        number: 변경할 요소의 일련번호
        new_fill_color: 새 칠할 색상(그림에는 적용되지 않아요)
        new_outline_color: 새 외곽선 색상(그림에는 적용되지 않아요)

        색상 관련 도움말:
        > 영어 단어로 대강 적으면 알아들을 거예요
        > Window.getColorCode()를 사용하여 원하는 색상 값을 만들어 사용할 수 있어요
        > '투명 색'을 쓰고 싶을 때는 ''를 적으면 돼요
        """

        info = self.internals얘는안봐도돼요.objectInfos_dict[number]

        if new_fill_color != None and info.fill_color != new_fill_color:
            info.fill_color = new_fill_color
            info.invalidation_flag |= info.flag_fill_color_changed

        if new_outline_color != None and info.outline_color != new_outline_color:
            info.outline_color = new_outline_color
            info.invalidation_flag |= info.flag_outline_changed

    def showObject(self, number):
        """
        일련번호가 number인 요소를 보여주기 시작합니다.

        number: 보여주기 시작할 요소의 일련번호
        """

        info = self.internals얘는안봐도돼요.objectInfos_dict[number]
        if info.isVisible == False:
            info.isVisible = True
            info.invalidation_flag |= info.flag_isVisible_changed

    def hideObject(self, number):
        """
        일련번호가 number인 요소를 '안' 보여주기 시작합니다.

        number: 안 보여주기 시작할 요소의 일련번호
        """

        info = self.internals얘는안봐도돼요.objectInfos_dict[number]
        if info.isVisible == True:
            info.isVisible = False
            info.invalidation_flag |= info.flag_isVisible_changed

    def raiseObject(self, number):
        """
        일련번호가 number인 요소를 화면상의 '맨 위'로 올립니다.
        여러 요소들이 화면의 동일한 위치에 겹쳐 있는 경우 이 요소가 가장 위에 보이게 됩니다.

        number: 맨 앞으로 내어 보여줄 요소의 일련번호
        """

        self.internals얘는안봐도돼요.canvas.tag_raise(number)

        info = self.internals얘는안봐도돼요.objectInfos_dict[number]
        self.internals얘는안봐도돼요.objectInfos_list.remove(info)
        self.internals얘는안봐도돼요.objectInfos_list.insert(0, info)

    def lowerObject(self, number):
        """
        일련번호가 number인 네모, 동그라미, 또는 그림을 화면상의 '맨 아래'로 내립니다.
        여러 요소들이 화면의 동일한 위치에 겹쳐 있는 경우 이 요소가 가장 아래에 보이게 됩니다.

        number: 맨 뒤로 깔아 보여줄 요소의 일련번호
        """

        self.internals얘는안봐도돼요.canvas.tag_lower(number)

        info = self.internals얘는안봐도돼요.objectInfos_dict[number]
        self.internals얘는안봐도돼요.objectInfos_list.remove(info)
        self.internals얘는안봐도돼요.objectInfos_list.append(info)

    def setImage(self, number, new_filename):
        """
        일련번호가 number인 그림을 다른 파일의 것으로 변경합니다.

        number: 파일을 변경할 그림의 일련번호
        new_filename: 적용할 새 그림 파일의 이름(그림 파일은 지금 작성중인 프로그램을 구성하는 .py 파일들이 담겨 있는 폴더 또는 그 하위 폴더에 넣어 두면 돼요)
        """
        if not new_filename in self.internals얘는안봐도돼요.images:
            new_img = tkinter.PhotoImage(file=new_filename)
            self.internals얘는안봐도돼요.images[new_filename] = new_img
        else:
            new_img = self.internals얘는안봐도돼요.images[new_filename]

        info = self.internals얘는안봐도돼요.objectInfos_dict[number]

        if info.img != new_img:
            info.img = new_img
            info.width = new_img.width()
            info.height = new_img.height()
            info.invalidation_flag |= info.flag_img_changed

    def setText(self, number, new_text):
        """
        일련번호가 number인 텍스트의 글자들을 변경합니다.

        number: 변경할 텍스트의 일련번호
        new_filename: 새로 적용할 글자들
        """
        info = self.internals얘는안봐도돼요.objectInfos_dict[number]

        if info.text != new_text:
            info.text = new_text
            info.invalidation_flag |= info.flag_text_changed

    def setAnchorOfText(self, number, new_anchor):
        """
        일련번호가 number인 텍스트의 배치 기준을 변경합니다.

        number: 변경할 텍스트의 일련번호
        new_anchor: 새로 적용할 기준

        Anchor 관련 도움말:
        > 동서남북 같은 느낌으로, 'n', 'ne', 'e', 'se', 's', 'sw', 'w', 'nw', 그리고 'center' 중에 고를 수 있어요
        > 'nw'를 고른다면 텍스트의 x, y좌표는 그 텍스트의 좌상단 좌표로 간주돼요
        """
        info = self.internals얘는안봐도돼요.objectInfos_dict[number]

        if info.anchor != new_anchor:
            info.anchor = new_anchor
            info.invalidation_flag |= info.flag_anchor_changed

    def getPosition(self, number):
        """
        일련번호가 number인 요소의 화면상의 위치(좌상단 좌표)를 return합니다.

        number: Data를 가져올 요소의 일련번호

        return값: 해당 요소의 x, y 값
        """

        info = self.internals얘는안봐도돼요.objectInfos_dict[number]

        return info.x, info.y

    def getSize(self, number):
        """
        일련번호가 number인 요소의 화면상의 크기를 return합니다.

        number: Data를 가져올 요소의 일련번호

        return값: 해당 요소의 width, height 값
        """

        info = self.internals얘는안봐도돼요.objectInfos_dict[number]

        return info.width, info.height

    def getColor(self, number):
        """
        일련번호가 number인 요소의 색상을 return합니다.

        number: Data를 가져올 요소의 일련번호

        return값: 해당 요소의 '칠할 색상' 값(해당 요소가 그림인 경우 어떤 값이 나올지 몰라요)
        """

        info = self.internals얘는안봐도돼요.objectInfos_dict[number]

        return info.fill_color

    def getOutlineInfo(self, number):
        """
        일련번호가 number인 요소의 외곽선 두께 및 색상을 return합니다.

        number: Data를 가져올 요소의 일련번호

        return값: 해당 요소의 외곽선 두께, 색상 값(해당 요소가 그림 또는 텍스트인 경우 어떤 값이 나올지 몰라요)
        """

        info = self.internals얘는안봐도돼요.objectInfos_dict[number]

        return info.outline_thickness, info.outline_color

    def getTopObjectAt(self, x, y):
        """
        화면의 (x, y)자리에 있는 '맨 위' 요소의 일련번호를 return합니다.

        x, y: 요소를 탐색할 좌표

        return값: 해당 좌표에 놓여 있는 가장 '위'에 있는 요소의 일련번호를 return합니다. 해당 좌표에 아무 요소도 없는 경우 None을 return합니다.


        주의할 점:
        > 화면에서 가려 두었거나 아예 제거한 요소는 선택되지 않아요
        > 색상은 고려하지 않으며, '투명 색'이라 눈에 안 보인다 하더라도 선택될 수 있어요
        > 텍스트는 선택되지 않아요
        """

        for info in self.internals얘는안봐도돼요.objectInfos_list:
            if info.hitTest(x, y):
                return info.number

        return None

    def getAllObjectsAt(self, x, y):
        """
        화면의 (x, y)자리에 있는 모든 요소에 대한 일련번호 목록을 return합니다.

        x, y: 요소를 탐색할 좌표

        return값: 해당 좌표에 놓여 있는 모든 요소들에 대한 일련번호 list를 return합니다. 해당 좌표에 아무 요소도 없는 경우 빈 list를 return합니다.

        주의할 점:
        > 화면에서 가려 두었거나 아예 제거한 요소는 선택되지 않아요
        > 색상은 고려하지 않으며, '투명 색'이라 눈에 안 보인다 하더라도 선택될 수 있어요
        > 텍스트는 선택되지 않아요
        """
        result = []

        for info in self.internals얘는안봐도돼요.objectInfos_list:
            if info.hitTest(x, y):
                result.append(info.number)

        return result

    # 안 봐도 되는 내용들

    def __init__(
        self,
        title="개발중!",
        width=800,
        height=600,
        interval=1 / 60,
        printKeysyms=False,
        printMouseButtonIdxs=False,
        isDebugMode=False,
    ):
        class Internals:
            """
            ☆
            gui 모듈 내부에서 사용할 요소들을, 여러분이 프로그래밍할 때 이름 목록에 잘 안 보이도록 따로 모아 담아 두었습니다.
            굳이 구경하지 않아도 좋아요. 툴팁 설명도 안 달아 두었어요.
            """

            def __init__(
                self, w, width, height, printKeysyms, printMouseButtonIdxs, isDebugMode
            ):
                self.w = w

                self.printKeysyms = printKeysyms
                self.printMouseButtonIdxs = printMouseButtonIdxs
                self.isDebugMode = isDebugMode

                self.isClosing = False

                self.isWindowMoved = False
                self.window_position_x = 0
                self.window_position_y = 0

                self.master = tkinter.Tk()
                self.master.title(title)
                self.master.protocol("WM_DELETE_WINDOW", self.windowClosing)
                self.master.bind("<Configure>", self.windowMove)
                self.master.resizable(False, False)

                self.frame = tkinter.Frame(self.master)
                self.frame.focus_set()
                self.frame.bind("<KeyPress>", self.keyPress)
                self.frame.bind("<KeyRelease>", self.keyRelease)
                self.frame.grid()

                self.canvas = tkinter.Canvas(
                    self.frame,
                    width=width,
                    height=height,
                    highlightthickness=0,
                    bg="white",
                )
                self.canvas.bind("<Button>", self.mousePress)
                self.canvas.bind("<ButtonRelease>", self.mouseRelease)
                if self.isDebugMode:
                    self.canvas.bind("<Motion>", self.mouseMove)
                self.canvas.grid()

                self.buffer_keyInputs = [None] * 256
                self.head_buffer_keyInputs = 0
                self.tail_buffer_keyInputs = 0

                self.buffer_mouseInputs = [None] * 256
                self.head_buffer_mouseInputs = 0
                self.tail_buffer_mouseInputs = 0

                self.images = dict()

                self.objectInfos_dict = dict()
                self.objectInfos_list = []

            class Keys(dict):
                def __missing__(self, key):
                    self[key] = False
                    return False

            class ObjectInfo:
                flag_moved_resized = 0b1
                flag_fill_color_changed = 0b10
                flag_outline_changed = 0b100
                flag_isVisible_changed = 0b1000
                flag_img_changed = 0b10000
                flag_text_changed = 0b100000
                flag_anchor_changed = 0b1000000

                def __init__(
                    self,
                    type,
                    canvas,
                    number,
                    x,
                    y,
                    width,
                    height,
                    fill_color,
                    outline_thickness,
                    outline_color,
                    isVisible,
                ):
                    self.type = type
                    self.number = number

                    self.canvas = canvas

                    self.invalidation_flag = 0
                    self.isMarkedForDelete = False

                    self.isVisible = isVisible
                    self.x = x
                    self.y = y
                    self.width = width
                    self.height = height
                    self.fill_color = fill_color
                    self.outline_thickness = outline_thickness
                    self.outline_color = outline_color

                def updateObject(self):
                    if not self.invalidation_flag:
                        return

                    # moved or resized
                    if self.invalidation_flag & self.flag_moved_resized:
                        self.canvas.coords(
                            self.number,
                            self.x,
                            self.y,
                            self.x + self.width,
                            self.y + self.height,
                        )

                    # fill_color changed
                    if self.invalidation_flag & self.flag_fill_color_changed:
                        self.canvas.itemconfigure(self.number, fill=self.fill_color)

                    # outline changed
                    if self.invalidation_flag & self.flag_outline_changed:
                        self.canvas.itemconfigure(
                            self.number,
                            outline=self.outline_color,
                            width=self.outline_thickness,
                        )

                    # isVisible changed
                    if self.invalidation_flag & self.flag_isVisible_changed:
                        self.canvas.itemconfigure(
                            self.number,
                            state=tkinter.NORMAL if self.isVisible else tkinter.HIDDEN,
                        )

                    self.invalidation_flag = 0

                def hitTest(self, x, y):
                    return (
                        self.isVisible
                        and x >= self.x
                        and x < self.x + self.width
                        and y >= self.y
                        and y < self.y + self.height
                    )

            class RectangleInfo(ObjectInfo):
                def __init__(
                    self,
                    canvas,
                    number,
                    x,
                    y,
                    width,
                    height,
                    fill_color,
                    outline_thickness,
                    outline_color,
                    isVisible,
                ):
                    super().__init__(
                        "rectangle",
                        canvas,
                        number,
                        x,
                        y,
                        width,
                        height,
                        fill_color,
                        outline_thickness,
                        outline_color,
                        isVisible,
                    )

            class OvalInfo(ObjectInfo):
                def __init__(
                    self,
                    canvas,
                    number,
                    x,
                    y,
                    width,
                    height,
                    fill_color,
                    outline_thickness,
                    outline_color,
                    isVisible,
                ):
                    super().__init__(
                        "oval",
                        canvas,
                        number,
                        x,
                        y,
                        width,
                        height,
                        fill_color,
                        outline_thickness,
                        outline_color,
                        isVisible,
                    )

                def hitTest(self, x, y):
                    return (
                        self.isVisible
                        and self.width != 0
                        and self.height != 0
                        and (x - (self.x + self.width / 2)) ** 2 / (self.width / 2) ** 2
                        + (y - (self.y + self.height / 2)) ** 2 / (self.height / 2) ** 2
                        <= 1
                    )

            class ImageInfo(ObjectInfo):
                def __init__(self, canvas, number, x, y, img, isVisible):
                    super().__init__(
                        "image", canvas, number, x, y, 0, 0, "", 0, "", isVisible
                    )

                    self.img = img
                    self.width = img.width()
                    self.height = img.height()
                    self.isVisible = isVisible

                def updateObject(self):
                    if not self.invalidation_flag:
                        return

                    # moved
                    if self.invalidation_flag & self.flag_moved_resized:
                        self.canvas.coords(self.number, self.x, self.y)

                    # isVisible changed
                    if self.invalidation_flag & self.flag_isVisible_changed:
                        self.canvas.itemconfigure(
                            self.number,
                            state=tkinter.NORMAL if self.isVisible else tkinter.HIDDEN,
                        )

                    # img changed
                    if self.invalidation_flag & self.flag_img_changed:
                        self.canvas.itemconfig(self.number, image=self.img)

                    self.invalidation_flag = 0

            class TextInfo(ObjectInfo):
                def __init__(
                    self,
                    canvas,
                    number,
                    x,
                    y,
                    width,
                    text,
                    fill_color,
                    anchor,
                    isVisible,
                ):
                    super().__init__(
                        "text",
                        canvas,
                        number,
                        x,
                        y,
                        width,
                        height,
                        fill_color,
                        0,
                        "",
                        isVisible,
                    )

                    self.text = text
                    self.anchor = anchor

                def updateObject(self):
                    if not self.invalidation_flag:
                        return

                    # moved or resized
                    if self.invalidation_flag & self.flag_moved_resized:
                        self.canvas.coords(self.number, self.x, self.y)
                        self.canvas.itemconfigure(self.number, width=self.width)

                    # fill_color changed
                    if self.invalidation_flag & self.flag_fill_color_changed:
                        self.canvas.itemconfigure(self.number, fill=self.fill_color)

                    # isVisible changed
                    if self.invalidation_flag & self.flag_isVisible_changed:
                        self.canvas.itemconfigure(
                            self.number,
                            state=tkinter.NORMAL if self.isVisible else tkinter.HIDDEN,
                        )

                    # text changed
                    if self.invalidation_flag & self.flag_text_changed:
                        self.canvas.itemconfigure(self.number, text=self.text)

                    # anchor changed
                    if self.invalidation_flag & self.flag_anchor_changed:
                        self.canvas.itemconfigure(self.number, anchor=self.anchor)

                    self.invalidation_flag = 0

                def hitTest(self, x, y):
                    # 텍스트는 hitTest의 대상이 되지 않음
                    return False

            class Data:
                """
                여러분의 프로그램에서 사용할 Data들을 여기에 자유롭게 담아둘 수 있어요.
                """

                pass

            def acceptInputs(self):
                while self.head_buffer_keyInputs != self.tail_buffer_keyInputs:
                    keysym, state = self.buffer_keyInputs[self.head_buffer_keyInputs]

                    if self.w.keys[keysym] != state:
                        self.w.keys[keysym] = state

                        if self.printKeysyms:
                            print(
                                repr(keysym)
                                + (" - Pressed" if state else " - Released")
                            )

                    self.head_buffer_keyInputs += 1
                    self.head_buffer_keyInputs %= 256

                while self.head_buffer_mouseInputs != self.tail_buffer_mouseInputs:
                    num, state = self.buffer_mouseInputs[self.head_buffer_mouseInputs]

                    self.w.mouse_buttons[num] = state

                    if self.printMouseButtonIdxs:
                        print(
                            f"mouse_buttons[{num}]"
                            + (" - Pressed" if state else " - Released")
                        )

                    self.head_buffer_mouseInputs += 1
                    self.head_buffer_mouseInputs %= 256

                self.window_position_x = self.master.winfo_x()
                self.window_position_y = self.master.winfo_y()

                self.w.mouse_position_x = (
                    self.master.winfo_pointerx() - self.master.winfo_rootx()
                )
                self.w.mouse_position_y = (
                    self.master.winfo_pointery() - self.master.winfo_rooty()
                )

            def refreshWindow(self):
                if self.isWindowMoved:
                    self.master.geometry(
                        f"+{int(self.window_position_x)}+{int(self.window_position_y)}"
                    )
                    self.isWindowMoved = False

                idx = 0
                while idx < len(self.objectInfos_list):
                    info = self.objectInfos_list[idx]

                    if info.isMarkedForDelete:
                        self.canvas.delete(info.number)
                        self.objectInfos_list.pop(idx)
                        self.objectInfos_dict.pop(info.number)
                    else:
                        idx += 1

                for info in self.objectInfos_list:
                    info.updateObject()

                self.master.update()

            def windowClosing(self):
                self.isClosing = True

            def windowMove(self, event):
                if self.isDebugMode:
                    self.master.title(event)
                    print(event)

            def keyPress(self, event):
                self.buffer_keyInputs[self.tail_buffer_keyInputs] = (event.keysym, True)
                self.tail_buffer_keyInputs += 1
                self.tail_buffer_keyInputs %= 256

                if self.isDebugMode:
                    self.master.title(event)
                    print(event)

            def keyRelease(self, event):
                self.buffer_keyInputs[self.tail_buffer_keyInputs] = (
                    event.keysym,
                    False,
                )
                self.tail_buffer_keyInputs += 1
                self.tail_buffer_keyInputs %= 256

                if self.isDebugMode:
                    self.master.title(event)
                    print(event)

            def mousePress(self, event):
                self.buffer_mouseInputs[self.tail_buffer_mouseInputs] = (
                    event.num,
                    True,
                )
                self.tail_buffer_mouseInputs += 1
                self.tail_buffer_mouseInputs %= 256

                if self.isDebugMode:
                    self.master.title(event)
                    print(event)

            def mouseRelease(self, event):
                self.buffer_mouseInputs[self.tail_buffer_mouseInputs] = (
                    event.num,
                    False,
                )
                self.tail_buffer_mouseInputs += 1
                self.tail_buffer_mouseInputs %= 256

                if self.isDebugMode:
                    self.master.title(event)
                    print(event)

            def mouseMove(self, event):
                if self.isDebugMode:
                    self.master.title(event)
                    print(event)

        self.internals얘는안봐도돼요 = Internals(
            self, width, height, printKeysyms, printMouseButtonIdxs, isDebugMode
        )

        self.keys = Internals.Keys()

        self.mouse_buttons = [False] * 16

        self.mouse_position_x = 0
        self.mouse_position_y = 0

        self.data = Internals.Data()

        self.initialize = None
        self.update = None

        self.interval = interval
