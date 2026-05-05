#!/usr/bin/python3
import os
import sys
from functools import cache
from collections import defaultdict, Counter, deque
import z3

current_dir = os.path.dirname(os.path.abspath(__file__))
with open(os.path.join(current_dir, "q10.txt"), "r") as f:
    D = f.read()

p2 = 0
for line in D.splitlines():
    words = line.split()

    buttons = words[1:-1]
    button_indices = []
    for button in buttons:
        indices = [int(x) for x in button[1:-1].split(",")]
        button_indices.append(indices)

    joltage_string = words[-1]
    joltages = [int(x) for x in joltage_string[1:-1].split(",")]

    # Create Z3 integers for each button
    x = []
    for i in range(len(buttons)):
        x.append(z3.Int(f"B{i}"))

    # Construct the requirements
    EQ = []
    for i in range(len(joltages)):
        terms = []
        for j in range(len(buttons)):
            if i in button_indices[j]:
                # Find each button that affects this joltage index
                terms.append(x[j])

        # The sum of the effects of the buttons that affect this joltage index must equal the target joltage
        # For example, if B4 and B5 both affect index 0, this states:
        # B4 + B5 == 3
        eq = sum(terms) == joltages[i]
        EQ.append(eq)

    o = z3.Optimize()
    o.minimize(sum(x))
    for eq in EQ:
        o.add(eq)  # Each counter must hit its target
    for v in x:
        o.add(v >= 0)  # Buttons can't be pressed a negative number of times
    assert o.check()

    M = o.model()
    for d in M.decls():
        p2 += M[d].as_long()

print(p2)
