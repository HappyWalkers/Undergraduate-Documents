code segment     
  main proc far  
    assume cs:code
  start:         
    push  ds     
    sub  ax,ax   
    push ax      
    
    mov  ax,0
    jmp  j1

  j2:
    mov  ax,0
    mov  ax,z
    jmp  j3
    mov  ax,cx

  j1:
    mov bx,ax
    jmp  j2
  j3:
    mov bx,0  
    jmp $+2
    ret          
  main endp      
code ends        
end start        
