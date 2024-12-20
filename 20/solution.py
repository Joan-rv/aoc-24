from heapq import heappop, heappush

input = open("input")
grid = input.read().split('\n')[:-1]
n = len(grid)
m = len(grid[0])

for l in grid:
    print(l)
print()

for i in range(n):
    for j in range(m):
        if grid[i][j] == 'S':
            s_0 = (i, j)
            break

dirs = [(0,1), (1,0), (0,-1), (-1, 0)]
def dijkstra(grid):
    queue = []
    dist = {}
    heappush(queue, (0, *s_0, dirs[0], [s_0]))
    while queue:
        qd, qi, qj, qdir, qpath = heappop(queue)
        if (qdir, qi, qj) in dist and qd > dist[(qdir, qi, qj)]:
            continue
        dist[(qdir, qi, qj)] = qd

        if grid[qi][qj] == 'E':
            #for i in range(n):
            #    for j in range(m):
            #        if (i, j) in qpath:
            #            print('O', end='')
            #        else:
            #            print(grid[i][j], end='')
            #    print("")
            #print()
            return qd, qpath
        for dir in dirs:
            if dir[0] == -qdir[0] and dir[1] == -qdir[1]:
                continue
            i, j = qi+dir[0], qj+dir[1]
            path = [*qpath,(i,j)]
            if i < 0 or j < 0 or i >= n or j >= m:
                continue
            elif grid[i][j] == '#':
                continue
            heappush(queue, (qd + 1,i,j,dir,path))


searched = set()
def count_cheats(dirs):
    cheats = {}
    for k in range(len(path_orig)):
        i,j = path_orig[k]
        print("          ", end='\r')
        print(f"{k} / {len(path_orig)}", end='\r')
        for dir in dirs:
            i_new, j_new = (i+dir[0],j+dir[1])
            if (i, j, i_new, j_new) in searched:
                continue
            searched.add((i, j, i_new, j_new))
            if i_new < 0 or j_new < 0 or i_new >= n or j_new >= m:
                continue
            if (i_new, j_new) not in path_orig:
                continue
            saved = path_orig.index((i_new, j_new)) - k - abs(dir[0]) - abs(dir[1])
            if saved < 0:
                continue
            if saved in cheats:
                cheats[saved] += 1
            else:
                cheats[saved] = 1

    return cheats

d_orig, path_orig = dijkstra(grid)
dirs2 = [(x[0]*2, x[1]*2) for x in dirs]
dirs3 = []
for i in range(21):
    for j in range(21 - i):
        dirs3.append((i, j))
        dirs3.append((i, -j))
        dirs3.append((-i, j))
        dirs3.append((-i, -j))
cheats = count_cheats(dirs2)
searched = set()
cheats2 = count_cheats(dirs3)
sum = 0
for k in cheats:
    if k >= 100:
        sum += cheats[k]
    #print(f"number: {cheats[k]}, saved: {k}")

sum2 = 0
for k in cheats2:
    if k >= 100:
        sum2 += cheats2[k]
    if k >= 50:
        print(f"number: {cheats2[k]}, saved: {k}")
print(f"Part 1 sum at leat 100: {sum}")
print(f"Part 2 sum at leat 100: {sum2}")
