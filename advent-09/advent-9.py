from itertools import combinations

vals = []
with open("input.txt", 'r') as file:
    vals = [int(line) for line in file.readlines()]

def part1(vals):
    for i in range(0, len(vals)-26):
        sums = set([a+b for a,b in combinations(vals[i:i+26], 2)])
        if vals[i+26] not in sums:
            print("First invalid value: ", vals[i+26])
            return

def part2(vals):
    TARGET = 177777905
    for i in range(0, len(vals)):
        for j in range(i+1, len(vals)):
            if sum(vals[i:j+1]) == TARGET:
                print("Vulnerability: ", min(vals[i:j+1]) + max(vals[i:j+1]))
                return
            elif sum(vals[i:j+1]) > TARGET:
                break


if __name__ == "__main__":
    part1(vals)
    part2(vals)
