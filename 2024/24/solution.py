from itertools import product
from math import log2
with open("input") as f:
    signals_raw, gates_raw = f.read().split("\n\n")
signals = {}
for signal in signals_raw.split('\n'):
    name, value = signal.split(': ')
    signals[name] = int(value)
gates = set()
for gate in gates_raw.split('\n')[:-1]:
    input, output = gate.split(" -> ")
    gates.add((*input.split(' '), output))

def find_output(gates, signals):
    gates_processed = set()
    while gates != gates_processed:
        for gate in gates:
            s1, g, s2, o = gate
            if s1 in signals and s2 in signals and o not in signals:
                if g == "AND":
                    r = signals[s1] & signals[s2]
                elif g == "OR":
                    r = signals[s1] | signals[s2]
                elif g == "XOR":
                    r = signals[s1] ^ signals[s2]
                signals[o] = r
                gates_processed.add(gate)

def signal_to_dec(c, signals):
    i = 0
    r = 0
    while f"{c}{i:02}" in signals:
        r |= signals[f"{c}{i:02}"] << i
        i += 1
    return r
def part1():
    new_signals = signals.copy()
    find_output(gates, new_signals)
    print(signal_to_dec('z', new_signals))

out_to_ins = {}
for gate in gates:
    out_to_ins[gate[3]] = (frozenset({gate[0], gate[2]}), gate[1])
ins_to_out = {}
for out in out_to_ins:
    s, g = out_to_ins[out]
    ins_to_out[(s, g)] = out
'''
def part2():
    new_signals = signals.copy()
    find_output(gates, new_signals)
    z = signal_to_dec('z', new_signals)
    x = signal_to_dec('x', signals)
    y = signal_to_dec('y', signals)
    if TEST:
        correct_z = x & y
    else:
        correct_z = x + y
    print(f"{z} ?= {correct_z}")
    i = 1
    wrong_outs = []
    while i < z or i < correct_z:
        if z & i != correct_z & i:
            wrong_outs.append(f"z{int(log2(i)):02}")
        i = i << 1
    new_wrong_outs = wrong_outs
    while True:
        old_wrong_outs = new_wrong_outs
        new_wrong_outs = []
        for old_wrong_out in old_wrong_outs:
            if old_wrong_out in out_to_ins:
                for out in out_to_ins[old_wrong_out]:
                    if out in out_to_ins:
                        new_wrong_outs.append(out)
        if new_wrong_outs == []:
            break
        wrong_outs = [*wrong_outs, *new_wrong_outs]
    print(wrong_outs)
'''
# found comparing circuit to full-adder
known_carry = {
        21: "sjk",
}
def part2():
    c = "mcg"
    for i in range(1, 45):
        z = f"z{i:02}"
        x = f"x{i:02}"
        y = f"y{i:02}"
        try:
            and_c2 = ins_to_out[frozenset({x, y}), "AND"]
            xor_c = ins_to_out[frozenset({x, y}), "XOR"]
            xor_s = ins_to_out[frozenset({xor_c, c}), "XOR"]
            if xor_s != z:
                print(i)
                c = known_carry[i]
                continue
            and_c1 = ins_to_out[frozenset({xor_c, c}), "AND"]
            c = ins_to_out[frozenset({and_c2, and_c1}), "OR"]
        except KeyError:
            print(i)
            c = known_carry[i]



part1()
part2()
