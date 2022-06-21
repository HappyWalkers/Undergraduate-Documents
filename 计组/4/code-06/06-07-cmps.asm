d1 segment
   sbuffera  db 'Helle World!'
   lena=$-sbuffera
   sbufferb  db 'Hello World!'   
d1 ends
d2 segment
   dbuffer  db 'Hello World!'
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
    
    mov cx,lena
    lea si,sbuffera
    lea di,dbuffer
    cld            
    repz cmpsb
    ;1 
    mov cx,lena
    lea si,sbufferb
    lea di,dbuffer
    cld            
    repz cmpsb
    ;2
    mov cx,lena
    lea si,sbuffera
    lea di,dbuffer
  lop1: 
    mov al,sbuffera[si]
    cmp dbuffer[di],al
    jne out1
    inc si
    inc di
    loop  lop1
  out1:
    ;3
    ret          
  main endp        
code ends       
end start        
