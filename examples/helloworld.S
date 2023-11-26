card 0 ; we dont need a bootloader, so overwrite the bootloader

begin:

cs 299 ; clear printer space
cs 324 ; clear extended printer space

mcw String, 200 ; move string to printer buffer

w ; print

h begin ; branch to begin

string: db "HELLO, WORLD!"< ; word mark at ! declared by < "String" is the address to "H"