; ============================================================
; Full test for stackdyn64 WITHOUT subroutines
; Output is ASCII via outb (port = 1)
; ============================================================

[section code, code]
start:
    ldsp 0xFFF0
    ldbp 0xFFF0
    setio 1

    ; --- print "START\n"
    push 0x0400000000000053  ; S
    outb
    push 0x0400000000000054  ; T
    outb
    push 0x0400000000000041  ; A
    outb
    push 0x0400000000000052  ; R
    outb
    push 0x0400000000000054  ; T
    outb
    push 0x040000000000000A  ; \n
    outb

    ; ------------------------------------------------------------
    ; DATA[0x20] = 'A', print "CHAR=A\n"
    ; store expects: addr value
    ; ------------------------------------------------------------
    push 0x0200000000000020
    push 0x0400000000000041
    store

    push 0x0400000000000043  ; C
    outb
    push 0x0400000000000048  ; H
    outb
    push 0x0400000000000041  ; A
    outb
    push 0x0400000000000052  ; R
    outb
    push 0x040000000000003D  ; =
    outb

    push 0x0200000000000020
    load
    outb
    push 0x040000000000000A
    outb

    ; ------------------------------------------------------------
    ; overwrite same cell with INT=7, print "INT=7\n"
    ; ------------------------------------------------------------
    push 0x0200000000000020
    push 0x0200000000000007
    store

    push 0x0400000000000049  ; I
    outb
    push 0x040000000000004E  ; N
    outb
    push 0x0400000000000054  ; T
    outb
    push 0x040000000000003D  ; =
    outb

    ; print digit (7 + '0')
    push 0x0200000000000020
    load
    push 0x0200000000000030
    add
    outb
    push 0x040000000000000A
    outb

    ; ------------------------------------------------------------
    ; Loop: print "LOOP:321\n"
    ; counter at DATA[0x30] (int)
    ; ------------------------------------------------------------
    push 0x040000000000004C  ; L
    outb
    push 0x040000000000004F  ; O
    outb
    push 0x040000000000004F  ; O
    outb
    push 0x0400000000000050  ; P
    outb
    push 0x040000000000003A  ; :
    outb

    ; counter = 3 in dataMem[0x30]
    push 0x0200000000000030
    push 0x0200000000000003
    store

loop_begin:
    ; print counter digit
    push 0x0200000000000030
    load
    push 0x0200000000000030
    add
    outb

    ; counter = counter - 1  (fixed)
    push 0x0200000000000030
    dup
    load
    push 0x0200000000000001
    sub
    store

    ; if counter == 0 => done
    push 0x0200000000000030
    load
    jz loop_done

    jmp loop_begin

loop_done:
    push 0x040000000000000A
    outb


    ; ------------------------------------------------------------
    ; MUL: 8*7 = 56, print "MUL=56\n"
    ; 56 печатаем как две цифры через /10 и %10
    ; ------------------------------------------------------------
    push 0x040000000000004D  ; M
    outb
    push 0x0400000000000055  ; U
    outb
    push 0x040000000000004C  ; L
    outb
    push 0x040000000000003D  ; =
    outb

    push 0x0200000000000008
    push 0x0200000000000007
    mul                       ; -> 56

    ; tens = 56 / 10
    dup
    push 0x020000000000000A
    div
    push 0x0200000000000030
    add
    outb

    ; ones = 56 % 10
    push 0x020000000000000A
    mod
    push 0x0200000000000030
    add
    outb

    push 0x040000000000000A
    outb

    ; ------------------------------------------------------------
    ; Div/Mod test: 57 / 10 => q=5, r=7
    ; print "DIV=5 MOD=7\n"
    ; ------------------------------------------------------------
    push 0x0400000000000044  ; D
    outb
    push 0x0400000000000049  ; I
    outb
    push 0x0400000000000056  ; V
    outb
    push 0x040000000000003D  ; =
    outb

    push 0x0200000000000039  ; 57
    push 0x020000000000000A  ; 10
    div                       ; -> 5
    push 0x0200000000000030
    add
    outb

    push 0x0400000000000020  ; space
    outb

    push 0x040000000000004D  ; M
    outb
    push 0x040000000000004F  ; O
    outb
    push 0x0400000000000044  ; D
    outb
    push 0x040000000000003D  ; =
    outb

    push 0x0200000000000039  ; 57
    push 0x020000000000000A  ; 10
    mod                       ; -> 7
    push 0x0200000000000030
    add
    outb

    push 0x040000000000000A
    outb

    ; --- print "END\n"
    push 0x0400000000000045  ; E
    outb
    push 0x040000000000004E  ; N
    outb
    push 0x0400000000000044  ; D
    outb
    push 0x040000000000000A
    outb

    hlt


[section data, dataMem]
; пусто
