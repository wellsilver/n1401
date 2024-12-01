; no bootloader comes prepackaged
cs 299 ; clear printer space
cs 324 ; clear extended printer space

mcw string, 200 ; move string to printer buffer

w ; print

h ; branch to begin after halt

; word mark at H, "string" points to !
dbs "HELLO, WORLD"
string: db "!"
; (db) define bytes
; db define bytes (no wordmark placed)
; dbe define bytes (with wordmark at last byte)
; dbs define bytes (with wordmark at first byte)

; notes:
; d character is prefixed with d so like: ss da, where the character is da
; (not done) to address a tape drive etc use U,T,F not %U,%T,%F
; (not done) n1401 will convert addressees above 999 to n1401's integer format, so typing 1000 will be converted by n1401. Prefix integers not meant to use this feature with 0b

; I dont know how readable src/instructions.hpp is but its there so

; a fair warning that the preproccessor is very shitty and will fuck you up, doesnt even give right line numbers for errors