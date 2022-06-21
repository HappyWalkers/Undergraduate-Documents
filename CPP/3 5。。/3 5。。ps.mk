
3 5。。ps.dll: dlldata.obj 3 5。。_p.obj 3 5。。_i.obj
	link /dll /out:3 5。。ps.dll /def:3 5。。ps.def /entry:DllMain dlldata.obj 3 5。。_p.obj 3 5。。_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del 3 5。。ps.dll
	@del 3 5。。ps.lib
	@del 3 5。。ps.exp
	@del dlldata.obj
	@del 3 5。。_p.obj
	@del 3 5。。_i.obj
