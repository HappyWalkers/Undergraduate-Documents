extrn  decout:far
code  segment
  main proc far
    assume cs:code
  start:
    push  ds
    sub   ax,ax
    push  ax
   
    mov  ax,6      

    call factor

    mov  bx,ax

    call decout

    ret
  main endp
  factor proc
    push  ax          ;数值先入栈，后计算 
    sub   ax,1        ;逐步减1，同时判断是不是已经到了1，到1后，就可以逐步退出了
    jne   con      
    pop   ax          ;等于1，就把1 弹出来放入ax,形成部分积
    jmp   return
  con:
    call  factor     ;递归调用
    pop   cx         ;递归返回后，将堆栈中的值弹出来，放入cx中    
    mul   cl         ;将ax中的部分积（al部分）与cl相乘，结果放入ax
  return:  
    ret
  factor endp
code ends
end start