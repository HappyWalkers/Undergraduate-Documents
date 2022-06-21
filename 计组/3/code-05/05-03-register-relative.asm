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
    
    mov  bx,0
    mov  ah,y[bx]
    mov  bx,3
    mov  al,y[bx]

    mov  bx,0
    mov  cx,z[bx]
    add  bx,1
    mov  si,z[bx]
    add  bx,1
    mov  di,z[bx]


    

    
ret          
  main endp      
code ends        
end start        
