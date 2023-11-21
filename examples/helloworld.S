card 0 ; we dont need a bootloader, so overwrite the bootloader
printer equ 299

cs  printer
lca 200+(stringstart-stringend), stringend ; move string to printer buffer
w ; print
h ; halt

stringstart: db , "HELLO, WORLD!" ; It will generate a warning if there is no bcd code equivelant
stringend: ; this is at "!"