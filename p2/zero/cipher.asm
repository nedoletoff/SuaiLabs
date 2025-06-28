format ELF64
public _start

include "str.inc"
include "fmt.inc"

section '.data' writeable
    enter_usual_str db "Enter string to cipher: ", 0
    len_eus = $-enter_usual_str
    enter_key_str db "Enter key: ", 0
    enter_cipher_str db "Enter string to decipher: ", 0
    print_cipher_str db "Cipher: ", 0
    print_usual_str db "Text: ", 0
    print_start_processing db "Processing...", 0

section '.var' writeable
    key rb 1
    str_size equ 256
    input_str rb str_size
    output_str rb str_size


section '.next_key' executable
; | input
;rdx = key
; | output
;rdx = key
next_key:
    rol dl, 1
    ret

section '.cipher' executable
; | input
;rdx = key
; | output
; rax = cipher string
cipher:
    push rbx
    push rdx
    push rcx
    push r8

    mov rax, input_str
    mov rcx, output_str
    xor rbx, rbx

    push rax
    call clear_output
    mov rax, print_start_processing
    call print_string
    call print_line
    pop rax

    .next_iter:
        cmp [rax+rbx], byte 0
        je .close
        cmp rbx, str_size
        je .close_limit
        call next_key
        mov r8, rdx

        push rax
        mov rax, rdx
        call print_hex
        mov rax, '^'
        call print_char
        pop rax

        push rax
        mov rax, [rax+rbx]
        call print_hex
        mov rax, '='
        call print_char
        pop rax

        xor dl, [rax+rbx]

        push rax
        mov rax, rdx
        call print_hex
        mov rax, '-'
        call print_char
        mov rax, rdx
        call print_char
        call print_line
        pop rax

        mov [rcx+rbx], dl
        mov rdx, r8

        inc rbx
        jmp .next_iter
    .close_limit:
        dec rbx
        mov [rcx+rbx], byte 0
        jmp .close
    .close:
        mov rax, rcx
        pop r8
        pop rcx
        pop rdx
        pop rbx
        ret

section '.clear' executable
clear_output:
    push rax
    push rbx
    mov rax, output_str
    xor rbx, rbx
    .next_iter:
        cmp rbx, str_size
        je .close
        mov [rax+rbx], byte 0
        inc rbx
        jmp .next_iter
    .close:
        pop rbx
        pop rax
        ret


section '.inputs' executable
input_string_base:
    push rax
    push rbx
    mov rax, input_str
    mov rbx, str_size
    call input_string
    jmp .close
    .close:
        pop rbx
        pop rax
        ret


input_string_usual:
    push rax
    mov rax, enter_usual_str
    call print_string
    call input_string_base
    pop rax
    ret

input_string_cipher:
    push rax
    mov rax, enter_cipher_str
    call print_string
    call input_string_base
    pop rax
    ret
; | output
; rdx - key
input_key:
    push rax
    push rbx
    mov rax, enter_key_str
    call print_string
    xor rax, rax
    call input_char
    mov rdx, rax
    jmp .close
    .close:
        pop rbx
        pop rax
        ret


section '.text' executable
_start:
    call input_string_usual
    call input_key

    call cipher
    mov rax, print_cipher_str
    call print_string
    mov rax, output_str
    call print_string
    call print_line

    call input_string_cipher
    call input_key

    call cipher
    mov rax, print_usual_str
    call print_string
    mov rax, output_str
    call print_string
    call print_line

    mov rax, 1
    mov rbx, 0
    int 0x80
