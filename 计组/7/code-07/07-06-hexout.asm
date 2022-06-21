Data   segment
	Num	dw   25afh
	String	db   4 dup(?), '$', 0dh, 0ah
Data    ends
Code   segment
	assume  cs:code, ds:data
Main   proc     far
  Begin: 
    push    ds
	xor		ax, ax
	push	ax 
	mov		ax,data
	mov		ds, ax

	lea		bx, string 
	push	bx				;将字符串的首地址放到BX中进行压栈
	push	num				;将要转换的数压栈
	call	binhex
	lea		dx, string 
	mov		ah, 9
	int		21h
	ret
Main    endp
Binhex   proc  near
	  ;此时堆栈状态见图
	  push  bp
	  mov  bp,sp
	  push  ax
	  push  di
	  push  bx
	  push  cx
	  pushf
	  ;此时堆栈状态见图	
	  mov	ax, [bp+4]     ; ax=25afh
	  mov	di, [bp+6]     ;  di=0002(string的偏移地址)
	  mov	ch, 4           
	  mov	cl, 4
   rota:
      rol	ax ,cl
	  mov	bl, al
	  and	bl, 0fh
	  add	bl, 30h 
	  cmp	bl, 39h
	  jle	next
	  add	bl, 7h   
   Next:
      mov	[di], bl
	  inc	di
	  dec	ch
	  jnz	rota 
	  popf
	  pop	cx
	  pop	bx
	  pop	di
	  pop	ax
	  pop	bp
	  ret	4
Binhex   endp
Code      ends
	  end   begin
