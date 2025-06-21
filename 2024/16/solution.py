from heapq import heappop, heappush

input = open("input")
grid = input.read().split('\n')[:-1]
n = len(grid)
m = len(grid[0])

for l in grid:
    print(l)
print()

queue = []
dirs = [(0,1), (1,0), (0,-1), (-1, 0)]
heappush(queue, (0, n-2, 1, dirs[0], [(n-2,1)]))
dist = {}

path_tiles = set()
qd_min = None

while queue:
    qd, qi, qj, qdir, qpath = heappop(queue)
    if (qdir, qi, qj) in dist and qd > dist[(qdir, qi, qj)]:
        continue
    dist[(qdir, qi, qj)] = qd

    if grid[qi][qj] == 'E':
        if qd_min == None:
            qd_min = qd
        elif qd > qd_min:
            break
        #for i in range(n):
        #    for j in range(m):
        #        if (i, j) in qpath:
        #            print('O', end='')
        #        else:
        #            print(grid[i][j], end='')
        #    print("")
        #print()
        path_tiles.update(qpath)
    for dir in dirs:
        if dir[0] == -qdir[0] and dir[1] == -qdir[1]:
            continue
        i, j = qi+dir[0], qj+dir[1]
        path = [*qpath,(i,j)]
        if i < 0 or j < 0 or i >= n or j >= m:
            continue
        elif grid[i][j] == '#':
            continue
        if dir == qdir:
            heappush(queue, (qd + 1,i,j,dir,path))
        else:
            heappush(queue, (qd + 1001,i,j,dir,path))

print(qd_min)
print(len(path_tiles))
