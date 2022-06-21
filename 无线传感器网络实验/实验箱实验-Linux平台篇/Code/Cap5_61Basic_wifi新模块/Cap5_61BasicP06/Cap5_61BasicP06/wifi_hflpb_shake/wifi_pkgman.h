#ifndef _WIFI_PKGMAN_H_
#define _WIFI_PKGMAN_H_

typedef unsigned char uint8;

// ����ͨ�����ݰ�
struct wificomm_pkg_data_t {
    uint8 endPoint;                 // remote endpoint
    uint8 data[0];
} __attribute__((packed));
typedef struct wificomm_pkg_data_t WIFICOMMPKG_DATA;
struct wificomm_pkg_t {
    uint8 fcs;
    uint8 sop;                      // always 0x03
    uint8 len;                      //len = sizeof(WIFICOMMPKG_DATA) + user data len
    union {
        uint8 dataBody[0];
        WIFICOMMPKG_DATA dataField;
    };
} __attribute__((packed));
typedef struct wificomm_pkg_t WIFICOMMPKG;

// �������ݰ���ʵ�ʳ���,������У���ֽ�
#define WIFICOMMPKG_LEN(pkg)         (sizeof(WIFICOMMPKG) + (pkg)->len - sizeof(WIFICOMMPKG_DATA) - 1)
// �������ݰ���data_field.data����
#define WIFICOMMPKG_DATLEN(pkg)      ((pkg)->len - sizeof(WIFICOMMPKG_DATA))

#define WIFICOMM_SOP                 0x03

// ����ڵ��0�˵�Ϊ���ƶ˵�,�������ݵ������򳤶�Ϊ1�ֽ�
#define WIFICOMM_NODEEP_CONTROL      0
enum {
    CtlQueryProfile = 0x01,
    CtlQuerySpecial = 0x02
};

// �ڵ㹦���б����ݽṹ
struct wificomm_func_info_t {
    uint8 type;
    uint8 id;
    uint8 cycle;
} __attribute__((packed));
typedef struct wificomm_func_info_t WIFIC_FUNCINFO;

struct wificomm_funcinfo_pkg_t {
    uint8 cmd;                      // always = CtlQueryProfile
    uint8 funcNum;
    WIFIC_FUNCINFO funcList[0];
} __attribute__((packed));
typedef struct wificomm_funcinfo_pkg_t WIFIC_FUNCINFOPKG;
#define FUNCINFOPKG_SIZE(l) (sizeof(WIFIC_FUNCINFOPKG) + (l)->funcNum * sizeof(WIFIC_FUNCINFO))

WIFICOMMPKG *pkgman_create_package(uint8 nodeEP, const void *data, uint8 len);
void pkgman_delete_package(WIFICOMMPKG *pkg);
int pkgman_send_package(int fd, const WIFICOMMPKG *pkg);
int pkgman_send_packageEx(int fd, unsigned char nodeEP, const void *data, int len);

typedef enum { STAT_SOP, STAT_LEN, STAT_DATA, STAT_FCS, STAT_DONE } PM_RECVSTAT;
typedef struct pkgman_recv_info_t {
    PM_RECVSTAT status;
    uint8 dataIdx;
    uint8 *dataPnter;
    WIFICOMMPKG *pkg;
} PM_RECVINFO;
PM_RECVINFO *pkgman_init_recv_info(PM_RECVINFO *info);
int pkgman_recv_packageCb(PM_RECVINFO *info, const unsigned char *data, int len, WIFICOMMPKG **pkg, const unsigned char **restData, int *restLen);

#endif//_WIFI_PKGMAN_H_
