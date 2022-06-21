
重循环实验ps.dll: dlldata.obj 重循环实验_p.obj 重循环实验_i.obj
	link /dll /out:重循环实验ps.dll /def:重循环实验ps.def /entry:DllMain dlldata.obj 重循环实验_p.obj 重循环实验_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del 重循环实验ps.dll
	@del 重循环实验ps.lib
	@del 重循环实验ps.exp
	@del dlldata.obj
	@del 重循环实验_p.obj
	@del 重循环实验_i.obj
