def next_secret(n):
    n = ((n * 64) ^ n) % 16777216
    n ^= n // 32
    n = (n ^ (n * 2048)) % 16777216
    return n

with open("input") as input:
    nums = [int(n) for n in input.read().split('\n')[:-1]]

sum = 0
monkey_prices = []
for num in nums:
    diffs = []
    prices = {}
    for i in range(2000):
        num_prev = num
        num = next_secret(num)
        diffs.append((num%10) - (num_prev%10))
        if i > 2:
            dif4 = (diffs[-4], diffs[-3], diffs[-2], diffs[-1])
            if dif4 not in prices:
                prices[dif4] = num%10
    monkey_prices.append(prices)
    sum += num

print(f"The sum is {sum}")

price_max = 0
seq_max = None
for d3 in range(-9, 10):
    for d2 in range(-9, 10):
        for d1 in range(-9, 10):
            for d0 in range(-9, 10):
                total_price = 0
                d = (d3, d2, d1, d0)
                for prices in monkey_prices:
                    if d in prices:
                        total_price += prices[d]
                if total_price > price_max:
                    price_max = total_price
                    seq_max = d
print(price_max)
