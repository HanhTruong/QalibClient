
QalibClientps.dll: dlldata.obj QalibClient_p.obj QalibClient_i.obj
	link /dll /out:QalibClientps.dll /def:QalibClientps.def /entry:DllMain dlldata.obj QalibClient_p.obj QalibClient_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del QalibClientps.dll
	@del QalibClientps.lib
	@del QalibClientps.exp
	@del dlldata.obj
	@del QalibClient_p.obj
	@del QalibClient_i.obj
