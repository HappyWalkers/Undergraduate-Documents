
��ѭ��ʵ��ps.dll: dlldata.obj ��ѭ��ʵ��_p.obj ��ѭ��ʵ��_i.obj
	link /dll /out:��ѭ��ʵ��ps.dll /def:��ѭ��ʵ��ps.def /entry:DllMain dlldata.obj ��ѭ��ʵ��_p.obj ��ѭ��ʵ��_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del ��ѭ��ʵ��ps.dll
	@del ��ѭ��ʵ��ps.lib
	@del ��ѭ��ʵ��ps.exp
	@del dlldata.obj
	@del ��ѭ��ʵ��_p.obj
	@del ��ѭ��ʵ��_i.obj
