#include <uapi/linux/ptrace.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/rawnand.h>

#define FILTER_PART __FILTER_PART__
#define MIN         __MIN__
#define SZ          __SZ__

int kprobe__nand_erase(struct pt_regs *ctx, struct mtd_info *mtd,
        struct erase_info *instr) {

    unsigned int blk_size = (unsigned int)(mtd->erasesize);
    unsigned int addr = (unsigned int)(instr->addr);
    unsigned int blk_num = addr / blk_size;

#if FILTER_PART
    if(!(addr >= MIN && addr < (MIN+SZ)))
        return 0;
#endif

    bpf_trace_printk("nand_erase block %u\\n", blk_num);
    return 0;
}


int kprobe__nand_read_oob(struct pt_regs *ctx, struct mtd_info *mtd,
        loff_t from, struct mtd_oob_ops *ops) {

#if FILTER_PART
    if(!(from >= MIN && from < (MIN+SZ)))
        return 0;
#endif

    struct nand_chip *chip = mtd_to_nand(mtd);
    unsigned long long int page = (unsigned long long int)from / mtd->writesize;

    if(chip->pagecache.page == page)
        bpf_trace_printk("nand_read pagebuf hit page %u\\n", page);
    else
        bpf_trace_printk("nand_read page %u\\n", page, chip->pagecache.page);

    return 0;
}

int kprobe__nand_write_oob(struct pt_regs *ctx, struct mtd_info *mtd, loff_t to,
			  struct mtd_oob_ops *ops) {
#if FILTER_PART
    if(!(to >= MIN && to < (MIN+SZ)))
        return 0;
#endif

    unsigned long long int page = (unsigned long long int)to / mtd->writesize;
    bpf_trace_printk("nand_write page %u\\n", page);
    return 0;
}

