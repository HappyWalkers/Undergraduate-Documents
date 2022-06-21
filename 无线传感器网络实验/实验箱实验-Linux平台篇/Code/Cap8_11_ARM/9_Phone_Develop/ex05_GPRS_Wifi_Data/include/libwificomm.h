#ifndef _LIBWIFICOMM_H_
#define _LIBWIFICOMM_H_

#ifndef externC
	#ifdef __cplusplus
		#define externC extern"C"
	#else
		#define externC
	#endif
#endif

#ifndef EXPORT_SYMBOL
#ifndef _WIN32
#define EXPORT_SYMBOL   __attribute__((visibility("default")))
#else
#ifdef _EXPORT
#define EXPORT_SYMBOL  __declspec(dllexport)
#else
#define EXPORT_SYMBOL  __declspec(dllimport)
#endif
#endif
#endif

typedef struct wifi_node_func_t{
    unsigned char funcCode, funcID;
    unsigned char rCycle;
}WIFI_NODE_FUNC;

typedef struct wifi_node_t{
	char ip[16];
	int funcNum;
	WIFI_NODE_FUNC *funcInfo;   //function list
}WIFI_NODE;


externC EXPORT_SYMBOL WIFI_NODE *wificomm_getNode_byAddr(const char *serverIP, const char *nodeIP);
externC EXPORT_SYMBOL WIFI_NODE *wificomm_getNode_byType(const char *serverIP, int type,int id);
externC EXPORT_SYMBOL int wificomm_getAllNode(const char *serverIP, WIFI_NODE **nodes);
externC EXPORT_SYMBOL WIFI_NODE *wificomm_node_dup(const WIFI_NODE *node);
externC EXPORT_SYMBOL WIFI_NODE_FUNC *wificomm_funclist_dup(const WIFI_NODE_FUNC *func, int funcNum);
externC EXPORT_SYMBOL WIFI_NODE *wificomm_node_list_dup(const WIFI_NODE *node, int count);
externC EXPORT_SYMBOL void wificomm_delete_node(WIFI_NODE *node);
externC EXPORT_SYMBOL void wificomm_delete_funclist(WIFI_NODE_FUNC *funcInfo);
externC EXPORT_SYMBOL void wificomm_delete_node_list(WIFI_NODE *node, int count);
externC EXPORT_SYMBOL int wificomm_sendNode_byPoint(const char *serverIP, const char *nodeIP, int point, const char *data, int len);
externC EXPORT_SYMBOL int wificomm_sendNode_byType(const char *serverIP, int type, int id, const char *data, int len);
externC EXPORT_SYMBOL int wificomm_getNodeData_byPoint(const char *serverIP, const char *nodeIP, int point, char **data);
externC EXPORT_SYMBOL int wificomm_getNodeData_byType(const char *serverIP, int type, int id, char **data);

typedef void (*WIFICB_NEW_NODE)(void *arg, const char *nodeIP, int funcNum, WIFI_NODE_FUNC *funcList);
typedef void (*WIFICB_NEW_DATA)(void *arg, const char *nodeIP, int endPoint, int funcCode, int funcID, char *data, int len);
typedef void (*WIFICB_NODE_GONE)(void *arg, const char *nodeIP);
typedef void (*WIFICB_SERVER_GONE)(void *arg);
externC EXPORT_SYMBOL void *wificomm_register(const char *serverIP,
            WIFICB_NEW_NODE cb_newNode,
            WIFICB_NEW_DATA cb_newData,
            WIFICB_NODE_GONE cb_nodeGone,
            WIFICB_SERVER_GONE cb_serverGone,
            void *arg);
externC EXPORT_SYMBOL int wificomm_unregister(void *user);

externC EXPORT_SYMBOL const char *wificomm_strerror(int errCode);

#endif // _LIBWIFICOMM_H_
