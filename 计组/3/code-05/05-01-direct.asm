d1  segment    
    x db 12,13,20 
    y db 5,6,7,8
    z dw 5678h   
d1 ends      
d2 segment
   a  db -5,-6,-7
   b  dw -5,-6,-7
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

    mov  ax,0

    mov  al,x
    mov  ah,x+1
    mov  bx,z   
    mov  cx,ds:[7h]
    mov  dx,0aaaah
    mov  z,dx   

    mov  dl,a

    
ret          
  main endp      
code ends        
end start        
