with open("input") as f:
    keys_and_locks = f.read().split("\n\n")
keys_and_locks[-1] = keys_and_locks[-1][:-1]

def lock_txt_to_num(lock_txt):
    lock = [0, 0, 0, 0, 0]
    for i, l in enumerate(lock_txt):
        for j, c in enumerate(l):
            if c == '#':
                lock[j] = i
    return lock

locks = []
keys = []

for key_or_lock in keys_and_locks:
    if key_or_lock[0:5] == "#####":
        locks.append(lock_txt_to_num(key_or_lock.split("\n")))
    else:
        keys.append(lock_txt_to_num(key_or_lock.split("\n")[::-1]))

print(locks)
print(keys)

sum = 0
for lock in locks:
    for key in keys:
        fits = [x+y <= 5 for x, y in zip(lock, key)]
        if all(fits):
            sum += 1
print(f"There are {sum} lock/key pairs that fit")
