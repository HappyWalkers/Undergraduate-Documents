d1 segment
   sbuffera  db 16  dup('a')
   sbufferb  db 16  dup('b')
   sbufferc  db 16  dup('c')
d1 ends
d2 segment
   dbuffer  db 4  dup(16 dup(' '))
d2 ends
code segment     
  main proc far  
    assume cs:code,ds:d1,es:d2
  start:         
    push  ds     
    sub  ax,ax   
    push ax      
    
    mov  ax,d1
    mov  ds,ax
    mov  ax,d2
    mov  es,ax

    mov cx,16
    lea si,sbuffera
    lea di,dbuffer
    cld              ;设置方向，如果std会如何？
    rep movsb
     
    mov cx,8
    lea si,sbufferb
    ;lea di,dbuffer
    cld              ;设置方向，如何std会如何？
    rep movsw

    mov cx,16
    mov si,0
  lop1: 
    mov al,sbufferc[si] 
    mov dbuffer[di],al
    inc si
    inc di
    loop  lop1

    ret          
  main endp        
code ends       
end start        
