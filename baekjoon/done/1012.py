from dataclasses import dataclass
from typing import Iterable, List, Set
from queue import Queue


@dataclass(frozen=True)
class Pos:
    row: int
    column: int


def new_poses(pos: Pos):
    return [
        Pos(pos.row + 1, pos.column),
        Pos(pos.row - 1, pos.column),
        Pos(pos.row, pos.column + 1),
        Pos(pos.row, pos.column - 1),
    ]


class Board:
    def __init__(self, rows: int, columns: int, baechus: Iterable[Pos]) -> None:
        self.rows = rows
        self.columns = columns
        self.baechus = list(baechus)

    def validate_pos(self, pos: Pos):
        return pos.row in range(0, self.rows) and pos.column in range(0, self.columns)

    def group(self):
        baechu_queue: Queue[Pos] = Queue()
        group: List[Set[Pos]] = []

        while len(self.baechus) > 0:
            if baechu_queue.empty():
                group.append(set())
                bachu = self.baechus.pop()
                baechu_queue.put(bachu)
                group[-1].add(bachu)

            for new_baechu in new_poses(baechu_queue.get()):
                if not self.validate_pos(new_baechu):
                    continue

                if not new_baechu in self.baechus:
                    continue

                self.baechus.remove(new_baechu)
                group[-1].add(new_baechu)
                baechu_queue.put(new_baechu)

        return group


def main():
    t: int = int(input())

    for _ in range(t):
        m, n, k = [int(v) for v in input().split()]
        bachus = []
        for _ in range(k):
            r, c = [int(v) for v in input().split()]
            bachus.append(Pos(r, c))
        board = Board(m, n, bachus)
        group = board.group()
        print(len(group))


if __name__ == "__main__":
    main()
