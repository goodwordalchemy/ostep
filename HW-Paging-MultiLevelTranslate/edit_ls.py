"""edit instructions down so it is just memory addresses"""
import sys

FILENAME = 'ls_instructions.txt'

OUT_FILENAME = 'ls_memaddrs.txt'

def edit_line(line):
    line = line[3:]
    comma_idx = line.find(",")
    if comma_idx == -1:
        print(line)
        sys.exit()
    print(line)
    line = line[:comma_idx]

    return line

with open(FILENAME, 'r') as handle:
    contents = handle.readlines()

new_contents = ",".join([edit_line(l) for l in contents])

with open(OUT_FILENAME, 'w') as handle:
    handle.write(new_contents)
