data  segment    
    xb db 12,13,20 
    zb db 5,6,7,8
    yw dw 5678h   
data ends      
code segment     
  main proc far  
    assume cs:code,ds:data
  start:         
    push  ds     
    sub  ax,ax   
    push ax      
    
    mov  ax,data 
    mov  ds,ax    ;不能直接将段其实地址data赋给ds

    mov  al,xb
    mov  bx,yw
    mov  ax,bx
    mov  cl,5
    mov  ch,0
    mov  cx,5
    mov  xb,0
    mov  xb,0
    mov  xb,al
    mov  yw,cx
    ;mov xb,zb ;不能同时两个操作数都是内存单元
    ;mov  5,xb ;5是立即数（常数）不能成为目的操作数  
    ret          
  main endp      
code ends        
end start        
