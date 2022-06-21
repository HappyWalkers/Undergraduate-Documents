data  segment    
    x dw 5,14,20 
    y dw 6
    z dw 7
    w dw ?
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
    mov  ax,x    
    add  ax,y    
    add  ax,z    
    mov  w,ax    
    ret          
  main endp      
code ends        
end start        
