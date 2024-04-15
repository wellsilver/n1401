begin:

cs 299 ; clear printer space
cs 324 ; clear extended printer space

mcw string, 200 ; move string to printer buffer

w ; print

h begin ; branch to begin after halt

string: db "HELLO, WORLD!"< ; word mark at ! declared by '<'. "String" is the address to "H"

card 1 ; will generate an error if we go past card 1 before saying we are on card1 now.

; notes:
; d character is prefixed with d so like: ss da, where the character is da
; fx starts with % so like: (I couldnt find a instruction that used fx somehow) itufx %0

; I dont know how readable src/instructions.hpp is but its there so

; a fair warning that the preproccessor is very shitty and will fuck you up, doesnt even give right line numbers for errors