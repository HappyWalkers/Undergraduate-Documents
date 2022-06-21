d1  segment    
    x db 30 dup (20 dup(' ')) 
    z dw 30 dup (20 dup(0abh))
d1 ends      
code segment     
  main proc far  
    assume cs:code,ds:d1
  start:         
    push  ds     
    sub  ax,ax   
    push ax      
    
    mov  al,150
    mov  bl,160
    add  al,bl
    mov  ah,100
    mov  bh,100
    adc  ah,bh
    ;1
    mov  ax,150
    mov  bx,160
    add  ax,bx
    mov  dx,100
    mov  cx,100
    adc  dx,cx
    ;2

    

    
ret          
  main endp      
code ends        
end start        
