d1  segment    
    x db 30 dup(20 dup(' '))
    z dw 30 dup(20 dup(0abcdh))
d1 ends      
code segment     
  main proc far  
    assume cs:code,ds:d1
  start:         
    push  ds     
    sub  ax,ax   
    push ax      
    
    mov  ax,d1 
    mov  ds,ax
    
    mov  ax,0
    
    mov  bx,0
    mov  si,0
    mov  al,x[bx+si]
    add  bx,20
    mov  al,x[bx+si]
    add  si,1
    mov  al,x[bx+si]

    mov  bx,0
    mov  di,0
    mov  ax,z[bx+di]
    add  bx,40
    mov  ax,z[bx+di]
    add  di,2
    mov  ax,z[bx+di]



    

    
ret          
  main endp      
code ends        
end start        
