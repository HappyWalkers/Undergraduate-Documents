extrn  decout:far        ;申明decout函数来自于其他obj文件
d1  segment
    a  dw  32,85,16,15,8
    crlf db 0dh,0ah,'$'
d1  ends      
code segment     
  main proc far  
    assume cs:code,ds:d1
  start:         
    push  ds     
    sub  ax,ax   
    push ax          
    mov  ax,d1 
    mov  ds,ax
    
    mov cx,5
    mov  si,0
lop0:
    push  cx
    mov  bx,a[si]
    call decout       ;输出一个数值
    mov  dl,' '
    mov  ah,2
    int  21h          ;输出一个空格
    add  si,2
    pop  cx
    loop  lop0
    lea dx,crlf
    mov ah,9
    int 21h
    
    mov  cx,4
 lop1:
    push cx
    mov  bx,0
 lop2:
    mov  ax,a[bx]
    cmp  ax,a[bx+2]
    jbe  con
    xchg ax,a[bx+2]
    mov  a[bx],ax
con:
    add  bx,2
    loop lop2

    pop  cx
    loop lop1   


   mov cx,5
    mov  si,0
lop4:
    push  cx
    mov  bx,a[si]
    call decout
    mov  dl,' '
    mov  ah,2
    int  21h
    add  si,2
    pop  cx
    loop  lop4

    ret          
  main endp  
code ends        
end start        
