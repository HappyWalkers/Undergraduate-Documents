
// Resource Table
// Created by IDE, Do not modify this table

.TEXT
.public _RES_Table;
.external __RES_48_48K_sa
.public _RES_48_48K_SA;
.external __RES_48_48K_ea;
.public _RES_48_48K_EA;
.external __RES_72_72K_sa
.public _RES_72_72K_SA;
.external __RES_72_72K_ea;
.public _RES_72_72K_EA;
.external __RES_K72_72K_sa
.public _RES_K72_72K_SA;
.external __RES_K72_72K_ea;
.public _RES_K72_72K_EA;


_RES_Table:

_RES_48_48K_SA:
	.DW offset __RES_48_48K_sa,seg __RES_48_48K_sa;
_RES_48_48K_EA:
	.DW offset __RES_48_48K_ea,seg __RES_48_48K_ea;

_RES_72_72K_SA:
	.DW offset __RES_72_72K_sa,seg __RES_72_72K_sa;
_RES_72_72K_EA:
	.DW offset __RES_72_72K_ea,seg __RES_72_72K_ea;

_RES_K72_72K_SA:
	.DW offset __RES_K72_72K_sa,seg __RES_K72_72K_sa;
_RES_K72_72K_EA:
	.DW offset __RES_K72_72K_ea,seg __RES_K72_72K_ea;


// End Table
.PUBLIC T_SACM_S480_SpeechTable
T_SACM_S480_SpeechTable:
	.DW _RES_48_48K_SA
	.DW _RES_72_72K_SA
	.DW _RES_K72_72K_SA
