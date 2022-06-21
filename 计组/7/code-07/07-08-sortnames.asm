data segment
   namemax  db 20
   namelen  db ?
   nameinput db 20 dup(0)
   nametable db 30 dup (20 dup(' '))
   namebuffer db 20 dup(' '),0dh,0ah,'$'
   namecount  db 0
   swapped  db 0
   msgi   db 'name?','$'
   msgo   db 'Sorted name:', 0dh,0ah,'$'
   crlf   db  0dh,0ah,'$'
data ends
code  segment
  main proc far
    assume cs:code,ds:data,es:data
  start:
    push  ds
    sub   ax,ax
    push  ax 


    mov   ax,data
    mov   ds,ax
    mov   es,ax          ;为了方便执行字符串处理指令，ds,es都指向同一个段

    lea   di,nametable   ;di初始化为姓名存储区的首地址
 input:
    lea   dx,msgi
    mov   ah,9
    int   21h

    lea   dx,namemax      ;姓名输入
    mov   ah,10
    int   21h
    cmp   namelen,0       ;如果输入字符串长度为0，表示用户直接按了回车，也就是输入结束
    je    sort
    mov   cx,20
    sub   cl,namelen      ;cx为尚未输入的字符数
    mov   bx,0
    mov   bl,namelen      ;bx为已输入的字符长度
  lop1:
    mov   nameinput[bx],' ';给相应位置赋空格，这样是防止新输入的未覆盖老的。
    inc   bx               ;如这次输入‘yu’，而上一次输入'sheng',那么在输入缓冲区前五个字母会是'yueng'
    loop  lop1

    lea   si,nameinput     ;将新输入的姓名，移到姓名存储区  
    mov   cx,20
    rep   movsb            ;这里di会加20，也就指向存储区的下一个位置

    inc   namecount        ;输入姓名个数+1

    lea   dx,crlf
    mov   ah,9
    int   21h
    jmp   input
  sort:
    
    lea  si,nametable     ;每一轮比较都从姓名存储区的第一个姓名开始
    mov  ch,0            
    mov  cl,namecount
    dec  cl               ;比较的次数为姓名个数-1
    mov  swapped,0        ;清交换标志。如果一轮比较后交换标志位1，则表示已经有序了
  lops:
    push  cx              ;里面会要用到cx，所以先保存

    mov  di,si            
    add  di,20            ;di指向si指向姓名的下一个姓名
    mov  ax,si            ;si,di值先临时存到ax,bx寄存器中，后面还会要用到
    mov  bx,di
    mov  cx,20        
    repz cmpsb            ;比较两个字符串
    jbe  nextname         ;如果第一个字符串的ASCII码值比第二个小，就无需交换  

    mov  si,ax            ;si值还原，也就是指向参与比较的前面一个姓名
    lea  di,namebuffer    ;di指向缓冲区
    mov  cx,20 
    rep  movsb            ;将前面的姓名赋值到缓冲区
    mov  di,ax            ;再将原si值给di，也就是让di指向前面一个姓名
    mov  cx,20            ;此时si在上一轮+20后已经指向参与比较后面一个姓名了
    rep  movsb            ;将后一个姓名的字符串值赋给前一个姓名
    lea  si,namebuffer    ;si指向缓冲区，此时缓冲区值为参与比较的前一个姓名      
    mov  cx,20            ;此时di在上一轮+20后，已经指向参与比较的后一个姓名了
    rep  movsb            ;将缓冲区，也就是前一个姓名复制到后一个姓名的存储区  
    
    mov  swapped,1        ;设置交换标志为1，表示发生了交换，无法保证是否有序
  nextname:     
    mov  si,bx            ;将原di值给si，这样si指向下一个字符串
    pop  cx
  loop lops 
    cmp  swapped,0        ;如果在一轮比较中发生了交换，则继续开始下一轮比较
    jne  sort

    lea  dx,msgo          ;输出
    mov  ah,9
    int  21h

    mov  ch,0
    mov  cl,namecount     ;获取要输出姓名的个数
    lea  si,nametable     ;si指向姓名存储区的首地址
  lopout:
    push  cx
    lea  di,namebuffer
    mov  cx,20
    rep  movsb            ;将姓名存储区里的姓名逐一搬到姓名缓冲区
    lea  dx,namebuffer    ;姓名缓冲区后面有回车换行和'$',输出比较方便
    mov  ah,9            
    int  21h
    pop  cx
    loop  lopout 

    ret   
  main endp
code ends
end start