import numpy as np
from itertools import product, combinations
from io import StringIO
import openpyxl

# 파일에서 읽어오기
import json

# 타입을 명확하게 설정하기 위한 것. 실제 코드와는 무관함.
import numpy.typing as npt
from typing import Optional

###################################################
# 입력받을 행렬
#             | 재료1 재료2 재료3 재료4 ...
# ------------+--------------------------
#  calorie/g  |
# nutrient1/g |
# nutrient2/g |
# nutrient3/g |
#     ...     |
#       tb/g  |
# = A
#
# 최소 조건
#        _             _
#       |               |
#       | calorie_min   |
#       | nutrient1_min |
# min = | nutrient2_min |
#       | nutrient3_min |
#       |      ...      |
#       |_             _|
#
#      _    _
#     |      |
#     |  w1  |
# w = |  w2  |
#     |  ... |
#     |_    _|
#
#       _               _
#      |                 |
#      | calorie total   |
#      | nutrient1 total |
# Aw = | nutrient2 total |
#      | nutrient3 total |
#      | tb total        |
#      |_               _|
#
###################################################


# 주어진 재료 하나만으로 기준치를 달성하기 위해 필요한 양 계산
def calc_min_quantities(criteria: npt.NDArray, A: npt.NDArray):
    result = []
    for column in range(A.shape[1]):
        result.append(np.max(criteria / A[:-1, column]))
    return np.array(result)


# 기준에 따라 n등분
def divide_scalar(start_value: float, end_value: float, n: int):
    interval = (end_value - start_value) / n
    for i in range(n):
        yield start_value + ((0.5 + i) * interval)


# 기준에 따라 벡터를 n^(차원) 등분
def divide_vector(start_vector: npt.NDArray, end_vector: npt.NDArray, n: int):
    return np.column_stack(
        list(
            product(
                *[
                    divide_scalar(start, end, n)
                    for start, end in zip(start_vector, end_vector)
                ]
            )
        )
    )


# 기준 범위 내에서 n등분한 벡터들 중 최고를 찾기
def calc_minimum_tb_area(
    A: npt.NDArray,
    start_vector: npt.NDArray,
    end_vector: npt.NDArray,
    criteria: npt.NDArray,
    n: int,
):
    vectors = divide_vector(start_vector, end_vector, n)
    results = A @ vectors

    for index in np.argsort(results[-1, :]):
        if np.all(results[:-1, index] >= criteria):
            return vectors[:, index]


# 기준 범위를 자동 설정, 일정 횟수 반복
def calc_best(
    A: npt.NDArray,
    criteria: npt.NDArray,
    n: int = 100,
    loop_count: int = 10,
    min_vector: Optional[npt.NDArray] = None,
    max_vector: Optional[npt.NDArray] = None,
):
    if min_vector is None:
        min_vector = np.zeros((A.shape[1]))
    if max_vector is None:
        max_vector = calc_min_quantities(criteria, A)

    min_vector = np.maximum(np.zeros((A.shape[1])), min_vector)
    max_vector = np.minimum(calc_min_quantities(criteria, A), max_vector)

    # 이미 최소 양만으로 충족
    if np.any(max_vector < min_vector):
        return min_vector

    startVector = min_vector.copy()
    endVector = max_vector.copy()
    min_local = None

    for i in range(loop_count):
        block_size = (endVector - startVector) / n
        min_local = calc_minimum_tb_area(A, startVector, endVector, criteria, n)

        print(f"\r[{i:03d}] {min_local=}, {block_size=}", end="")

        if min_local is None:
            break
        startVector = np.maximum(min_local - block_size * 1.5, min_vector)
        endVector = np.minimum(min_local + block_size * 1.5, max_vector)
    # print()
    return min_local


def read_from_input():
    food_count = int(input("Enter the number of food: "))
    print()

    kcal_per_g = [
        int(input(f"Enter calorie(kcal/g) of food #{i+1}: ")) for i in range(food_count)
    ]
    print()

    nutrient_count = int(input("Enter the number of nutrients: "))
    mg_per_g = [
        [
            int(input(f"Enter {n + 1}th nutrients(mg/g) of food #{i+1}: "))
            for i in range(food_count)
        ]
        for n in range(nutrient_count)
    ]
    print()

    tb_per_g = [int(input(f"Enter tb/g of food #{i+1}: ")) for i in range(food_count)]
    print()

    min_foods = np.array(
        [int(input(f"Enter minimum amount food #{i+1}: ")) for i in range(food_count)]
    )
    print()

    max_foods = np.array(
        [int(input(f"Enter maximum amount food #{i+1}: ")) for i in range(food_count)]
    )
    print()

    kcal_min = int(input("Enter the minimum value of calorie: "))
    mg_min = [
        int(input(f"Enter the minimum value of the {i + 1}th nutrients: "))
        for i in range(nutrient_count)
    ]
    print()

    # 사용자가 설정하게 하고 싶으면 주석 해제
    n = 10
    loop_count = 100
    # n = int(input("Enter n(The number of division): "))
    # loop_count = int(input("Enter loop count: "))

    A = np.array([kcal_per_g, *mg_per_g, tb_per_g])
    criteria = np.array([kcal_min, *mg_min])

    comb = int(input("Enter the number of foods to be seleted: "))

    for indexes in combinations(range(food_count), comb):
        print("-" * 50)

        best_vector = calc_best(
            A[:, indexes],  # type: ignore
            criteria,
            n,
            loop_count,
            min_foods.take(indexes),
            max_foods.take(indexes),
        )

        if best_vector is None:
            continue

        for i, index in enumerate(indexes):
            print(f"Food#{index + 1}: {best_vector[i]}")
        best_result = A[:, indexes] @ best_vector  # type: ignore
        print(f"Total calories: {best_result[0]}")
        for i in range(best_result.shape[0] - 2):
            print(f"Total nutrients #{i + 1}: {best_result[i + 1]}")
        print(f"Total tb: {best_result[-1]}")


def main():
    filename = input("Enter file name: ")
    tb_list = []
    with open(filename, "r") as f:
        data: dict = json.load(f)
        ingridients = []
        A = []
        min_ingridient_amount = []
        max_ingridient_amount = []
        for k, v in data["ingridients"].items():
            ingridients.append(k)
            A.append([v["calorie"], *v["nutrients"], v["tb"]])
            min_ingridient_amount.append(v["minimum"])
            max_ingridient_amount.append(v["maximum"])

        A = np.column_stack(A)
        min_ingridient_amount = np.array(min_ingridient_amount)
        max_ingridient_amount = np.array(max_ingridient_amount)

        criteria = np.array(
            [data["criteria"]["calorie"], *data["criteria"]["nutrients"]]
        )
        comb = data["settings"]["number_of_selection"]
        n = data["settings"]["vector_divide"]
        loop_count = data["settings"]["loop_count"]

        s = StringIO()

        for indexes in combinations(range(len(ingridients)), comb):
            result = calc_best(
                A[:, indexes],  # type: ignore
                criteria,
                n,
                loop_count,
                min_ingridient_amount.take(indexes),
                max_ingridient_amount.take(indexes),
            )
            if result is None:
                continue

            print("-" * 50, file=s)
            for i, index in enumerate(indexes):
                print(f"{ingridients[index]}: {result[i]}", file=s)
            calced_result = A[:, indexes] @ result  # type: ignore
            print(f"Total calories: {calced_result[0]}", file=s)
            for i in range(calced_result.shape[0] - 2):
                print(f"Total nutrients #{i + 1}: {calced_result[i + 1]}", file=s)
            print(f"Total tb: {calced_result[-1]}", file=s)
            tb_list.append(calced_result[-1])

        print()
        result = s.getvalue()
        print(result)
        with open("lastResult.txt", "w") as fw:
            print(result, file=fw)

    wb = openpyxl.Workbook()
    ws = wb.active
    for i, tb in enumerate(tb_list):
        ws.cell(i + 1, 1, tb)
    wb.save("./results.xlsx")


if __name__ == "__main__":
    main()
