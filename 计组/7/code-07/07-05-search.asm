d1  segment
  a   dw 11,22,33,44,55,66,77,88,99,111,222,333
  lena=$-a
  number dw 56
  low_idx dw ?
  high_idx dw ?
  msg1 db 'found$'
  msg2 db 'not found$'
d1  ends
code segment     
  main proc far  
    assume cs:code,ds:d1
  start:         
    push  ds     
    sub  ax,ax   
    push ax          
    mov  ax,d1 
    mov  ds,ax
    
    mov  ax,number

    mov  low_idx,1
    mov  high_idx,number-a
    shr  high_idx,1
 again:
    mov  si,low_idx
    mov  di,high_idx
    cmp  si,di
    ja   notfound

    add  si,di
    shr  si,1
    shl  si,1
    cmp  ax,a[si]
    je   find
    jb   lower
    shr  si,1
    inc  si
    mov  low_idx,si
    jmp  again
  lower:
    shr si,1
    dec si
    mov high_idx,si
    jmp  again


  find:
    clc  
    lea dx,msg1
    mov ah,9
    int 21h
    jmp done 

  notfound:
    stc
    lea dx,msg2
    mov ah,9
    int 21h
    
  done:

    ret          
  main endp  
code ends        
end start        
