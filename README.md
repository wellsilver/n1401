# n1401
Trying to write a modern assembler for the 1401

# syntax

## db
### define bytes
this will define some data
```x86asm
db 540.
db "Hello World".
```
puts the number 540 and the string Hello World in the file

## ;  
### note
anything after this until newline is ignored

```x86asm
text:
  mwe ; this isnt valid
```

## .  
### word mark 
dont try addresses like ``.text:`` the ``.`` will make a wordmark.

this will place a wordmark on the nearest byte before it

can be used with db like this:
```x86asm
db "Hello World".
```
places a wordmark on the letter "d"

## :  
### address with name

dont try addresses like ``.text:`` the ``.`` will make a wordmark.

```x86asm
string:
  db "Hello world".
```
will point to "H" in the string

## addressing
