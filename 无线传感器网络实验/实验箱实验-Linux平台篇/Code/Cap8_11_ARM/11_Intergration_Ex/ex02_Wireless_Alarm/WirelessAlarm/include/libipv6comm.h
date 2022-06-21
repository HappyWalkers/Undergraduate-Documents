#ifndef _LIBIPV6COMM_H_
#define _LIBIPV6COMM_H_

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

#define	IPV6_ADDR_LEN		16
#define VALID_NWKADDR		"ffffffff"
typedef struct ipv6comm_node_func_t{
	unsigned char funcCode, funcID;
	unsigned char rCycle;
}IPV6COMM_NODE_FUNC;

typedef struct ipv6comm_node_t{
	unsigned char nwkAddr[IPV6_ADDR_LEN];		//ipv6 addr -->2001:0410:0000:1234:FB00:1400:5000:45FF
	//unsigned short nwkPort;
	//unsigned char hwAddr[8];			//for IPV6 mac 去掉与mac 地址有关的地方
	
	int funcNum;
	IPV6COMM_NODE_FUNC *funcInfo;   //function list
}IPV6COMM_NODE;


externC EXPORT_SYMBOL IPV6COMM_NODE *ipv6comm_getNode_byAddr(const char *ip, unsigned char nwkAddr[IPV6_ADDR_LEN]);
externC EXPORT_SYMBOL IPV6COMM_NODE *ipv6comm_getNode_byType(const char *ip, int type,int id);
externC EXPORT_SYMBOL int ipv6comm_getAllNode(const char *ip, IPV6COMM_NODE **nodes);
externC EXPORT_SYMBOL IPV6COMM_NODE *ipv6comm_node_dup(const IPV6COMM_NODE *node);
externC EXPORT_SYMBOL IPV6COMM_NODE *ipv6comm_node_list_dup(const IPV6COMM_NODE *node, int count);
externC EXPORT_SYMBOL void ipv6comm_delete_node(IPV6COMM_NODE *node);
externC EXPORT_SYMBOL void ipv6comm_delete_node_list(IPV6COMM_NODE *node, int count);
externC EXPORT_SYMBOL int ipv6comm_sendNode_byPoint(const char *ip, unsigned char nwkAddr[IPV6_ADDR_LEN], int point, const char *data, int len);
externC EXPORT_SYMBOL int ipv6comm_sendNode_byType(const char *ip, int type, int id, const char *data, int len);
externC EXPORT_SYMBOL int ipv6comm_getNodeData_byPoint(const char *ip, unsigned char nwkAddr[IPV6_ADDR_LEN], int point, char **data);
externC EXPORT_SYMBOL int ipv6comm_getNodeData_byType(const char *ip, int type, int id, char **data);

typedef void (*IPV6CB_NEW_NODE)(void *arg, unsigned char nwkAddr[IPV6_ADDR_LEN]);
typedef void (*IPV6CB_NEW_FUNC)(void *arg, unsigned char nwkAddr[IPV6_ADDR_LEN], int funcNum, IPV6COMM_NODE_FUNC *funcList);
typedef void (*IPV6CB_NEW_DATA)(void *arg, unsigned char nwkAddr[IPV6_ADDR_LEN], int endPoint, int funcCode, int funcID, char *data, int len);
typedef void (*IPV6CB_NODE_GONE)(void *arg, unsigned char nwkAddr[IPV6_ADDR_LEN]);
typedef void (*IPV6CB_SERVER_GONE)(void *arg);

externC EXPORT_SYMBOL void *ipv6comm_register(const char *ip,
            IPV6CB_NEW_NODE cb_newNode,
            IPV6CB_NEW_FUNC cb_newFunc,
            IPV6CB_NEW_DATA cb_newData,
            IPV6CB_NODE_GONE cb_nodeGone,
            IPV6CB_SERVER_GONE cb_serverGone,
            void *arg);
externC EXPORT_SYMBOL int ipv6comm_unregister(void *user);

externC EXPORT_SYMBOL const char *ipv6comm_strerror(int errCode);

externC EXPORT_SYMBOL void initwsn4python();

#endif // _LIBWSNCOMM_H_
