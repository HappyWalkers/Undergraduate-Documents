code segment     
  main proc far  
    assume cs:code
  start:         
    push  ds     
    sub  ax,ax   
    push ax      
    
    ;无符号数溢出
    mov  ax,5
    mov  bx,10
    sub  ax,bx
   
    ;有符号数溢出
    mov  ax,-20000
    mov  bx,20000
    sub  ax,bx

    cmp  ax,bx

    dec  ax

    mov  ax,5
    neg  ax
    neg  ax
    ret          
  main endp        
code ends       
end start        
