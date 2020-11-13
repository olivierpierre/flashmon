# FLASHMON flash memory monitoring tool (Version 2.1)

2020/11/13 <pierre.olivier@manchester.ac.uk>
2013/05/23 <pierre.olivier@univ-brest.fr>

**Note**: Flashmon relies on jprobes that have been dropped from the Linux
kernel starting v4.19. Look in the `Flashmon-eBPF` folder for a basic tool
providing similar functionalities on recent kernels.

## DESCRIPTION

Flashmon is a Linux kernel module that monitors NAND flash memory access events
using Kprobes and Jprobes. Flashmon monitors accesses for _bare flash chips_
soldered on embedded boards, managed by the Linux Memory Technology Device
(MTD) subsystem. Please note that Flashmon will not work for devices that are
not managed by MTD: SD/MMC cards, USB pen drives, SSD drives, etc.

The monitored events are: flash pages read / write requests, and flash block
erase operations. Those operations are traced at the MTD subsystem level to
stay independent from the file system and the device driver.

For more information about Flashmon please see the "FlashmonUserGuide.pdf" file
in the archive.

### REQUIREMENTS

This module must be loaded on a kernel with KPROBES and KALLSYMS activated. It
should be fine if a command like 'cat /proc/kallsyms | grep "jprobe"' returns
something on your system.

### Compiling & installing flashmon

If you are compiling flashmon on the same computer (x86 / amd64) on which you
are planning to use it, a simple "make -f Makefile.x86" in the flashmon folder
should do the job.

For cross compiling the module for another architecture, you will have
to edit the Makefile.

To run flashmon, insert the module "flashmon.ko", following the instructions in
the FlashMonUserGuide.pdf document.

### Using Flashmon as a built-in function in the kernel

When Flashmon is used as a built-in function in the kernel (as opposed to a
module), one interesting feature is the fact that Flashmon is loaded before the
file system driver. It then allows to trace flash access at boot time.

Flashmon uses the 'getnstimeofday' function to compute time measurements for
the log of flash accesses. The problem is that sometimes the system time is not
setup very well setup early in the boot process. So there may be is an
important offset in the time measurements. As that offset is the same for each
entry of the log, one can cope with this problem by subtracting this offset
from each measurement (a tool for doing so is available in trunk/Tests/
flashmon_startzero on the flashmon svn repository on sourceforge).

Another problem is the fact that the system time may be setup during the boot
process (i.e. during flashmon tracing process), leading to inconsistencies in
flashmon time measurements. For now a solution is to disable the system time
setup at boot time. In the kernel menuconfig go to Device Drivers -> Real Time
Clock -> Set system time from rtc at startup and resume. Another solution would
be for flashmon to have its own timer.

