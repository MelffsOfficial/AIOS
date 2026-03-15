[BITS 32]
global bokj_context_switch

bokj_context_switch:
    mov eax, [esp + 4]   ; Параметр: адрес точки входа
    
    mov bx, 0x23         ; Пользовательский сегмент данных
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    push 0x23            ; Stack Segment
    push 0x1FFFFF        ; User Stack Pointer
    push 0x1B            ; Code Segment
    push eax             ; Entry Point (EIP)
    
    iretd                ; Выход в User Mode
