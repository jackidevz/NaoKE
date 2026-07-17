.code16gcc
.text
.global _start
_start:
    cli
    xor %ax, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %ss
    mov $0x7c00, %sp
    sti

    mov %dl, boot_drive

    mov $msg_loading, %si
    call print_string

    xor %ax, %ax
    mov %ax, %es
    mov $0x8000, %bx
    mov $0x02, %ah
    mov $17, %al
    mov $0x00, %ch
    mov $0x02, %cl
    mov $0x00, %dh
    mov boot_drive, %dl
    int $0x13
    jc disk_error

    mov $msg_r1, %si
    call print_string

    mov $0xA200, %bx
    mov $0x02, %ah
    mov $18, %al
    mov $0x00, %ch
    mov $0x01, %cl
    mov $0x01, %dh
    mov boot_drive, %dl
    int $0x13
    jc disk_error

    mov $msg_r2, %si
    call print_string

    in $0x92, %al
    or $2, %al
    out %al, $0x92

    mov $msg_a20, %si
    call print_string

    cli
    lgdt gdt_descriptor

    mov $msg_pm, %si
    call print_string

    mov %cr0, %eax
    or $1, %eax
    mov %eax, %cr0

    ljmp $0x08, $pm_entry

disk_error:
    mov $msg_error, %si
    call print_string
hang16:
    hlt
    jmp hang16

print_string:
    lodsb
    or %al, %al
    jz print_done
    mov $0x0E, %ah
    mov $0x00, %bh
    int $0x10
    jmp print_string
print_done:
    ret

boot_drive: .byte 0
msg_loading: .asciz "NaoixOS: loading...\r\n"
msg_r1:      .asciz "R1 ok\r\n"
msg_r2:      .asciz "R2 ok\r\n"
msg_a20:     .asciz "A20 ok\r\n"
msg_pm:      .asciz "PM...\r\n"
msg_error:   .asciz "NaoixOS: disk error\r\n"

.align 8
gdt_start:
    .quad 0
gdt_code:
    .word 0xFFFF
    .word 0x0000
    .byte 0x00
    .byte 0x9A
    .byte 0xCF
    .byte 0x00
gdt_data:
    .word 0xFFFF
    .word 0x0000
    .byte 0x00
    .byte 0x92
    .byte 0xCF
    .byte 0x00
gdt_end:

gdt_descriptor:
    .word gdt_end - gdt_start - 1
    .long gdt_start

.code32
pm_entry:
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
    mov $0x90000, %esp

    movb $'A', 0xB8000
    movb $0x0F, 0xB8001
    movb $'B', 0xB8002
    movb $0x0F, 0xB8003

    ljmp $0x08, $0x8000
