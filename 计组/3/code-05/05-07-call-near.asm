code segment     
  main proc far  
    assume cs:code
  start:         
    push  ds     
    sub  ax,ax   
    push ax      
    
    call p1
    
    ret          
  main endp      
  p1 proc  near  
    ret
  p1 endp
code ends        
end start        
