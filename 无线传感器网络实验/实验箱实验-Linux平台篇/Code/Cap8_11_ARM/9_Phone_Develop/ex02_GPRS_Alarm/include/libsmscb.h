#ifndef LIBSMSCB_H
#define LIBSMSCB_H

#define SMSCB_DEFAULT_PORT	0x7247
#define SMSCB_PKG_PREFIX	"$GS"
enum {
    GSR_MINREQUEST = 0,
    GSR_SENDSMS,                // <phone>-<sms content>
    GSR_REGISTER,
    GSR_UNREGISTER,
    GSR_MAXREQUEST,
    GSP_MINRESPONSE = 0x40,
    GSP_STATUS,                 // <error code>
    GSP_NEWSMS,                 // <phone>-<date time>-<sms content>
    GSP_MAXRESPONSE
};

#ifdef __cplusplus
extern"C"{
#endif

typedef void (*SMSUserCB)(const char *phone, const char *date_time, const char *smsContent, void *arg);

int SMSCB_SendSMS(const char *server, const char *phone, const char *sms);
void *SMSCB_RegisterSMSReceiver(const char *server, SMSUserCB callback, void *arg);
void SMSCB_UnregisterSMSReceiver(void *handle);

#ifdef __cplusplus
}
#endif
#endif // LIBSMSCB_H
