
1ps.dll: dlldata.obj 1_p.obj 1_i.obj
	link /dll /out:1ps.dll /def:1ps.def /entry:DllMain dlldata.obj 1_p.obj 1_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del 1ps.dll
	@del 1ps.lib
	@del 1ps.exp
	@del dlldata.obj
	@del 1_p.obj
	@del 1_i.obj
