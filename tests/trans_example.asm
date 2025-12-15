[section code, code]

start:
  ; 
ldsp 0xFF00 ; init sp
ldbp 0xFF00 ; init bp
setio 0x0001 ; enable io
push 0x0200000000000000 ; return slot
call fn_main ; call main
drop ; drop main return
hlt
fn_ab_func:
  ; 
push 0x0200000000000000 ; local init
push 0x0200000000000000 ; local init
push 0x0200000000000000 ; local init
jmp fn_ab_func_B0_entry ; enter body
fn_ab_func_B0_entry:
  ; 
push 0x0200000000000003 ; int
stfp -8 ; store local a
push 0x0200000000000002 ; int
stfp -16 ; store local b
ldfp -8 ; load local a
ldfp -16 ; load local b
add
push 0x0200000000000030 ; '0'
add ; to ascii digit
outb ; builtin printInt(0..9)
push 0x0200000000000000 ; printInt ret
drop ; drop expr result
push 0x040000000000000A ; newline
outb ; builtin println
push 0x0200000000000000 ; println ret
drop ; drop expr result
fn_ab_func_B1_exit:
  ; 
push 0x0200000000000000 ; default return
stfp 16 ; write return slot
ret
fn_main:
  ; 
push 0x0200000000000000 ; local init
push 0x0200000000000000 ; local init
push 0x0200000000000000 ; local init
push 0x0200000000000000 ; local init
jmp fn_main_B0_entry ; enter body
fn_main_B0_entry:
  ; 
push 0x0200000000000003 ; int
stfp -24 ; store local v
push 0x0200000000000003 ; int
stfp -8 ; store local p
push 0x0200000000000000 ; return slot
call fn_ab_func ; call fn_ab_func
drop ; drop expr result
ldfp -24 ; load local v
push 0x0200000000000000 ; int
gt
jnz fn_main_B3_if_then ; if true
jmp fn_main_B4_if_else ; if false
fn_main_B4_if_else:
  ; 
push 0x0200000000000000 ; int
stfp -16 ; store local r
jmp fn_main_B2_if_join ; edge
fn_main_B3_if_then:
  ; 
ldfp -24 ; load local v
stfp -16 ; store local r
fn_main_B2_if_join:
  ; 
ldfp -16 ; load local r
push 0x0200000000000005 ; int
add
ldfp -8 ; load local p
sub
stfp -16 ; store local r
ldfp -16 ; load local r
push 0x0200000000000030 ; '0'
add ; to ascii digit
outb ; builtin printInt(0..9)
push 0x0200000000000000 ; printInt ret
drop ; drop expr result
fn_main_B1_exit:
  ; 
push 0x0200000000000000 ; default return
stfp 16 ; write return slot
ret

[section data, dataMem]


