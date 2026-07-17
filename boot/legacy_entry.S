.section .bss
.align 16
legacy_stack_bottom:
    .skip 16384
legacy_stack_top:

.section .entry, "ax"
.global _start
.type _start, @function
_start:
    mov $0x3F9, %dx
    mov $0x00, %al
    out %al, %dx
    mov $0x3FB, %dx
    mov $0x80, %al
    out %al, %dx
    mov $0x3F8, %dx
    mov $0x03, %al
    out %al, %dx
    mov $0x3F9, %dx
    mov $0x00, %al
    out %al, %dx
    mov $0x3FB, %dx
    mov $0x03, %al
    out %al, %dx

    mov $0x3F8, %dx
    mov $'1', %al
    out %al, %dx

    mov $__bss_start, %edi
    mov $__bss_end, %ecx
    sub %edi, %ecx
    xor %eax, %eax
    cld
    rep stosb

    mov $0x3F8, %dx
    mov $'2', %al
    out %al, %dx

    mov $legacy_stack_top, %esp
    xor %ebp, %ebp

    mov $0x3F8, %dx
    mov $'3', %al
    out %al, %dx

    push $0
    push $0xB105F00D

    mov $0x3F8, %dx
    mov $'4', %al
    out %al, %dx

    call kmain

hang:
    cli
    hlt
    jmp hang
.size _start, . - _start
