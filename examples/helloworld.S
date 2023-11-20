boot none ; program doesnt need to have a bootloader (its smaller than a card)
printer equ 299
va: "f"

cs  printer
lca 200+13, stringend ; move string to printer buffer
w ; print
h ; halt

db , "HELLO, WORLD!" ; size of this string is 13
stringend: ; this is at "!"