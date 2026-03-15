[BITS 32]

global bokj_syscall_gate
global get_cpu_ticks
global bokj_io_outb
global bokj_io_inb

bokj_io_outb:
    mov edx, [esp + 4]
    mov al, [esp + 8]
    out dx, al
    ret

bokj_io_inb:
    mov edx, [esp + 4]
    in al, dx
    ret

get_cpu_ticks:
    rdtsc
    ret

bokj_syscall_gate:
    pusha
    push ds
    push es
    
    ; System Call Logic
    ; EAX = Function ID
    ; EBX = Param 1
    ; ECX = Param 2
    
    pop es
    pop ds
    popa
    iret
