set -e

for policy in FIFO LRU
do
    echo "policy: $policy"
    for i in 2 4 8 16 32 64
    do
        echo "cache size: $i"
        python2 paging-policy.py -f ls_memaddrs.txt -p $policy -C $i -c | tail -n 2 | head -n 1
    done
done
