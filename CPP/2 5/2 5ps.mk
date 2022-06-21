
2 5ps.dll: dlldata.obj 2 5_p.obj 2 5_i.obj
	link /dll /out:2 5ps.dll /def:2 5ps.def /entry:DllMain dlldata.obj 2 5_p.obj 2 5_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del 2 5ps.dll
	@del 2 5ps.lib
	@del 2 5ps.exp
	@del dlldata.obj
	@del 2 5_p.obj
	@del 2 5_i.obj
