card 0 ; we dont need a bootloader, so overwrite the bootloader
printer equ 299
printer2 equ 324

cs printer  ; clear printer space
cs printer2 ; clear extended printer space

lca 200+(stringstart-stringend), stringend ; move string to printer buffer

w ; print

h ; halt

stringstart: db "HELLO, WORLD!" ; word mark is generated automatically at first byte
stringend: ; this is at "!"