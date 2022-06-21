d1  segment    
    x dw 5 
    y dw 6
    z dw 7
    q db 8
    w dw ?
    p dw 9,9
d1 ends      
d2 segment
   a  dw 8 dup (0abcdh)
   b  db 3,3 dup(5 dup(15))
   c1 db 'abcd'
   c2 db 'a','b'
   c3 dw 'ab'
   c4 dd 12345678h
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
    mov  ax,x
    mov  bx,x+1      ;加了一个内存单元（1*dw=2字节)，还是1个字节？
    mov  cx,x+2      ;加了两个内存单元（2*dw=4字节)，还是2个字节？
    mov  dx,y        ;跟上一条一样？
    mov  si,x+16     ;跨到d2段了？
    mov  di,x+64     ;代码段？

    mov  x,0101h   
    mov  q,33h       ;可以为3333h吗？（2字节或者更多）
    mov  a+4,1234h   ;用的是哪个段寄存器？ 
  
    ret          
  main endp      
code ends        
end start        
