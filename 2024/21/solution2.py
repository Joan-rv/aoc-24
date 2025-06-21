with open("input.test") as f:
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
            while pos[1] != tgt_pos[1]:
                if (delta[1] < 0):
                    if (pos[0], pos[1]-1) != numeric_keypad[' ']:
                        moves_2 += '<'
                        pos = (pos[0], pos[1]-1) 
                    else:
                        break
                else:
                    break
            while pos[0] != tgt_pos[0]:
                if (delta[0] < 0):
                    moves_2 += '^'
                    pos = (pos[0]-1, pos[1])
                else:
                    break
            while pos[0] != tgt_pos[0]:
                if (delta[0] < 0):
                    break
                else:
                    if (pos[0]+1, pos[1]) != numeric_keypad[' ']:
                        moves_2 += 'v'
                        pos = (pos[0]+1, pos[1])
                    else:
                        break
            while pos[1] != tgt_pos[1]:
                if (delta[1] < 0):
                    break
                else:
                    moves_2 += '>'
                    pos = (pos[0], pos[1]+1)
        moves_2 += "A"
        total_moves = [move + moves_2 for move in total_moves]
    return total_moves, pos

def directional_press(code, pos):
    total_moves = [""]
    for digit in code:
        tgt_pos = directional_keypad[digit]
        pos_orig = pos
        moves_1 = ""
        moves_2 = ""
        delta = (tgt_pos[0]-pos[0], tgt_pos[1]-pos[1])
        '''
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
        '''
        pos = pos_orig
        while pos != tgt_pos:
            while pos[1] != tgt_pos[1]:
                if (delta[1] < 0):
                    if (pos[0], pos[1]-1) != directional_keypad[' ']:
                        moves_2 += '<'
                        pos = (pos[0], pos[1]-1) 
                    else:
                        break
                else:
                    break
            while pos[0] != tgt_pos[0]:
                if (delta[0] < 0):
                    moves_2 += '^'
                    pos = (pos[0]-1, pos[1])
                else:
                    break
            while pos[0] != tgt_pos[0]:
                if (delta[0] < 0):
                    break
                else:
                    if (pos[0]+1, pos[1]) != directional_keypad[' ']:
                        moves_2 += 'v'
                        pos = (pos[0]+1, pos[1])
                    else:
                        break
            while pos[1] != tgt_pos[1]:
                if (delta[1] < 0):
                    break
                else:
                    moves_2 += '>'
                    pos = (pos[0], pos[1]+1)
        moves_2 += "A"
        total_moves = [move + moves_2 for move in total_moves]
    return total_moves, pos

def to_numeric(code):
    return int("".join([x for x in code if x != 'A']))

def chunk_process(chunk, i):
    pos = (0, 2)
    if i >= 2:
        len_min = len(chunk)
        return len_min
    print(i, end='\r')
    directional_moves = []
    new_moves, pos = directional_press(chunk, pos)
    for move in new_moves:
        directional_moves.append(move)
    len_min = 0
    print(directional_moves)
    #for new_chunk in directional_moves[0].split('A'):
    for new_chunk in directional_moves:
        len_min += chunk_process(new_chunk, i+1)
    return len_min
sum = 0
for code in codes:
    len_tot = float("inf")
    pos_num = (3, 2)
    directional_moves_prev, pos_num = numeric_press(code, pos_num)
    directional_moves_prev = directional_moves_prev
    for moves in directional_moves_prev:
        len_tot = min(chunk_process(moves, 0), len_tot)
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
