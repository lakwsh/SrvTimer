#include "srvtimer.h"
#include "signature.h"
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

srvtimer g_srvtimer;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(srvtimer, IServerPluginCallbacks, INTERFACEVERSION_ISERVERPLUGINCALLBACKS, g_srvtimer);

uint **srvtimer::p_filesystem = NULL;
uint srvtimer::p_FindOrAddFileName = 0;

void srvtimer::alarm_handler(int signum){
	Msg("[SrvTimer] Timeout!\n");
	abort();
}

FileNameHandle_t srvtimer::FindOrAddFileName(void *cls, char const *pFileName){
	alarm(5);
	FileNameHandle_t ret = ((FileNameHandle_t (*)(void *, char const *))p_FindOrAddFileName)(cls, pFileName);
	alarm(0);
	return ret;
}

bool srvtimer::Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory){
	auto p_filesystem = (uint **)interfaceFactory(FILESYSTEM_INTERFACE_VERSION, NULL);
	if(!p_filesystem) return false;
	p_FindOrAddFileName = p_filesystem[0][37];
	if(!p_FindOrAddFileName) return false;
	signal(SIGALRM, alarm_handler);
	unsigned char hook[6] = {0x04, 0x00};
	*(uint *)&hook[2] = (uint)&FindOrAddFileName;
	write_signature(&p_filesystem[0][37], hook);
	Msg("[SrvTimer] Initialized.\n");
	return true;
}

void srvtimer::Unload(){
	if(!p_filesystem) return;
	signal(SIGALRM, SIG_DFL);
	unsigned char restore[6] = {0x04, 0x00};
	*(uint *)&restore[2] = p_FindOrAddFileName;
	write_signature(&p_filesystem[0][37], restore);
	p_filesystem = NULL;
}
