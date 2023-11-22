card 0 ; we dont need a bootloader, so overwrite the bootloader
printer equ 299
printer2 equ 324

cs printer  ; clear printer space
cs printer2 ; clear extended printer space

mcw string, 200 ; move string to printer buffer

w ; print

h ; halt

string: db "HELLO, WORLD!" . ; word mark at ! declared by .