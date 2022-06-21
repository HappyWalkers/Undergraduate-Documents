data  segment    
    xb db 12,13,20 
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
    mov  ds,ax 
    ;mov ax,xb ;会提示类型不匹配的警告,不要使用
    mov al,xb
    mov bx,word ptr xb

    ;mov cl,yw  ;会提示类型不匹配的警告,不要使用
    mov cx,yw
    mov dl,byte ptr yw

    mov si,1
    ;mov [si],0abh;直接这样写，报错：操作数必须明确类型
    mov [si],byte ptr 0abh;
    add si,1
    mov [si],word ptr 0cdh;
    ret          
  main endp      
code ends        
end start        
