d2 segment
   dbuffer  db 'Hello World!'
   lend=$-dbuffer
d2 ends
code segment     
  main proc far  
    assume cs:code,es:d2
  start:         
    push  ds     
    sub  ax,ax   
    push ax      
    
    mov  ax,d2
    mov  es,ax
    

    mov cx,lend
    mov al,'o'
    lea di,dbuffer
    cld            
    repnz scasb
    ;1 
    mov cx,lend
    mov ax,'lo'
    lea di,dbuffer
    cld            
    repnz scasw
    ;2
    mov cx,lend
    mov ax,'Wo'
    lea di,dbuffer
    cld            
    repnz scasw
    ;3
    mov cx,lend
    mov ax,'oW'
    lea di,dbuffer
    cld            
    repnz scasw
    ;4
    mov cx,lend
    mov al,'o'
    lea di,dbuffer
  lop1: 
    cmp dbuffer[di],al
    je out1
    inc di
    loop  lop1
  out1:

    ret          
  main endp        
code ends       
end start        
