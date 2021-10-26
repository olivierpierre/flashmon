#!/usr/bin/python3

import sys
from bcc import BPF

with open("core.c") as f:
    code = f.read()

if len(sys.argv) > 1:
    if len(sys.argv) != 3:
        print("Usage: " + sys.argv[0] + " [partition start offset] [partition size]")
        sys.exit(0)
    code = code.replace("__FILTER_PART__", "1")
    code = code.replace("__MIN__", sys.argv[1])
    code = code.replace("__SZ__", sys.argv[2])

b = BPF(text=code)
b.trace_print()
