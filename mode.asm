[BITS 32]
global bokj_jump_to_app

; [esp + 4] = адрес точки входа приложения
bokj_jump_to_app:
    mov eax, [esp + 4]
    
    ; Сброс сегментных регистров для изоляции приложения
    mov bx, 0x23 ; Селектор данных пользователя
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    push 0x23     ; SS
    push 0xBFFFFF ; ESP (верхушка стека приложения)
    push 0x1B     ; CS
    push eax      ; EIP (точка входа)
    
    iretd         ; Прыжок в пространство приложения
