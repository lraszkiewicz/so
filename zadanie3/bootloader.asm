ORG 0x0600

; relocate MBR from 0x7c00 to 0x0600
relocate:
    xor ax, ax
    mov es, ax
    mov ds, ax
    mov si, 0x7c00
    mov di, 0x0600
    mov cx, 0x0100
    repnz movsw     ; move from ds:si to es:di while not zero
    jmp 0x0:start

; char argument expected in register al
printChar:
    mov ah, 0x0e    ; function code - print character
    int 0x10
    ret

; address to buffer expected in register ax
print:
    mov bx, ax
    mov al, [bx]
    cmp al, 0x0
    je returnPrint
    call printChar
    inc bx
    mov ax, bx
    jmp print
returnPrint:
    ret

start:
    mov ax, cs
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x8000

    ; start reading name
    mov ax, ENTER_YOUR_NAME_STRING
    call print
    mov bp, 0       ; current name length
readInput:
    mov ah, 0x00    ; function code - read key press
    int 0x16        ; reads character, returns it in register al
    cmp al, 0x0d
    je pressedEnter
    cmp al, 0x08
    je pressedBackspace
    jmp pressedChar
pressedEnter:
    cmp bp, 3       ; check if not shorter than 3 characters
    jl readInput    ; if too short, don't do anything
    ; if not too short, finish reading it
    mov ax, HELLO_STRING
    call print
    mov ax, NAME_BUFFER
    call print
    mov ax, NEWLINE_STRING
    call print
    jmp hello
pressedBackspace:
    cmp bp, 0       ; check if name was empty
    je readInput    ; if empty, don't do anything
    ; if not empty, delete the last character from memory and from screen
    mov al, 0x08
    call printChar  ; move cursor back
    mov al, ' '
    call printChar  ; erase the earlier entered character
    mov al, 0x08
    call printChar  ; move cursor back again
    mov [NAME_BUFFER+bp], byte 0x0
    dec bp
    jmp readInput
pressedChar:
    cmp bp, 12      ; check if name has 12 characters
    je readInput    ; it name has 12 characters, don't save the next character
    ; if name is shorter than 12 characters, print the character and save it
    call printChar
    inc bp
    mov [NAME_BUFFER+bp-1], al
    jmp readInput

hello:
    mov ah, 0x86
    mov cx, 0x1e
    mov dx, 0x8480
    int 0x15
    jmp copyOldBL

; copy minix's bootloader from second disk sector to 0x7c00 in memory
copyOldBL:
    xor ax, ax
    mov es, ax      ; buffer address segment
    mov bx, 0x7c00  ; buffer address offset
    mov ah, 0x02    ; function code - read sectors from drive
    mov al, 0x01    ; sectors to read count
    mov ch, 0x00    ; cylinder
    mov cl, 0x02    ; sector
    mov dh, 0x00    ; head
    mov dl, 0x80    ; drive
    int 0x13
    jmp 0x0:0x7c00  ; run the old bootloader


ENTER_YOUR_NAME_STRING: db 'Enter your name', 0xd, 0xa, 0x0
HELLO_STRING: db 0xd, 0xa, 'Hello ', 0x0
NEWLINE_STRING: db 0xd, 0xa, 0x0

NAME_BUFFER: times 13 db 0x0
