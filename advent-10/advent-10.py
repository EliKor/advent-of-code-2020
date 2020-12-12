from collections import defaultdict

adaptors = []
with open("input.txt", 'r') as file:
    adaptors = [int(line) for line in file.readlines()]

def part1(adaptors):
    adaptors.append(0)
    adaptors = sorted(adaptors)
    diffs = [0] * 4
    for i in range(1, len(adaptors)):
        diffs[adaptors[i] - adaptors[i-1]] += 1
    print("Multiplied counts: ", diffs[1] * (diffs[3]+1))

def part2(adaptors):
    adaptors.append(0)
    adaptors = sorted(adaptors)
    d = defaultdict(int)
    d[adaptors[-1]] = 1
    for adaptor in adaptors[::-1]:
        for i in range(1,4):
            d[adaptor] += d[adaptor + i]
    print("Total Num Ways: ", d[0])

if __name__ == "__main__":
    part1(adaptors.copy())
    part2(adaptors.copy())
