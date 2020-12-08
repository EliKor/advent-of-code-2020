with open("input.txt") as file:
    count = 0
    fields = set() 
    valid_fields = set(["byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"])
    for line in file.readlines():
        if line == "\n":
            if len(fields) == 8 or (len(fields) == 7 and (not ("cid" in fields))):
                count += 1
            fields = set()
            continue
        line_fields = set()
        for key_val in line.split(" "):
            line_fields.add(key_val[:3])
        fields = fields.union(line_fields)
    if len(fields) == 8 or (len(fields) == 7 and (not ("cid" in fields))):
        count += 1
    print(count)
