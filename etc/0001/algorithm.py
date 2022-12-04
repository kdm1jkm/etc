import numpy as np
from itertools import product, combinations

# 타입을 명확하게 설정학 위한 것. 실제 코드와는 무관함.
import numpy.typing as npt
from typing import Optional

###################################################
# 입력받을 행렬
#            | food1 food2 food3 ...
# -----------+------------------------
#  calorie/g |
# nutrient/g |
#       tb/g |
# = A
#
# 최소 조건
#        _            _
#       |              |
# min = | calorie_min  |
#       | nutrient_min |
#       |_            _|
#
#      _    _
#     |      |
#     |  w1  |
# w = |  w2  |
#     |  w3  |
#     |  ... |
#     |_    _|
#
#       _              _
#      |                |
#      | calorie total  |
# Aw = | notrient total |
#      | tb total       |
#      |_              _|
#
###################################################


def calc_min_quantities(criteria: npt.NDArray, A: npt.NDArray):
    result = []
    for column in range(A.shape[1]):
        result.append(np.max(criteria / A[:-1, column]))
    return np.array(result)


def divide_scalar(start_value: float, end_value: float, n: int):
    interval = (end_value - start_value) / n
    for i in range(n):
        yield start_value + ((0.5 + i) * interval)


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

    if np.any(max_vector < min_vector):
        return min_vector

    startVector = min_vector.copy()
    endVector = max_vector.copy()
    min_local = None

    for i in range(loop_count):
        block_size = (endVector - startVector) / n
        min_local = calc_minimum_tb_area(A, startVector, endVector, criteria, n)

        if min_local is None:
            break

        startVector = np.maximum(min_local - block_size * 1.5, min_vector)
        endVector = np.minimum(min_local + block_size * 1.5, max_vector)
        print(f"\r[{i:03d}] {min_local=}, {block_size=}", end="")
    print()
    return min_local


def test_min_quantity():
    a = calc_min_quantities(
        np.array([800, 600]), np.array([[10, 15, 20], [15, 10, 20], [100, 150, 170]])
    )
    print(a)


def test_divide():
    print(*divide_vector(np.array([1, 1, 2]), np.array([3, 3, 4]), 2))


def test_minimum_tb():
    A = np.array([[10, 15, 20], [15, 10, 20], [100, 150, 200]])
    criteria = np.array([800, 600])
    print(
        calc_minimum_tb_area(
            A, np.array([0, 0, 0]), calc_min_quantities(criteria, A), criteria, 10
        )
    )


def test_minimum_tb2():
    A = np.array([[10, 15], [15, 10], [100, 150]])
    criteria = np.array([100, 100])
    print(
        calc_minimum_tb_area(
            A, np.array([0, 0]), calc_min_quantities(criteria, A), criteria, 10
        )
    )


def test_calc_best():
    A = np.array([[10, 15], [15, 10], [100, 150]])
    criteria = np.array([800, 600])
    best = calc_best(A, criteria, 100, 100)
    print(f"{best=}")
    print(f"{A @ best=}")


def test():
    print("-" * 50)
    print("MINIMUM_QUANTITY")
    test_min_quantity()

    print("-" * 50)
    print("DIVIDE")
    test_divide()

    print("-" * 50)
    print("MINIMUM_TB")
    test_minimum_tb()

    print("-" * 50)
    print("MINIMUM_TB2")
    test_minimum_tb2()

    print("-" * 50)
    print("CALC_BEST")
    test_calc_best()


def main():
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


if __name__ == "__main__":
    main()
