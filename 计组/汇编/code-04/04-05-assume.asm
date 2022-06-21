  
d2 segment
    a dw 4
d2 ends
d1  segment    
    x dw 5,14,20 
    y dw 6
    z dw 7
    w dw ?
d1 ends      
code segment     
  main proc far  
    assume cs:code,ds:d2,es:d1
  start:         
    push  ds     
    sub  ax,ax   
    push ax      
    mov  ax,d1 
    mov  ds,ax 
    mov  ax,d2
    mov  es,ax  
    mov  ax,x    
    add  ax,y    
    add  ax,z    
    mov  w,ax    
    ret          
  main endp      
code ends        
end start        
