# Flashmon eBPF

This is a simple implementation of the core functionality of Flashmon using
eBPF, suitable for kernels versions > 4.18.

## Requirements
```
sudo apt install bpfcc-tools python3-bpfcc libbpfcc libbpfcc-dev
```

## Usage

To trace the entire chip:
```
sudo ./flashmon.py
```

Tracing a particular partition, you first need to compute the start offset
and the size of the partition in question, in bytes. To do so, use
the `mtdinfo` command to compute the size and position of all partitions
preceding the one you want to trace, for example if we want to trace /dev/mtd2:

```
sudo mtdinfo /dev/mtd0
Amount of eraseblocks:          4096 (536870912 bytes, 512.0 MiB)

sudo mtdinfo /dev/mtd1
Amount of eraseblocks:          2048 (268435456 bytes, 256.0 MiB)

sudo mtdinfo /dev/mtd2
Amount of eraseblocks:          2048 (268435456 bytes, 256.0 MiB)
```

So we know that `mtd2` starts at `536870912 + 268435456 = 805306368` bytes and
that its size is 268435456 bytes. So we can trace like that:

```
sudo ./flashmon.py 805306368 268435456
```
