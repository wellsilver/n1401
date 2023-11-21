card 0 ; we dont need a bootloader, so overwrite the bootloader
printer equ 299

cs  printer
lca 200+13, stringend ; move string to printer buffer
w ; print
h ; halt

db , "HELLO, WORLD!" ; size of this string is 13
stringend: ; this is at "!"