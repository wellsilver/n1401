; no bootloader comes prepackaged
begin:

cs 299 ; clear printer space
cs 324 ; clear extended printer space

mcw string, 200 ; move string to printer buffer

w ; print

h begin ; branch to begin after halt

string: db "HELLO, WORLD!"< ; word mark at ! declared by '<'. "String" is the address to "H"

; notes:
; d character is prefixed with d so like: ss da, where the character is da
; (not done) to address a tape drive etc use U,T,F not %U,%T,%F
; (not done) n1401 will convert addressees above 999 to n1401's integer format, so typing 1000 will be converted by n1401. Prefix integers not meant to use this feature with 0b

; I dont know how readable src/instructions.hpp is but its there so

; a fair warning that the preproccessor is very shitty and will fuck you up, doesnt even give right line numbers for errors