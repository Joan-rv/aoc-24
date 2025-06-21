from heapq import heappop, heappush

with open("input") as input:
    data = input.read().split('\n')

n = int(data[0])
b = int(data[1])
points = [x.split(',') for x in data[2:-1]]
points = [(int(x[0]), int(x[1])) for x in points]
grid = [[False for _ in range(n)] for _ in range(n)]
for i in range(n):
    for j in range(n):
        grid[i][j] = (j,i) in points[:b]
        #grid[i][j] = ((j, i) in points)

for i in range(n):
    for j in range(n):
        if grid[i][j]:
            print('#', end='')
        else:
            print('.', end='')
    print()
print()


def dijkstra(grid, n):
    queue = []
    dirs = [(0,1), (1,0), (0,-1), (-1, 0)]
    heappush(queue, (0, 0, 0, dirs[0], [(0,0)]))
    dist = {}
    while queue:
        qd, qi, qj, qdir, qpath = heappop(queue)
        if (qdir, qi, qj) in dist:
            continue
        dist[(qdir, qi, qj)] = qd

        if (qi,qj) == (n-1, n-1):
            #path_tiles.update(qpath)
            return set(qpath), qd
        for dir in dirs:
            if dir[0] == -qdir[0] and dir[1] == -qdir[1]:
                continue
            i, j = qi+dir[0], qj+dir[1]
            path = [*qpath,(i,j)]
            if i < 0 or j < 0 or i >= n or j >= n:
                continue
            elif grid[i][j] == True:
                continue
            heappush(queue, (qd + 1,i,j,dir,path))
    return None, None

path, d = dijkstra(grid, n)
print(d)
for i in range(n):
    for j in range(n):
        if (i, j) in path:
            print('O', end='')
        else:
            if grid[i][j]:
                print('#', end='')
            else:
                print('.', end='')
    print("")
print()

b -= 1
while (d != None):
    while (points[b][1], points[b][0]) not in path:
        b += 1
        j, i = points[b]
        grid[i][j] = True
    path, d = dijkstra(grid, n)
print(points[b])
