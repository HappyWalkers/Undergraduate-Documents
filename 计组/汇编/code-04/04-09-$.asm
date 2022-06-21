d1  segment
   list db 10,20,30,40
   listSize=$-list
   array dw 10,20,30,$,$+2,60
   arraySize=$-array   
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

    mov cx,listSize
    arraySize=arraySize/2
    mov cx,arraySize
    
    ret          
  main endp      
code ends        
end start        
