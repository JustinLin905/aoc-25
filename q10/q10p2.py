#!/usr/bin/python3
import sys
from functools import cache
from collections import defaultdict, Counter, deque
import z3

D = sys.stdin.read()
p2 = 0
for line in D.splitlines():
    words = line.split()

    buttons = words[1:-1]
    button_indices = []
    for button in buttons:
        indices = [int(x) for x in button[1:-1].split(",")]
        button_indices.append(indices)

    # solve Ax = B
    # where A = effect of each button
    # x = how many times we press each button
    # B = goal state
    # minimize(sum(X))
    joltage_string = words[-1]
    joltages = [int(x) for x in joltage_string[1:-1].split(",")]
    V = []
    for i in range(len(buttons)):
        V.append(z3.Int(f"B{i}"))
    EQ = []
    for i in range(len(joltages)):
        terms = []
        for j in range(len(buttons)):
            if i in button_indices[j]:
                terms.append(V[j])
        eq = sum(terms) == joltages[i]
        EQ.append(eq)
    o = z3.Optimize()
    o.minimize(sum(V))
    for eq in EQ:
        o.add(eq)
    for v in V:
        o.add(v >= 0)
    assert o.check()
    M = o.model()
    for d in M.decls():
        # print(d.name(), M[d])
        p2 += M[d].as_long()

print(p2)
