with open("input") as f:
    data = f.read().split('\n')[:-1]
towel_avail = data[0].split(", ")

memo = {}
def find_towel_comb(towel, towel_avail):
    num = 0
    if towel in memo:
        return memo[towel]
    if towel == "":
        return 1
    for t_avail in  towel_avail:
        n = len(t_avail)
        if t_avail == towel[:n]:
            num += find_towel_comb(towel[n:], towel_avail)
    memo[towel] = num 
    return num

sum = 0
comb_sum = 0
for towel in data[2:]:
    combs = find_towel_comb(towel, towel_avail)
    if combs != 0:
        print(towel)
        sum += 1
        comb_sum += combs
print(sum)
print(comb_sum)
