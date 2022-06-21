d1  segment
   array  db  3,5,15,23,37,49,52,65,78,99,105  ;如果为dw类型呢？
   n   db    200         
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

    mov  al,n           ; 待插入数值先放入al寄存器中
    mov  cx,n-array     ; 数组元素个数
    mov  bx,cx          ; bx作为访问数组元素的指针

  lop1:
    dec  bx             ;每次减1，实现对数组元素的便利
                        ;放在第一行是因为数组访问最后一个元素的偏移量为数组元素个数减1
                        ;因为第一个元素偏移量为0
                        ;如果是dw类型的数据呢？
    cmp  array[bx],al   ;将待插入元素与数组中元素进行比较
    jbe  rtn            ;如果待插入元素大于数组元素，即可插入到数组中
    mov  dl,array[bx]   ;否则，将数组元素复制一份到其下一个位置
    mov  array[bx+1],dl      
    loop  lop1 
    dec  bx             ;能执行这条指令，说明比第一个元素都小
                        ;如果是比第一个元素小，需要将bx减1，为下面的插入做准备 
   rtn: 
    mov  array[bx+1],al ;插入到bx+1的位置。该位置为前一次比较且已完成复制数据

ret          
  main endp      
code ends        
end start        
