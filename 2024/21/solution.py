with open("input") as f:
    codes = f.read().split('\n')[:-1]
print(codes)

numeric_keypad = {
    '7': (0, 0),
    '8': (0, 1),
    '9': (0, 2),
    '4': (1, 0),
    '5': (1, 1),
    '6': (1, 2),
    '1': (2, 0),
    '2': (2, 1),
    '3': (2, 2),
    ' ': (3, 0),
    '0': (3, 1),
    'A': (3, 2),
}

directional_keypad = {
    ' ': (0, 0),
    '^': (0, 1),
    'A': (0, 2),
    '<': (1, 0),
    'v': (1, 1),
    '>': (1, 2),
}

def numeric_press(code, pos):
    total_moves = [""]
    for digit in code:
        moves_1 = ""
        moves_2 = ""
        pos_orig = pos
        tgt_pos = numeric_keypad[digit]
        delta = (tgt_pos[0]-pos[0], tgt_pos[1]-pos[1])
        while pos != tgt_pos:
            while pos[1] != tgt_pos[1]:
                if (delta[1] < 0):
                    if (pos[0], pos[1]-1) != numeric_keypad[' ']:
                        moves_1 += '<'
                        pos = (pos[0], pos[1]-1)
                    else:
                        break
                else:
                    moves_1 += '>'
                    pos = (pos[0], pos[1]+1)
            while pos[0] != tgt_pos[0]:
                if (delta[0] < 0):
                    moves_1 += '^'
                    pos = (pos[0]-1, pos[1])
                else:
                    if (pos[0]+1, pos[1]) != numeric_keypad[' ']:
                        moves_1 += 'v'
                        pos = (pos[0]+1, pos[1])
                    else:
                        break
        moves_1 += "A"
        pos = pos_orig
        while pos != tgt_pos:
            while pos[0] != tgt_pos[0]:
                if (delta[0] < 0):
                    moves_2 += '^'
                    pos = (pos[0]-1, pos[1])
                else:
                    if (pos[0]+1, pos[1]) != numeric_keypad[' ']:
                        moves_2 += 'v'
                        pos = (pos[0]+1, pos[1])
                    else:
                        break
            while pos[1] != tgt_pos[1]:
                if (delta[1] < 0):
                    if (pos[0], pos[1]-1) != numeric_keypad[' ']:
                        moves_2 += '<'
                        pos = (pos[0], pos[1]-1)
                    else:
                        break
                else:
                    moves_2 += '>'
                    pos = (pos[0], pos[1]+1)
        moves_2 += "A"
        total_moves1 = [move + moves_1 for move in total_moves]
        total_moves2 = [move + moves_2 for move in total_moves]
        total_moves = list(set([*total_moves1, *total_moves2]))
    return total_moves, pos

memo = {}
def directional_press(code, pos):
    total_moves = [""]
    for digit in code:
        tgt_pos = directional_keypad[digit]
        pos_orig = pos
        if (digit, pos) in memo:
            moves_1, moves_2 = memo[(digit, pos)]
            pos = tgt_pos
        else:
            moves_1 = ""
            moves_2 = ""
            delta = (tgt_pos[0]-pos[0], tgt_pos[1]-pos[1])
            while pos != tgt_pos:
                while pos[1] != tgt_pos[1]:
                    if (delta[1] < 0):
                        if (pos[0], pos[1]-1) != directional_keypad[' ']:
                            moves_1 += '<'
                            pos = (pos[0], pos[1]-1)
                        else:
                            break
                    else:
                        moves_1 += '>'
                        pos = (pos[0], pos[1]+1)
                while pos[0] != tgt_pos[0]:
                    if (delta[0] < 0):
                        moves_1 += '^'
                        pos = (pos[0]-1, pos[1])
                    else:
                        if (pos[0]+1, pos[1]) != directional_keypad[' ']:
                            moves_1 += 'v'
                            pos = (pos[0]+1, pos[1])
                        else:
                            break
            moves_1 += "A"
            pos = pos_orig
            while pos != tgt_pos:
                while pos[0] != tgt_pos[0]:
                    if (delta[0] < 0):
                        moves_2 += '^'
                        pos = (pos[0]-1, pos[1])
                    else:
                        if (pos[0]+1, pos[1]) != numeric_keypad[' ']:
                            moves_2 += 'v'
                            pos = (pos[0]+1, pos[1])
                        else:
                            break
                while pos[1] != tgt_pos[1]:
                    if (delta[1] < 0):
                        if (pos[0], pos[1]-1) != numeric_keypad[' ']:
                            moves_2 += '<'
                            pos = (pos[0], pos[1]-1) 
                        else:
                            break
                    else:
                        moves_2 += '>'
                        pos = (pos[0], pos[1]+1)
            moves_2 += "A"
        memo[(digit, pos_orig)] = (moves_1, moves_2)
        if moves_1 != moves_2:
            total_moves1 = [move + moves_1 for move in total_moves]
            total_moves2 = [move + moves_2 for move in total_moves]
            total_moves = [*total_moves1, *total_moves2]
        else:
            total_moves = [move + moves_1 for move in total_moves]
        total_moves = total_moves
    return total_moves, pos

def to_numeric(code):
    return int("".join([x for x in code if x != 'A']))
sum = 0
for code in codes:
    len_tot = 0
    pos_num = (3, 2)
    for digit in code:
        directional_moves_prev, pos_num = numeric_press(digit, pos_num)
        directional_moves_prev = set(directional_moves_prev)
        pos = (0, 2)
        for i in range(2):
            print(i, end='\r')
            directional_moves = set()
            for moves in directional_moves_prev:
                new_moves, pos = directional_press(moves, pos)
                for move in new_moves:
                    directional_moves.add(move)
            len_min = min([len(x) for x in directional_moves])
            directional_moves = [x for x in directional_moves if len(x) == len_min]
            directional_moves_prev = directional_moves
        len_tot += len_min
    print(f"{len_tot} * {to_numeric(code)}")
    sum += len_tot * to_numeric(code)
print(f"Sum of all complexities: {sum}")


'''
def numeric_press(code):
    pos = (3, 2)
    moves = ""
    for digit in code:
        tgt_pos = numeric_keypad[digit]
        delta = (tgt_pos[0]-pos[0], tgt_pos[1]-pos[1])
        while pos != tgt_pos:
            while pos[1] != tgt_pos[1]:
                if (delta[1] < 0):
                    if (pos[0], pos[1]-1) != numeric_keypad[' ']:
                        moves += '<'
                        pos = (pos[0], pos[1]-1)
                    else:
                        break
                else:
                    moves += '>'
                    pos = (pos[0], pos[1]+1)
            while pos[0] != tgt_pos[0]:
                if (delta[0] < 0):
                    moves += '^'
                    pos = (pos[0]-1, pos[1])
                else:
                    if (pos[0]+1, pos[1]) != numeric_keypad[' ']:
                        moves += 'v'
                        pos = (pos[0]+1, pos[1])
                    else:
                        break
        moves += "A"
    return moves

def directional_press(directions):
    pos = (0, 2)
    moves = ""
    for direction in directions:
        tgt_pos = directional_keypad[direction]
        delta = (tgt_pos[0]-pos[0], tgt_pos[1]-pos[1])
        while pos != tgt_pos:
            while pos[1] != tgt_pos[1]:
                if (delta[1] < 0):
                    if (pos[0], pos[1]-1) != directional_keypad[' ']:
                        moves += '<'
                        pos = (pos[0], pos[1]-1)
                    else:
                        break
                else:
                    moves += '>'
                    pos = (pos[0], pos[1]+1)
            while pos[0] != tgt_pos[0]:
                if (delta[0] < 0):
                    if (pos[0]-1, pos[1]) != directional_keypad[' ']:
                        moves += '^'
                        pos = (pos[0]-1, pos[1])
                    else:
                        break
                else:
                    moves += 'v'
                    pos = (pos[0]+1, pos[1])
        moves += "A"
    return moves

for code in codes:
    moves = directional_press(directional_press(numeric_press(code)))
    print(moves)
    print(len(moves))
'''
