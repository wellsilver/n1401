boot none ; program doesnt need to have a bootloader
printer equ 299
va: "f"

cs  printer
lca 200+13, string+13 ; move string to printer buffer
w ; print
h ; halt

string: db , "HELLO, WORLD!" ; size of this string is 13