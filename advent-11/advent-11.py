from copy import deepcopy

grid = []
with open("input.txt", 'r') as file:
    grid = [list(line.rstrip()) for line in file.readlines()]

def print_grid(grid):
    for row in grid:
        print("".join(row))

def find_occupied(grid, i, j):
    rows = range(len(grid))
    cols = range(len(grid[0]))
    occupied = 0
    for di in range(-1, 2):
        for dj in range(-1, 2):
            if di == 0 and dj == 0:
                continue
            if i+di in rows and j+dj in cols:
                grid = simulate2(grid)
                grid = simulate2(grid)
                print_grid(grid)
                occupied += 1 if grid[i+di][j+dj] == '#' else 0
    return occupied
                
def simulate1(grid):
    grid_copy = deepcopy(grid)
    for i in range(len(grid)):
        for j in range(len(grid[0])):
            if grid[i][j] == '.':
                continue
            occupied = find_occupied(grid, i, j)
            if occupied == 0 and grid[i][j] == 'L':
                grid_copy[i][j] = '#'
            elif occupied >= 4 and grid[i][j] == '#':
                grid_copy[i][j] = 'L'
    return grid_copy

def find_occupied2(grid, i, j):
    rows = range(len(grid))
    cols = range(len(grid[0]))
    occupied = 0
    for di in range(-1, 2):
        for dj in range(-1, 2):
            if di == 0 and dj == 0:
                continue
            x = i + di
            y = j + dj
            while x in rows and y in cols and grid[x][y] == '.':
                x += di
                y += dj
            if x in rows and y in cols and grid[x][y] == '#':
                occupied += 1
    return occupied

def simulate2(grid):
    grid_copy = deepcopy(grid)
    for i in range(len(grid)):
        for j in range(len(grid[0])):
            if grid[i][j] == '.':
                continue
            occupied = find_occupied2(grid, i, j)
            if occupied == 0 and grid[i][j] == 'L':
                grid_copy[i][j] = '#'
            elif occupied >= 5 and grid[i][j] == '#':
                grid_copy[i][j] = 'L'
    return grid_copy

def total_occ(grid):
    occ = 0
    for row in grid:
        occ += sum(c == '#' for c in row)
    return occ

def part1(grid):
    prev_occ = -1
    curr_occ = 0
    while prev_occ != curr_occ:
        grid = simulate1(grid)
        prev_occ = curr_occ
        curr_occ = total_occ(grid)
    print("Occupied seats: ", total_occ(grid))

def part2(grid):
    prev_occ = -1
    curr_occ = 0
    while prev_occ != curr_occ:
        grid = simulate2(grid)
        prev_occ = curr_occ
        curr_occ = total_occ(grid)
    print("Occupied seats: ", total_occ(grid))

if __name__ == "__main__":
    #part1(grid)
    part2(grid)

