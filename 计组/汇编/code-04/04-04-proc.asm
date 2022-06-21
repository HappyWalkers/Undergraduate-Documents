code segment     
  main proc far  
    assume cs:code
  start:         
    push  ds     
    sub  ax,ax   
    push ax      
     
    mov  ax,-5
    call tmp
    mov bx,ax
    ret          
  main endp      
  tmp proc
     neg ax
     ret
  tmp endp
code ends        
end start        
