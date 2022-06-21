d1 segment
   dbuffer  db 3  dup(16 dup(' '))
d1 ends
code segment     
  main proc far  
    assume cs:code,es:d1
  start:         
    push  ds     
    sub  ax,ax   
    push ax      
    
    mov  ax,d1
    mov  es,ax
    
    mov cx,16
    lea di,dbuffer
    mov al,'a'
    cld              
    rep stosb
     
    mov cx,8
    mov ax,'ab'
    ;lea di,dbuffer  
    cld              
    rep stosw

    mov cx,16
    mov al,'a'
  lop1: 
    mov dbuffer[di],al
    inc di
    loop  lop1


    ret          
  main endp        
code ends       
end start        
