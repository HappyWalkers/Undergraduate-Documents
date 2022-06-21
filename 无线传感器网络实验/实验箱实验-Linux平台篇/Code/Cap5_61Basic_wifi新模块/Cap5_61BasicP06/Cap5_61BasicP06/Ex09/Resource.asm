
// Resource Table
// Created by IDE, Do not modify this table

.TEXT
.public _RES_Table;
.external __RES_AT_FINISH_72K_sa
.public _RES_AT_FINISH_72K_SA;
.external __RES_AT_FINISH_72K_ea;
.public _RES_AT_FINISH_72K_EA;
.external __RES_FAIL_72K_sa
.public _RES_FAIL_72K_SA;
.external __RES_FAIL_72K_ea;
.public _RES_FAIL_72K_EA;
.external __RES_LIANJIE_72K_sa
.public _RES_LIANJIE_72K_SA;
.external __RES_LIANJIE_72K_ea;
.public _RES_LIANJIE_72K_EA;
.external __RES_SUCCESS_72K_sa
.public _RES_SUCCESS_72K_SA;
.external __RES_SUCCESS_72K_ea;
.public _RES_SUCCESS_72K_EA;
.external __RES_STATUS_INQ_72K_sa
.public _RES_STATUS_INQ_72K_SA;
.external __RES_STATUS_INQ_72K_ea;
.public _RES_STATUS_INQ_72K_EA;
.external __RES_ASS_72K_sa
.public _RES_ASS_72K_SA;
.external __RES_ASS_72K_ea;
.public _RES_ASS_72K_EA;
.external __RES_CUR_NET_72K_sa
.public _RES_CUR_NET_72K_SA;
.external __RES_CUR_NET_72K_ea;
.public _RES_CUR_NET_72K_EA;
.external __RES_NO_ASS_72K_sa
.public _RES_NO_ASS_72K_SA;
.external __RES_NO_ASS_72K_ea;
.public _RES_NO_ASS_72K_EA;


_RES_Table:

_RES_AT_FINISH_72K_SA:
	.DW offset __RES_AT_FINISH_72K_sa,seg __RES_AT_FINISH_72K_sa;
_RES_AT_FINISH_72K_EA:
	.DW offset __RES_AT_FINISH_72K_ea,seg __RES_AT_FINISH_72K_ea;

_RES_FAIL_72K_SA:
	.DW offset __RES_FAIL_72K_sa,seg __RES_FAIL_72K_sa;
_RES_FAIL_72K_EA:
	.DW offset __RES_FAIL_72K_ea,seg __RES_FAIL_72K_ea;

_RES_LIANJIE_72K_SA:
	.DW offset __RES_LIANJIE_72K_sa,seg __RES_LIANJIE_72K_sa;
_RES_LIANJIE_72K_EA:
	.DW offset __RES_LIANJIE_72K_ea,seg __RES_LIANJIE_72K_ea;

_RES_SUCCESS_72K_SA:
	.DW offset __RES_SUCCESS_72K_sa,seg __RES_SUCCESS_72K_sa;
_RES_SUCCESS_72K_EA:
	.DW offset __RES_SUCCESS_72K_ea,seg __RES_SUCCESS_72K_ea;

_RES_STATUS_INQ_72K_SA:
	.DW offset __RES_STATUS_INQ_72K_sa,seg __RES_STATUS_INQ_72K_sa;
_RES_STATUS_INQ_72K_EA:
	.DW offset __RES_STATUS_INQ_72K_ea,seg __RES_STATUS_INQ_72K_ea;

_RES_ASS_72K_SA:
	.DW offset __RES_ASS_72K_sa,seg __RES_ASS_72K_sa;
_RES_ASS_72K_EA:
	.DW offset __RES_ASS_72K_ea,seg __RES_ASS_72K_ea;

_RES_CUR_NET_72K_SA:
	.DW offset __RES_CUR_NET_72K_sa,seg __RES_CUR_NET_72K_sa;
_RES_CUR_NET_72K_EA:
	.DW offset __RES_CUR_NET_72K_ea,seg __RES_CUR_NET_72K_ea;

_RES_NO_ASS_72K_SA:
	.DW offset __RES_NO_ASS_72K_sa,seg __RES_NO_ASS_72K_sa;
_RES_NO_ASS_72K_EA:
	.DW offset __RES_NO_ASS_72K_ea,seg __RES_NO_ASS_72K_ea;


// End Table
.public T_SACM_S480_SpeechTable
T_SACM_S480_SpeechTable:	
	.DW _RES_LIANJIE_72K_SA  	 //0
	.DW _RES_FAIL_72K_SA   		//1
	.DW _RES_SUCCESS_72K_SA   	//2
	.DW _RES_AT_FINISH_72K_SA   //3
	
	.DW _RES_STATUS_INQ_72K_SA  	 //4 网络状态查询
	.DW _RES_CUR_NET_72K_SA  	 //5  当前网络状态
	.DW _RES_ASS_72K_SA  	 //6	已连接
	.DW _RES_NO_ASS_72K_SA  	 //7 未连接
