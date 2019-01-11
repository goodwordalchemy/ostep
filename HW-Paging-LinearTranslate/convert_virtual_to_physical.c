#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *decimal_to_binary(int n, int length)
{
    int c, d, count;
    char * result;

    result = malloc(length + 1);

    count = 0;

    for (c = length-1; c >= 0; c--) {
       d = n >> c;
       if (d & 1)
           *(result+count) = '1';
       else
           *(result+count) = '0';

       count++;
    }
    *(result+count) = '\0';
    return result;
}

int binary_to_decimal(char *bin_rep, int length)
{
    int c, result;
    result = 0;
    for (c = 0; c < length; c++){
        if (bin_rep[c] == '1')
            result += (int) pow(2, (length-1)-c);
    }
    return result;

}

char *get_paging_bits(int num_paging_bits, char *bin_rep)
{
    return strndup(bin_rep, (size_t) num_paging_bits);
}

char *get_offset_bits(int num_paging_bits, char *bin_rep)
{
    return strdup(bin_rep+num_paging_bits);
}


int main(int argc, char *argv[]) {
    int virtual_address, page_size, address_size;
    int n_address_bits, n_paging_bits;

    if (argc == 4){
        virtual_address = (int) strtol(argv[1], NULL, 16);
        address_size = atoi(argv[2]);
        page_size = atoi(argv[3]);
    } 
    else if (argc == 1) {
        printf("What is the virtual address (as hex)?\n>");
        scanf("%x", &virtual_address);

        printf("How big is the address space \n>");
        scanf("%d", &address_size);

        printf("What is the page size?\n>");
        scanf("%d", &page_size);
    }
    else {
        puts("Invalid number of arguments");
        exit(1);
    }

    n_address_bits = (int) ceil(log2(address_size));

    n_paging_bits = (int) ceil(log2(address_size / page_size));

    char *bin_rep = decimal_to_binary(virtual_address, n_address_bits);

    char *paging_bits = get_paging_bits(n_paging_bits, bin_rep);

    printf("virtual address: %d\n", virtual_address);
    printf("address size: %d\n", address_size);
    printf("page size: %d\n", page_size);
    printf("n address bits: %d\n", n_address_bits);
    printf("n paging bits: %d\n", n_paging_bits);
    printf("binary representation: %s\n", bin_rep);
    printf("decimal recreation: %d\n", binary_to_decimal(bin_rep, n_address_bits));
    printf("paging bits: %s\n", paging_bits);
    printf("virtual page number: %d\n", binary_to_decimal(paging_bits, n_paging_bits));

    int physical_frame_number;
    printf("please enter appropriate physical frame number from page table (in hex)\n>");
    scanf("%x", &physical_frame_number);

    char *offset_bits = get_offset_bits(n_paging_bits, bin_rep);
    int n_shift_bits = n_address_bits - n_paging_bits;
    int offset = binary_to_decimal(offset_bits, n_shift_bits);

    int physical_address = physical_frame_number << n_shift_bits | offset;

    printf("physical_frame_number: %d\n", physical_frame_number);
    printf("offset bits: %s\n", offset_bits);
    printf("offset: %d\n", offset);
    puts("---------------------");
    printf("physical address (as int) is: %d\n", physical_address);
    printf("physical address (as hex) is: %x\n", physical_address);

    free(bin_rep);
    free(paging_bits);
    free(offset_bits);
}

