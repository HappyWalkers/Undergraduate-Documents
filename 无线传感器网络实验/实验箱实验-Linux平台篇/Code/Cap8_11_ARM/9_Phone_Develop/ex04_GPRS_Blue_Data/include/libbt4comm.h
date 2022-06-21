#ifndef _LIBBT4COMM_H_
#define _LIBBT4COMM_H_

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

#define	BT_ADDR_LEN	6
#define VALID_NWKADDR		"ffffffff"	
typedef struct bt4comm_node_func_t{
    unsigned char funcCode, funcID;
    unsigned char rCycle;
}BT4COMM_NODE_FUNC;

#ifndef     BTCOMM_ADDRTYPE
#define     BTCOMM_ADDRTYPE     0     //addrType
#endif
typedef struct bt4comm_node_t{
    	//unsigned short nwkAddr;
        unsigned char nwkAddr[BT_ADDR_LEN];		//bt addr:char dest[18] = "00:12:01:31:01:13";
        unsigned char addrType;		//表示节点的地址类型
		
    	//unsigned short parAddr;
    	unsigned char hwAddr[8];

	int funcNum;
	BT4COMM_NODE_FUNC *funcInfo;   //function list
}BT4COMM_NODE;


externC EXPORT_SYMBOL BT4COMM_NODE *bt4comm_getNode_byAddr(const char *ip, unsigned char nwkAddr[BT_ADDR_LEN], unsigned char addrType );
externC EXPORT_SYMBOL BT4COMM_NODE *bt4comm_getNode_byType(const char *ip, int type,int id);
externC EXPORT_SYMBOL int bt4comm_getAllNode(const char *ip, BT4COMM_NODE **nodes);
externC EXPORT_SYMBOL BT4COMM_NODE *bt4comm_node_dup(const BT4COMM_NODE *node);
externC EXPORT_SYMBOL BT4COMM_NODE *bt4comm_node_list_dup(const BT4COMM_NODE *node, int count);
externC EXPORT_SYMBOL void bt4comm_delete_node(BT4COMM_NODE *node);
externC EXPORT_SYMBOL void bt4comm_delete_node_list(BT4COMM_NODE *node, int count);
externC EXPORT_SYMBOL int bt4comm_sendNode_byPoint(const char *ip, unsigned char nwkAddr[BT_ADDR_LEN], unsigned char addrType, int point, const char *data, int len);
externC EXPORT_SYMBOL int bt4comm_sendNode_byType(const char *ip, int type, int id, const char *data, int len);
externC EXPORT_SYMBOL int bt4comm_getNodeData_byPoint(const char *ip, unsigned char nwkAddr[BT_ADDR_LEN], unsigned char addrType, int point, char **data);
externC EXPORT_SYMBOL int bt4comm_getNodeData_byType(const char *ip, int type, int id, char **data);

typedef void (*BTCB_NEW_NODE)(void *arg, unsigned char nwkAddr[BT_ADDR_LEN]);
typedef void (*BTCB_NEW_FUNC)(void *arg, unsigned char nwkAddr[BT_ADDR_LEN], int funcNum, BT4COMM_NODE_FUNC *funcList);
typedef void (*BTCB_NEW_DATA)(void *arg, unsigned char nwkAddr[BT_ADDR_LEN], int endPoint, int funcCode, int funcID, char *data, int len);
typedef void (*BTCB_NODE_GONE)(void *arg, unsigned char nwkAddr[BT_ADDR_LEN]);
typedef void (*BTCB_SERVER_GONE)(void *arg);
externC EXPORT_SYMBOL void *bt4comm_register(const char *ip,
            BTCB_NEW_NODE cb_newNode,
            BTCB_NEW_FUNC cb_newFunc,
            BTCB_NEW_DATA cb_newData,
            BTCB_NODE_GONE cb_nodeGone,
            BTCB_SERVER_GONE cb_serverGone,
            void *arg);
externC EXPORT_SYMBOL int bt4comm_unregister(void *user);

externC EXPORT_SYMBOL const char *bt4comm_strerror(int errCode);

externC EXPORT_SYMBOL void initbt44python();

#endif // _LIBBT4COMM_H_
