card 0 ; we dont need a bootloader, so overwrite the bootloader

cs 299 ; clear printer space
cs 324 ; clear extended printer space

mcw string, 200 ; move string to printer buffer

w ; print

h ; halt

string: db "HELLO, WORLD!" . ; word mark at ! declared by . "string" is the address to "H"