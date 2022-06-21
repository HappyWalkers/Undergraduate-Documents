d1  segment    
    x db 12,13,20 
    y db 1,2,3,4,5
    z dw 1234h,4567h,89abh,0cdefh
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
    
    mov  bx,offset x
    mov  si,0
    mov  al,[bx+si]
    add  si,1
    mov  ah,[bx+si]

    mov  bx,offset z
    mov  di,0
    mov  cx,[bx+di]
    add  di,1
    mov  dx,[bx+di]
    add  di,1
    mov  bp,[bx+di]



    

    
ret          
  main endp      
code ends        
end start        
