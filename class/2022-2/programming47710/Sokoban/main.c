#define _CRT_SECURE_NO_WARNINGS // NOLINT(bugprone-reserved-identifier)

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

/**********************************************************************************************************************/
//                                                     열거형

// 특수 키
typedef enum
{
    KEY_ESC = 27,
    KEY_LEFT = 75,
    KEY_RIGHT = 77,
    KEY_UP = 72,
    KEY_DOWN = 80
} Key;

// 맵 원소
typedef enum
{
    ELEMENT_EMPTY,
    ELEMENT_WALL,
    ELEMENT_PACK,
    ELEMENT_DEPOT,
    ELEMENT_PLAYER
} Element;

/**********************************************************************************************************************/
//                                                     구조체

// Z^2 Vector
typedef struct
{
    int row, column;
} Vec2i;

// ArrayList
typedef struct
{
    void *data;
    size_t capacity;
    size_t width;
    size_t size;
} ArrayList;

// 게임 맵
typedef struct
{
    int row, column;
    Element *data;
    Vec2i playerPos;
    ArrayList *packs, *depots;
} Map;

// 한 회 이동 정보
typedef struct
{
    Vec2i moveVec;
    bool pushed;
} MoveInfo;

// 현재 게임 정보
typedef struct
{
    Map *map;
    int totalPassedTime;
    int localPassedTime;
    int totalMovement;
    int localMovement;
    MoveInfo lastMove;
    int cancelAmount;
} Game;

// 사용자 입력 종류
typedef struct
{
    enum
    {
        MOVE,
        RESET,
        CHANGE_STAGE,
        EXIT,
        NONE
    } commandType;
    union
    {
        Vec2i vec;
        Map *nextMap;
    } commandValue;
} InputCommand;

/**********************************************************************************************************************/
//                                                콘솔 유틸 함수

void gotoxy(int x, int y)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                             (COORD){x, y}); // NOLINT(cppcoreguidelines-narrowing-conversions)
}

void clrscr()
{
    system("cls");
    gotoxy(0, 0);
}

void showcursor(bool bShow)
{
    CONSOLE_CURSOR_INFO CurInfo = {20, bShow};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

Vec2i getConsoleSize()
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

    return (Vec2i){info.srWindow.Bottom - info.srWindow.Top + 1, info.srWindow.Right - info.srWindow.Left + 1};
}

Vec2i calcMiddlePos(const Vec2i *boxSize)
{
    Vec2i screenSize = getConsoleSize();
    return (Vec2i){(screenSize.row - boxSize->row) / 2, (screenSize.column - boxSize->column) / 2};
}

/**********************************************************************************************************************/
//                                                일반 유틸 함수

void delay(int milliSecond)
{
    Sleep(milliSecond);
}

Vec2i addVec(const Vec2i *vec1, const Vec2i *vec2)
{
    return (Vec2i){vec1->row + vec2->row, vec1->column + vec2->column};
}

Vec2i scalarVec(const Vec2i *vec, int scale)
{
    return (Vec2i){vec->row * scale, vec->column * scale};
}

int compareVec2i(const void *p1, const void *p2)
{
    Vec2i *pos1 = (Vec2i *)p1;
    Vec2i *pos2 = (Vec2i *)p2;
    if (pos1->row == pos2->row)
        return pos1->column - pos2->column;
    return pos1->row - pos2->row;
}

/**********************************************************************************************************************/
//                                           ArrayList 구조체 관련 함수

ArrayList *newArrayList(size_t width, size_t capacity)
{
    ArrayList *arrayList = (ArrayList *)malloc(sizeof(ArrayList));

    arrayList->capacity = capacity;
    arrayList->width = width;
    arrayList->data = malloc(width * capacity);
    arrayList->size = 0;

    return arrayList;
}

void freeArrayList(ArrayList *arrayList)
{
    free(arrayList->data);
    free(arrayList);
}

void sortList(ArrayList *arrayList, int compare(const void *, const void *))
{
    qsort(arrayList->data, arrayList->size, arrayList->width, compare);
}

void *getListElement(ArrayList *arrayList, size_t index)
{
    char *c = arrayList->data;
    return &c[index * arrayList->width];
}

bool resetListCapacity(ArrayList *arrayList, size_t capacity)
{
    void *prev = arrayList->data;
    arrayList->data = realloc(arrayList->data, arrayList->width * capacity);
    if (arrayList->data == NULL)
    {
        arrayList->data = prev;
        return false;
    }
    return true;
}

bool listAppend(ArrayList *arrayList, void *element)
{
    if (arrayList->size == arrayList->capacity)
        if (!resetListCapacity(arrayList, arrayList->capacity * 2))
            return false;

    char *ptr = getListElement(arrayList, arrayList->size++);
    for (int i = 0; i < arrayList->width; ++i)
    {
        ptr[i] = ((char *)element)[i];
    }

    return true;
}

void *findElement(ArrayList *arrayList, void *element, int compare(const void *, const void *))
{
    return bsearch(element, arrayList->data, arrayList->size, arrayList->width, compare);
}

/**********************************************************************************************************************/
//                                              Map 구조체 관련 함수

Map *newMap(int row, int column)
{
    Map *map = (Map *)malloc(sizeof(Map));
    map->row = row;
    map->column = column;
    map->data = (Element *)malloc(sizeof(Element) * row * column);
    map->packs = newArrayList(8, sizeof(Vec2i));
    map->depots = newArrayList(8, sizeof(Vec2i));
    return map;
}

void freeMap(Map *map)
{
    free(map->data);
    freeArrayList(map->packs);
    freeArrayList(map->depots);
    free(map);
}

Vec2i posFromIndex(Map *map, int index)
{
    return (Vec2i){.row = index / map->column, .column = index % map->column};
}

int indexFromPos(Map *map, Vec2i pos)
{
    return pos.column + pos.row * map->column;
}

bool checkMapRange(Map *map, Vec2i pos)
{
    return 0 <= pos.row && pos.row < map->row && 0 <= pos.column && pos.column < map->column;
}

Element getMapElement(Map *map, Vec2i pos)
{
    if (!checkMapRange(map, pos))
        return ELEMENT_EMPTY;
    if (compareVec2i(&pos, &map->playerPos) == 0)
        return ELEMENT_PLAYER;
    if (findElement(map->packs, &pos, compareVec2i) != NULL)
        return ELEMENT_PACK;
    if (findElement(map->depots, &pos, compareVec2i) != NULL)
        return ELEMENT_DEPOT;
    return map->data[indexFromPos(map, pos)];
}

Map *getEmbeddedStage(int mapIndex)
{
    static char arStage[][18][20] = {
        {
            "11111111111111111111",
            "11111111111111111111",
            "11111111111111111111",
            "11111000111111111111",
            "11111200111111111111",
            "11111002111111111111",
            "11100202011111111111",
            "11101011011111111111",
            "10001011011111003311",
            "10200200040000003311",
            "11111011101011003311",
            "11111000001111111111",
            "11111111111111111111",
            "11111111111111111111",
            "11111111111111111111",
            "11111111111111111111",
            "11111111111111111111",
            "11111111111111111111",
        },
        {
            "11111111111111111111",
            "11111111111111111111",
            "11111111111111111111",
            "11111111111111111111",
            "11113300100000111111",
            "11113300102002001111",
            "11113300121111001111",
            "11113300004011001111",
            "11113300101002011111",
            "11111111101120201111",
            "11111102002020201111",
            "11111100001000001111",
            "11111111111111111111",
            "11111111111111111111",
            "11111111111111111111",
            "11111111111111111111",
            "11111111111111111111",
            "11111111111111111111",
        },
        {
            "11111111111111111111",
            "11111111111111111111",
            "11111111111111111111",
            "11111111111111111111",
            "11111111110000041111",
            "11111111110212011111",
            "11111111110200211111",
            "11111111111202011111",
            "11111111110201011111",
            "11333300110200200111",
            "11133300002002000111",
            "11333300111111111111",
            "11111111111111111111",
            "11111111111111111111",
            "11111111111111111111",
            "11111111111111111111",
            "11111111111111111111",
            "11111111111111111111",
        },
    };
    if (mapIndex < 0 || mapIndex >= 3)
    {
        return NULL;
    }
    Map *map = newMap(18, 20);

    for (int i = 0; i < map->row * map->column; ++i)
    {
        Vec2i pos = posFromIndex(map, i);
        char c = arStage[mapIndex][pos.row][pos.column];
        if (c == '1')
        {
            map->data[i] = ELEMENT_WALL;
        }
        else
        {
            map->data[i] = ELEMENT_EMPTY;
            switch (c)
            {
            case '2':
                listAppend(map->packs, &pos);
                break;
            case '3':
                listAppend(map->depots, &pos);
                break;
            case '4':
                map->playerPos = pos;
                break;

            default:
                break;
            }
        }
    }

    sortList(map->packs, compareVec2i);
    sortList(map->depots, compareVec2i);

    return map;
}

Map *loadMapFromFile(const char *filename)
{
    FILE *f = fopen(filename, "r");

    if (f == NULL)
    {
        return NULL;
    }

    int row, column;
    if (fscanf(f, "%d %d", &row, &column) != 2) // NOLINT(cert-err34-c)
        return NULL;

    Map *map = newMap(row, column);

    for (int i = 0; i < row * column; ++i)
    {
        char c;
        fscanf(f, " %c", &c);
        Vec2i pos = posFromIndex(map, i);
        if (c == '1')
        {
            map->data[i] = ELEMENT_WALL;
        }
        else
        {
            map->data[i] = ELEMENT_EMPTY;
            switch (c)
            {
            case '2':
                listAppend(map->packs, &pos);
                break;
            case '3':
                listAppend(map->depots, &pos);
                break;
            case '4':
                map->playerPos = pos;
                break;

            default:
                break;
            }
        }
    }

    sortList(map->packs, compareVec2i);
    sortList(map->depots, compareVec2i);

    fclose(f);

    return map;
}

void printElement(Element element, FILE *stream)
{
    static const char *colors[] = {
        "\x1b[100m",
        "\x1b[47m",
        "\x1b[41m",
        "\x1b[101m",
        "\x1b[44m",
    };
    fprintf(stream, "%s  \x1b[0m", colors[element]);
}

void printMap(Map *map, Vec2i pos, FILE *stream)
{
    for (int row = 0; row < map->row; ++row)
    {
        gotoxy(pos.column, pos.row + row);
        for (int column = 0; column < map->column; ++column)
        {
            printElement(getMapElement(map, (Vec2i){row, column}), stream);
        }
    }
}

bool checkBlank(Map *map, Vec2i pos)
{
    if (!checkMapRange(map, pos))
        return false;
    Element e = getMapElement(map, pos);
    return e == ELEMENT_EMPTY || e == ELEMENT_DEPOT;
}

bool checkClear(Map *map)
{
    for (int i = 0; i < map->packs->size; ++i)
    {
        Vec2i *pack = getListElement(map->packs, i);
        Vec2i *depot = getListElement(map->depots, i);
        if (compareVec2i(pack, depot) != 0)
            return false;
    }

    return true;
}

/**********************************************************************************************************************/
//                                              Game 구조체 관련 함수

Game *newGame(Map *map)
{
    Game *game = (Game *)malloc(sizeof(Game));
    game->map = map;
    game->cancelAmount = 1;
    game->localMovement = 0;
    game->totalMovement = 0;
    game->localPassedTime = 0;
    game->totalPassedTime = 0;

    return game;
}

void resetMap(Game *game, Map *map)
{
    freeMap(game->map);
    game->map = map;
    game->cancelAmount = 1;
    game->localMovement = 0;
    game->localPassedTime = 0;
}

void freeGame(Game *game)
{
    free(game->map);
    free(game);
}

void printGame(Game *game, const char *mapName, FILE *stream)
{
    const int infoRowSize = 10;
    const int infoColumnSize = 3 + 50;

    static Vec2i prevSize = {-1, -1};

    Vec2i gameSize = {max(infoRowSize, game->map->row), infoColumnSize + game->map->column * 2};
    Vec2i screenSize = getConsoleSize();
    Vec2i pos = calcMiddlePos(&gameSize);

    if (compareVec2i(&prevSize, &screenSize) != 0)
    {
        prevSize = screenSize;
        clrscr();
    }

    if (screenSize.row < gameSize.row || screenSize.column < gameSize.column)
    {
        gotoxy(0, 0);
        fputs("콘솔 창의 크기가 너무 작습니다!\n", stream);
        fputs("크기를 늘리거나 숫자키(1, 2, 3) 또는 l을 눌러 스테이지를 변경해 주세요.", stream);
        return;
    }

    // Print map
    printMap(game->map, pos, stream);

    // Print infoColumnSize
    int infoRowStart = pos.row;
    if (infoRowStart < pos.row)
        infoRowStart = pos.row;
    int infoColumnStart = pos.column + game->map->column * 2 + 3;
    gotoxy(infoColumnStart, infoRowStart);
    fprintf(stream, "SOKOBAN(%s)", mapName);
    infoRowStart += 2;

    gotoxy(infoColumnStart, infoRowStart);
    fputs("종료: ESC", stream);
    infoRowStart += 1;
    gotoxy(infoColumnStart, infoRowStart);
    fputs("스테이지 이동: 1, 2, 3", stream);
    infoRowStart += 1;
    gotoxy(infoColumnStart, infoRowStart);
    fputs("스테이지 불러오기(파일): l", stream);
    infoRowStart += 1;
    gotoxy(infoColumnStart, infoRowStart);
    fputs("플레이어 이동: ↑ ↓ ← →", stream);
    infoRowStart += 1;
    gotoxy(infoColumnStart, infoRowStart);
    fprintf(stream, "되돌리기(남은 횟수: %d): z", game->cancelAmount);
    infoRowStart += 2;

    gotoxy(infoColumnStart, infoRowStart);
    fprintf(stream, "총 경과 시간(현재 맵 경과 시간): %.02f(%.02f)", game->totalPassedTime / 1000.0,
            game->localPassedTime / 1000.0);
    infoRowStart += 1;
    gotoxy(infoColumnStart, infoRowStart);
    fprintf(stream, "총 움직인 횟수(현재 맵 움직인 횟수): %03d(%03d)", game->totalMovement, game->localMovement);
}

bool tryMove(Game *game, const Vec2i *playerMovement)
{
    Vec2i nextPos = addVec(&game->map->playerPos, playerMovement);
    if (!checkMapRange(game->map, nextPos))
        return false;
    if (checkBlank(game->map, nextPos))
    {
        game->map->playerPos = nextPos;
        game->lastMove = (MoveInfo){.pushed = false, .moveVec = *playerMovement};
        return true;
    }

    if (getMapElement(game->map, nextPos) != ELEMENT_PACK)
        return false;

    Vec2i nextNextPos = addVec(&nextPos, playerMovement);
    if (!checkMapRange(game->map, nextNextPos))
        return false;
    if (!checkBlank(game->map, nextNextPos))
        return false;

    Vec2i *pack = findElement(game->map->packs, &nextPos, compareVec2i);
    if (pack != NULL)
        *pack = nextNextPos;
    game->map->playerPos = nextPos;

    game->lastMove = (MoveInfo){.pushed = true, .moveVec = *playerMovement};

    return true;
}

bool tryRevertGame(Game *game)
{
    if (game->cancelAmount <= 0)
        return false;
    if (game->localMovement == 0)
        return false;

    MoveInfo *lastMove = &game->lastMove;
    Vec2i backMovement = scalarVec(&lastMove->moveVec, -1);
    if (lastMove->pushed)
    {
        Vec2i nextPos = addVec(&game->map->playerPos, &lastMove->moveVec);
        Vec2i *pack = findElement(game->map->packs, &nextPos, compareVec2i);
        *pack = addVec(pack, &backMovement);
    }
    game->map->playerPos = addVec(&game->map->playerPos, &backMovement);

    return true;
}

bool updateGame(Game *game, clock_t elapsed, InputCommand command)
{
    game->localPassedTime += elapsed;
    game->totalPassedTime += elapsed;
    switch (command.commandType)
    {
    case MOVE:
        if (tryMove(game, &command.commandValue.vec))
        {
            game->localMovement++;
            game->totalMovement++;
            sortList(game->map->packs, compareVec2i);
        }
        break;

    case CHANGE_STAGE:
        clrscr();
        resetMap(game, command.commandValue.nextMap);
        break;

    case RESET:
        if (tryRevertGame(game))
        {
            game->cancelAmount--;
            game->localMovement--;
            game->totalMovement--;
            sortList(game->map->packs, compareVec2i);
        }
        break;

    case EXIT:
        return false;

    case NONE:
    default:
        break;
    }

    return true;
}

void runGame(Game *game, int fps)
{
    int milliSecPerFrame = (int)((1.0 / fps) * 1000);

    int stage = 0;
    char mapName[100];
    sprintf(mapName, "Stage %d", stage + 1);

    clock_t before = clock();

    FILE *stream = stdout;
    printGame(game, mapName, stream);
    while (true)
    {
        clock_t now = clock();
        clock_t elapsedClock = now - before;
        int elapsed = elapsedClock * 1000 / CLOCKS_PER_SEC;

        if (elapsed <= milliSecPerFrame)
            delay(milliSecPerFrame - elapsed);

        now = clock();
        elapsed = now - before;
        before = now;

        InputCommand command;

        if (!_kbhit())
            command.commandType = NONE;
        else
        {
            int c = _getch();
            switch (c)
            {
            case KEY_RIGHT:
                command.commandType = MOVE;
                command.commandValue.vec = (Vec2i){0, 1};
                break;
            case KEY_LEFT:
                command.commandType = MOVE;
                command.commandValue.vec = (Vec2i){0, -1};
                break;
            case KEY_UP:
                command.commandType = MOVE;
                command.commandValue.vec = (Vec2i){-1, 0};
                break;
            case KEY_DOWN:
                command.commandType = MOVE;
                command.commandValue.vec = (Vec2i){1, 0};
                break;

            case KEY_ESC:
                command.commandType = EXIT;
                break;

            case 'z':
            case 'Z':
                command.commandType = RESET;
                break;

            case '1':
            case '2':
            case '3':
                stage = c - '0' - 1;
                sprintf(mapName, "Stage %d", stage + 1);
                command.commandType = CHANGE_STAGE;
                command.commandValue.nextMap = getEmbeddedStage(stage);
                break;

            case 'l':
            case 'L':
            {
                clrscr();
                char filename[100];
                showcursor(true);
                printf("Enter file name: ");
                scanf(" %s", filename);
                showcursor(false);
                Map *map = loadMapFromFile(filename);
                if (map == NULL)
                {
                    printf("맵 파일을 열 수 없습니다.\n");
                    for (int i = 0; i < 3; ++i)
                    {
                        printf("\r기존 게임으로 돌아갑니다 %d...", 3 - i);
                        delay(1000);
                    }
                    clrscr();
                    command.commandType = NONE;
                    break;
                }
                command.commandType = CHANGE_STAGE;
                command.commandValue.nextMap = map;
                stage = -1;
                sprintf(mapName, "file: %s", filename);
                break;
            }

            default:
                command.commandType = NONE;
                break;
            }
        }
        if (!updateGame(game, elapsed, command))
            break;
        if (checkClear(game->map))
        {
            if (++stage > 3)
                stage = 0;
            resetMap(game, getEmbeddedStage(stage));

            sprintf(mapName, "Stage %d", stage + 1);

            clrscr();
            for (int i = 0; i < 3; ++i)
            {
                printf("\r축하합니다! 다음 스테이지로 이동합니다 %d...", 3 - i);
                delay(1000);
            }
            clrscr();
        }
        printGame(game, mapName, stream);
    }
}

/**********************************************************************************************************************/
//                                                      메인 함수

int main()
{
    showcursor(false);
    Game *game = newGame(getEmbeddedStage(0));
    runGame(game, 60);
    freeGame(game);
}
