import sys

def hex_from_bin(bin_str):
    return hex(int(bin_str, 2))

def print_bin(name, bin_str):
    print(f'name: {name}\n\tbin: {bin_str}\n\tdec: {int(bin_str, 2)}\n\thex: {hex_from_bin(bin_str)}')

virtual_address = '0x' + input("what is the virtual address (hex)?\n>")
virtual_address = int(virtual_address, 16)

va_binary = bin(virtual_address)[2:]
pd_index = va_binary[:5]
pt_index = va_binary[5:10]
offset = va_binary[10:]

print_bin("va_binary", va_binary)
print_bin("pd_index", pd_index)
print_bin("pt_index", pt_index)
print_bin("offset", offset)

page_directory = input("Paste the page at the memory(pdbr) here:\n>")
pde_address = page_directory.split()[int(pd_index, 2)]
print(f"DEBUG: pde_address: {pde_address}")
print(f"DEBUG: {int('0x' + pde_address, 16)}")
print(f"DEBUG: {bin(int('0x' + pde_address, 16))}")
pde_address = bin(int('0x' + pde_address, 16))[2:]
print("pde_address = pdbr + pd_index * x")

valid = pde_address[0]
pde_address = pde_address[1:]
print_bin("pde_address", pde_address)
if valid != '1':
    print("segfault")
    sys.exit(0)

pde = input("Paste the page at memory(pde_address) here:\n>")
pte_address = pde.split()[int(pt_index, 2)]
pte_address = bin(int('0x' + pte_address, 16))[2:]
print("pte_address = pde + pt_index * x")

valid = pte_address[0]
pte_address = pte_address[1:]
print_bin("pte_address", pte_address)
if valid != '1':
    print("segfault")
    sys.exit(0)

pte = input("Paste the page at memory(pte_address) here:\n>")
mem = pte.split()[int(offset, 2)]
mem = bin(int('0x' + mem, 16))
print("value in memory at physical address = pte + offset * x")
print_bin("value", mem)
