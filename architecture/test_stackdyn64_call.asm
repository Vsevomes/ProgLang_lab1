[section code, code]
start:
    ldsp 0xFFF0
    ldbp 0xFFF0
    setio 1

    ; args: push 'H', then push 'I'
    push 0x0400000000000048    ; 'H'
    push 0x0400000000000049    ; 'I'
    call emit2

    ; caller-cleans (optional but good practice):
    drop
    drop

    push 0x040000000000000A
    outb
    hlt

; emit2(a,b): prints a then b
; layout:
; [bp+0]  old_bp
; [bp+8]  return_ip
; [bp+16] b ('I')  (last pushed)
; [bp+24] a ('H')  (previous)
emit2:
    ldfp 24
    outb
    ldfp 16
    outb
    ret

[section data, dataMem]
