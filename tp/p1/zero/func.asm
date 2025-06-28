format ELF64

section '.next_key' executable
; | input ax - this key
; | output ax - new key

next_key:
    rcr al, 1
    jmp close
    .close:
        ret

section '.cipher' executable
; |input
;ax - char
;bx - key
; | output
; ax - char xor key
cipher:
    xor rax, rbx
    jmp close
    .close:
        ret


