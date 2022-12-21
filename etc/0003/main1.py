import math
import ast


def isthere_block(A, B, block):
    if (
        max(A[0], B[0]) < block[0]
        or min(A[0], B[0]) > block[0]
        or max(A[1], B[1]) < block[1]
        or min(A[1], B[1]) > block[1]
    ):
        return False
    else:
        if (block[0] - A[0]) * (block[1] - B[1]) == (block[0] - B[0]) * (
            block[1] - A[1]
        ):
            return True
        else:
            return False


def distance(A, B):
    dx = A[0] - B[0]
    dy = A[1] - B[1]
    dist = math.sqrt(dx**2 + dy**2)
    return dist


def min_cost(start, locations, block):
    min_index = 0
    second_min_index = 0
    min_dist = float("inf")
    second_min_dist = float("inf")
    for i in range(len(locations)):
        dist = distance(locations[i], start)
        if dist == 0:
            continue
        for j in block:
            if isthere_block(locations[i], start, j) == True:
                dist += 10
                break
        if dist < min_dist:
            second_min_dist = min_dist
            second_min_index = min_index
            min_dist = dist
            min_index = i
        elif dist < second_min_dist:
            second_min_dist = dist
            second_min_index = i
    return min_index, second_min_index


locations_dict = ast.literal_eval(input())
locations = list(locations_dict.values())
locations_key = list(locations_dict.keys())
block = ast.literal_eval(input())
N = int(input())
tour_locations = []
start = locations[0]
start_loc = locations_key[0]
tour_locations.append(start_loc)
print(locations)

for i in range(N):
    for k in range(len(locations)):
        if locations[k] == start:
            del locations_key[k]
            del locations[k]
            break
    min_index, second_min_index = min_cost(start, locations, block)
    if (i + 1) % 3 == 0:
        start = locations[second_min_index]
        start_loc = locations_key[second_min_index]
    else:
        start = locations[min_index]
        start_loc = locations_key[min_index]
    tour_locations.append(start_loc)

print(f"Final Position: {tour_locations[-1]}")
print("Path: ", end="")
print(*tour_locations, sep=" ==> ")
