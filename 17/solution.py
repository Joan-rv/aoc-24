with open("input") as f:
    data = f.read().split('\n')

ra = int(data[0][12:])
rb = int(data[1][12:])
rc = int(data[2][12:])

prog = [int(x) for x in data[4][9:].split(',')]

def part1(ra, rb, rc):
    global prog
    pc = 0
    out = []
    while pc < len(prog):
        op = prog[pc]
        arg = prog[pc+1]
        lit = arg
        comb = arg
        pc += 2
        if comb > 3:
            if comb == 4:
                comb = ra
            elif comb == 5:
                comb = rb
            elif comb == 6:
                comb = rc

        if op == 0:
            ra >>= comb
        elif op == 1:
            rb ^= lit 
        elif op == 2:
            rb = comb % 8
        elif op == 3 and ra != 0:
            pc = lit
        elif op == 4:
            rb ^= rc
        elif op == 5:
            out.append(comb % 8)
        elif op == 6:
            rb = ra >> comb 
        elif op == 7:
            rc = ra >> comb 
    return out

def part2():
    ra = 0
    n = 5
    out = part1(ra, rb, rc)
    while (prog != out):
        print(ra, end='\r')
        if (out[:n] == prog[:n]):
            n += 1
        ra += pow(8, n - 5)
        out = part1(ra, rb, rc)
    print(ra)

print(",".join([str(x) for x in part1(ra, rb, rc)]))
part2()
