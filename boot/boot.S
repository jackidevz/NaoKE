.set MB1_MAGIC,    0x1BADB002
.set MB1_FLAGS,    0x00000003
.set MB1_CHECKSUM, -(MB1_MAGIC + MB1_FLAGS)

.section .multiboot1, "a"
.align 4
    .long MB1_MAGIC
    .long MB1_FLAGS
    .long MB1_CHECKSUM

.set MB2_MAGIC,        0xE85250D6
.set MB2_ARCH,         0
.set MB2_HEADER_LEN,   (header_end - header_start)
.set MB2_CHECKSUM,     -(MB2_MAGIC + MB2_ARCH + MB2_HEADER_LEN)

.section .multiboot2, "a"
.align 8
header_start:
    .long MB2_MAGIC
    .long MB2_ARCH
    .long MB2_HEADER_LEN
    .long MB2_CHECKSUM

    .align 8
    .word 0
    .word 0
    .long 8
header_end:

.section .bss
.align 16
stack_bottom:
    .skip 16384
stack_top:

.section .text
.global _start
.type _start, @function
_start:
    mov $stack_top, %esp
    xor %ebp, %ebp

    push %ebx
    push %eax

    call kmain

hang:
    cli
    hlt
    jmp hang
.size _start, . - _start
