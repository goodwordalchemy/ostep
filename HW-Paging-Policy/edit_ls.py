"""edit instructions down so it is just memory addresses"""
FILENAME = 'ls_instructions.txt'

OUT_FILENAME = 'ls_memaddrs.txt'

OFFSET_SHIFT = 12

def edit_line(line):
    raw_addr = line[3:]
    comma_idx = raw_addr.find(",")
    raw_addr = raw_addr[:comma_idx]

    addr = str(int(int(raw_addr, 16) >> OFFSET_SHIFT))

    return addr

with open(FILENAME, 'r') as handle:
    contents = handle.readlines()

new_contents = "\n".join([edit_line(l) for l in contents])

with open(OUT_FILENAME, 'w') as handle:
    handle.write(new_contents)
