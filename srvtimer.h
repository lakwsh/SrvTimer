#include "eiface.h"
#include "filesystem.h"

class srvtimer:public IServerPluginCallbacks{
public:
	virtual bool Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory);
	virtual void Unload();
	virtual void Pause(){ }
	virtual void UnPause(){ }
	virtual const char *GetPluginDescription(){ return "SrvTimer v1.0.0, https://github.com/lakwsh/srvtimer"; }
	virtual void LevelInit(char const *pMapName){ }
	virtual void ServerActivate(edict_t *pEdictList, int edictCount, int clientMax){ }
	virtual void GameFrame(bool simulating){ }
	virtual void LevelShutdown(){ }
	virtual void ClientActive(edict_t *pEntity){ }
	virtual void ClientDisconnect(edict_t *pEntity){ }
	virtual void ClientPutInServer(edict_t *pEntity, char const *playername){ }
	virtual void SetCommandClient(int index){ }
	virtual void ClientSettingsChanged(edict_t *pEdict){ }
	virtual PLUGIN_RESULT ClientConnect(bool *bAllowConnect, edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen){ return PLUGIN_CONTINUE; }
	virtual PLUGIN_RESULT ClientCommand(edict_t *pEntity, const CCommand &args){ return PLUGIN_CONTINUE; }
	virtual PLUGIN_RESULT NetworkIDValidated(const char *pszUserName, const char *pszNetworkID){ return PLUGIN_CONTINUE; }
	virtual void OnQueryCvarValueFinished(QueryCvarCookie_t iCookie, edict_t *pPlayerEntity, EQueryCvarValueStatus eStatus, const char *pCvarName, const char *pCvarValue){ }

	static void alarm_handler(int signum);
	static FileNameHandle_t FindOrAddFileName(void *cls, char const *pFileName);
private:
	static uint **p_filesystem;
	static uint p_FindOrAddFileName;
};
extern srvtimer g_srvtimer;
