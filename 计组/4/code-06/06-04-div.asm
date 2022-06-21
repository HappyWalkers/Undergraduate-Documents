data segment
   tb  db 10
   tw  dw 10
data ends
code segment     
  main proc far  
    assume cs:code,ds:data
  start:         
    push  ds     
    sub  ax,ax   
    push ax      
    
    mov  ax,data
    mov  ds,ax

    mov  ax,10005
    mov  bl,100
    div  bl

    mov  ax,10000
    mov  bl,10
    ;div  bl


    mov  dx,1
    mov  ax,2
    mov  bx,60000
    div  bx
    
    


    mov ax,100
    div tb
    
    mov  dx,1
    mov  ax,2
    div  tw

    

    ret          
  main endp        
code ends       
end start        
