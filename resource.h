/* ========================================================================
    Project  Name			: Fast/Force copy file and directory
    Create					: 2016-02-25
    Update					: 2016-02-25
    Copyright				: Kengo Sawatsu
    port update	            : 2016-02-28
    Reference				:
    Summary 				: メッセージカタログ,errnoヘッダ
    ======================================================================== */

#include <errno.h>
#include <attr/xattr.h>

#define IDS_MKDIR					1
#define IDS_RMDIR					2
#define IDS_SRC_SELECT				3
#define IDS_DST_SELECT				4
#define IDS_SAMEDISK				5
#define IDS_DIFFDISK				6
#define IDS_FIX_SAMEDISK			7
#define IDS_FIX_DIFFDISK			8
#define IDS_VERIFY					9
#define IDS_SHA1					10
#define IDS_MD5						11
#define IDS_XX						12
#define IDS_SHA2_256				13
#define IDS_SHA2_512				14
#define IDS_SHA3_256				15
#define IDS_SHA3_512				16
#define IDS_SIZEVERIFY				17
#define IDS_ALLSKIP 				20
#define IDS_ATTRCMP 				21
#define IDS_UPDATECOPY 				22
#define IDS_FORCECOPY 				23
#define IDS_SYNCCOPY 				24
#define IDS_MUTUAL 					25
#define IDS_MOVEATTR 				26
#define IDS_MOVEFORCE 				27
#define IDS_DELETE 					28
#define IDS_EXECUTE 				29
#define IDS_CANCEL 					30
#define IDS_BEHAVIOR 				31
#define IDS_UPDATE 					32
#define IDS_FILESELECT 				33
#define IDS_DIRSELECT 				34
#define IDS_SAMEPATHERR 			41
#define IDS_PARENTPATHERR 			42
#define IDS_MOVECONFIRM 			43
#define IDS_SHELLEXT_MODIFY 		44
#define IDS_SHELLEXT_EXEC 			45
#define IDS_FASTCOPYURL 			46
#define IDS_FASTCOPYHELP 			47
#define IDS_EXCEPTIONLOG 			48
#define IDS_SYNCCONFIRM 			49
#define IDS_BACKSLASHERR 			50
#define IDS_DELETECONFIRM 			51
#define IDS_ERRSTOP 				60
#define IDS_CONFIRMFORCEEND 		61
#define IDS_STOPCONFIRM 			62
#define IDS_DELSTOPCONFIRM 			63
#define IDS_DELCONFIRM 				64
#define IDS_DUPCONFIRM 				65
#define IDS_NOFILTER_USAGE 			66
#define IDS_LISTCONFIRM 			67
#define IDS_JOBNAME 				68
#define IDS_JOBNOTFOUND 			69
#define IDS_LISTING 				70
#define IDS_FIXPOS_MSG 				72
#define IDS_FIXSIZE_MSG 			73
#define IDS_FINACTNAME 				74
#define IDS_FINACTMENU 				75
#define IDS_FINACT_NORMAL 			76
#define IDS_ELEVATE 				77
#define IDS_SHUTDOWN_MSG 			78
#define IDS_HIBERNATE_MSG 			79
#define IDS_SUSPEND_MSG 			80
#define IDS_FINACT_SUSPEND 			81
#define IDS_FINACT_HIBERNATE 		82
#define IDS_FINACT_SHUTDOWN 		83
#define IDS_DATEFORMAT_MSG 			84
#define IDS_SIZEFORMAT_MSG 			85
#define IDS_CMDNOTFOUND 			86
#define IDS_VERIFYNOTFOUND 			87
#define IDS_FINACTNOTFOUND 			88
#define IDS_DATEISOVER 				89
#define IDS_OPENFILE 				90
#define IDS_SOUNDFILEERR 			91
#define IDS_REPORTOUT 				92
#define IDS_VERIFY_FILE_MISSING_ERR 93
#define IDS_VERIFY_FILE_SIZE_ERR 	94
#define IDS_VERIFY_FILE_DATE_ERR 	95
#define IDS_VERIFY_DIR_MISSING_ERR 	96
#define IDS_VERIFY_DIR_SIZE_ERR 	97
#define IDS_VERIFY_DIR_DATE_ERR 	98
#define IDS_REPORTING_NOT_CANCEL 	99
#define IDS_UNDO 					100
#define IDS_CUT 					101
#define IDS_COPY 					102
#define IDS_PASTE 					103
#define IDS_DEL 					104
#define IDS_SELECTALL 				105
#define IDS_STATUS_WAITING_OTHER 	106
#define IDS_STATUS_PRESEARCHING 	107
#define IDS_STATUS_COPYING 			108
#define IDS_STATUS_VERIFYING 		109
#define IDS_STATUS_LISTING			110
#define IDS_STATUS_DELETING			111
#define IDS_XYARG_NOTFOUND			112
#define IDS_CLIMODE_PROHIBIT		113
#define IDS_FASTCOPYURL_EN			114
#define IDS_CMDCSVNOTFOUND			119
#define IDS_FACMD_ALWAYS 			120
#define IDS_FACMD_NORMAL 			121
#define IDS_FACMD_ERROR 			122
#define IDS_CMDCSVWITHFILELOG_ERROR	123
#define IDS_CMDLTFSATTR_ERROR		124
#define IDS_PATH_INITERROR			125
#define IDS_CONFIRM_REJECTED		126
#define IDS_VERIFY_ERROR_WARN_1		127
#define IDS_VERIFY_ERROR_WARN_2		128
#define IDS_VERIFY_ERROR_WARN_3		129
#define IDS_MOVEDIR_FAILED			130
#define IDS_NEWWINDOW_FAILED        131

#define IDS_FASTCOPY 				1000
#define IDS_USAGE					1001
#define IDS_HIST_CLEAR				1002
#define IDS_SIZESKIP			    1003
#

#define IDS_CMD_NOEXIST_ONLY 		1080
#define IDS_CMD_DIFF 				1081
#define IDS_CMD_UPDATE 				1082
#define IDS_CMD_FORCE_COPY 			1083
#define IDS_CMD_SYNC 				1084
#define IDS_CMD_MUTUAL 				1085
#define IDS_CMD_MOVE 				1086
#define IDS_CMD_DELETE 				1087
#define IDS_CMD_OPT 				1088
#define IDS_CMD_MOVEATTR 			1089
#define IDS_BUFSIZE_OPT 			1090
#define IDS_ERRSTOP_OPT 			1091
#define IDS_OPENWIN_OPT 			1092
#define IDS_AUTOCLOSE_OPT 			1093
#define IDS_FORCECLOSE_OPT 			1094
#define IDS_NOEXEC_OPT 				1095
#define IDS_NOCONFIRMDEL_OPT 		1096
#define IDS_LOG_OPT 				1097
#define IDS_TO_OPT 					1098
#define IDS_ESTIMATE_OPT 			1099
#define IDS_JOB_OPT 				1100
#define IDS_AUTOSLOW_OPT 			1101
#define IDS_SPEED_OPT 				1102
#define IDS_UTF8LOG_OPT				1103
#define IDS_ALLFILES_FILTER			1104
#define IDS_CMD_VERIFY				1105
#define IDS_JOBLIST_OPT				1106
#define IDS_CMD_SIZE				1107
#define IDS_CMD_SIZEVERIFY			1108

#define IDS_INCLUDE_OPT 		    1115
#define IDS_EXCLUDE_OPT 		    1117
#define IDS_REGEXP_OPT 				1119
#define IDS_FORCESTART_OPT 			1120
#define IDS_SKIPEMPTYDIR_OPT 		1121
#define IDS_DISKMODE_OPT 			1122
#define IDS_DISKMODE_SAME 			1123
#define IDS_DISKMODE_DIFF 			1124
#define IDS_DISKMODE_AUTO 			1125
#define IDS_ACL_OPT 				1126
#define IDS_STREAM_OPT 				1127
#define IDS_OWDEL_OPT 				1128
#define IDS_SPEED_FULL 				1129
#define IDS_SPEED_AUTOSLOW 			1130
#define IDS_SPEED_SUSPEND 			1131
#define IDS_REPARSE_OPT 			1132
#define IDS_RUNAS_OPT 				1133
#define IDS_USERDIR_MENU 			1134
#define IDS_LOGFILE_OPT 			1135
#define IDS_NOCONFIRMSTOP_OPT 		1136
#define IDS_VERIFY_OPT 				1137
#define IDS_USEROLDDIR_MENU 		1138
#define IDS_WIPEDEL_OPT 			1139
#define IDS_SRCFILE_OPT 			1140
#define IDS_SRCFILEW_OPT 			1141
#define IDS_FINACT_OPT 				1142
#define IDS_NOTEPAD 				1146
#define IDS_LINKDEST_OPT 			1147
#define IDS_RECREATE_OPT 			1148
#define IDS_FROMDATE_OPT 			1149
#define IDS_TODATE_OPT 				1150
#define IDS_MINSIZE_OPT 			1151
#define IDS_MAXSIZE_OPT 			1152
#define IDS_STANDBY 				1153
#define IDS_HIBERNATE 				1154
#define IDS_SHUTDOWN 				1155
#define IDS_FILELOG_OPT 			1156
#define IDS_TRUE 					1157
#define IDS_FALSE 					1158
#define IDS_FILELOGNAME 			1159
#define IDS_FILELOG_SUBDIR 			1160
#define IDS_INSTALL_OPT 			1161
#define IDS_VERIFYMD5_OPT 			1162
#define IDS_VERIFYSHA1_OPT 			1163
#define IDS_VERIFYXX_OPT 			1164
#define IDS_VERIFYSHA2_256_OPT 		1165
#define IDS_VERIFYSHA2_512_OPT 		1166
#define IDS_VERIFYSHA3_256_OPT 		1167
#define IDS_VERIFYSHA3_512_OPT 		1168
#define IDS_FNOCACHE_OPT 			1169
#define IDS_LTFS_OPT 				1170
#define IDS_VERIFY_FALSE_OPT 		1171
#define IDS_DOTIGNORE_OPT 			1172
#define IDS_X_OPT 					1173
#define IDS_Y_OPT 					1174
#define IDS_FILECSVNAME				1175
#define IDS_FILECSVTITLE			1176
#define IDS_FILECSVEX				1177
#define IDS_FILECSV_OPT				1178

#define IDS_FULLSPEED_DISP 			1201
#define IDS_AUTOSLOW_DISP 			1202
#define IDS_SUSPEND_DISP 			1203
#define IDS_RATE_DISP 				1204

#define IDS_DST_CASE_ERR 			1206
#define IDS_FINACT_CRESAV_INFO 		1207
#define IDS_FINACT_DELETE_INFO 		1208
#define IDS_JOBACT_SUCCESS_INFO 	1209
#define IDS_JOBACT_ERROR_INFO 		1210
#define IDS_FINACT_WAIT_INFO 		1211
#define IDS_GROWL_TITLE 			1212
#define IDS_PATH_INPUT 				1213
#define IDS_PATH_ADDED 				1214
#define IDS_JOBACT_ERROR_DETAIL_INFO 1215
#define IDS_SRCHEAP_ERROR 			1216
#define IDS_SRCPATH_CLEAR 			1217
#define IDS_DSTPATH_CLEAR 			1218
#define IDS_FINACT_SANDBOX_SOUND_ERR 1219
#define IDS_ABOUT_WINDOWTITLE		1220
#define IDS_FINACT_EMPTYSTR			1221

#define IDS_SIZECHANGED_ERROR		1229
#define IDS_LTFS_REPLACE_WARN		1230
#define IDS_LTFS_REPLACE_ERROR		1231
#define IDS_JOBLISTACT_SUCCESS_INFO	1232
#define IDS_JOBLISTACT_ERROR_INFO	1233
#define IDS_JOB_DELETEREQ			1234
#define IDS_JOBLISTDEL_SUCCESS_INFO	1235
#define IDS_JOBLISTDEL_ERROR_INFO	1236
#define IDS_JOBLISTMAX_ERROR		1237
#define IDS_JOBGROUPDEL_ERROR		1238
#define IDS_JOBLIST_PLACEHOLDER		1239
#define IDS_JOBLIST_CANCEL			1240
#define IDS_JOBLIST_EXECUTE			1241
#define IDS_JOBLIST_JOBSAVE			1242
#define IDS_JOBLISTNOTFOUND			1243
#define IDS_SINGLELIST_MENUNAME		1244
#define IDS_JOBLIST_CHANGENOTIFY	1245
#define IDS_JOBNAME_CHANGE			1246
#define IDS_JOBNAME_DUPERROR		1247
#define IDS_JOBLIST_MENUNAME		1248
#define IDS_SINGLEJOB_MODERROR		1249
#define IDS_JOBLISTRENAME_TITLE		1250
#define IDS_JOBLIST_DELETEREQ		1251
#define IDS_JOB_DELETEALLREQ		1252
#define IDS_JOB_CHANGEDNOTIFY		1253

#define TOOLTIP_TXTEDIT_SRC			1300
#define TOOLTIP_TXTEDIT_DST			1301

#define FINACT_MENUITEM			    30026

//4xxxx はerrnoをベースにRapidCopy独自のエラーメッセージ変換する用
#define RAPIDCOPY_ERRNO_BASE 		40000
#define RAPIDCOPY_ERRNO_EPERM 		RAPIDCOPY_ERRNO_BASE + EPERM
#define RAPIDCOPY_ERRNO_ENOENT 		RAPIDCOPY_ERRNO_BASE + ENOENT
#define RAPIDCOPY_ERRNO_EINTR 		RAPIDCOPY_ERRNO_BASE + EINTR
#define RAPIDCOPY_ERRNO_EIO 		RAPIDCOPY_ERRNO_BASE + EIO
#define RAPIDCOPY_ERRNO_ENXIO 		RAPIDCOPY_ERRNO_BASE + ENXIO
#define RAPIDCOPY_ERRNO_E2BIG 		RAPIDCOPY_ERRNO_BASE + E2BIG
#define RAPIDCOPY_ERRNO_ENOEXEC 	RAPIDCOPY_ERRNO_BASE + ENOEXEC
#define RAPIDCOPY_ERRNO_EBADF 		RAPIDCOPY_ERRNO_BASE + EBADF
#define RAPIDCOPY_ERRNO_ENOMEM 		RAPIDCOPY_ERRNO_BASE + ENOMEM
#define RAPIDCOPY_ERRNO_EACCES 		RAPIDCOPY_ERRNO_BASE + EACCES
#define RAPIDCOPY_ERRNO_EFAULT 		RAPIDCOPY_ERRNO_BASE + EFAULT
#define RAPIDCOPY_ERRNO_ENOTBLK 	RAPIDCOPY_ERRNO_BASE + ENOTBLK
#define RAPIDCOPY_ERRNO_EBUSY 		RAPIDCOPY_ERRNO_BASE + EBUSY
#define RAPIDCOPY_ERRNO_EEXIST 		RAPIDCOPY_ERRNO_BASE + EEXIST
#define RAPIDCOPY_ERRNO_EXDEV 		RAPIDCOPY_ERRNO_BASE + EXDEV
#define RAPIDCOPY_ERRNO_ENODEV 		RAPIDCOPY_ERRNO_BASE + ENODEV
#define RAPIDCOPY_ERRNO_ENOTDIR 	RAPIDCOPY_ERRNO_BASE + ENOTDIR
#define RAPIDCOPY_ERRNO_EISDIR 		RAPIDCOPY_ERRNO_BASE + EISDIR
#define RAPIDCOPY_ERRNO_EINVAL 		RAPIDCOPY_ERRNO_BASE + EINVAL
#define RAPIDCOPY_ERRNO_ENFILE 		RAPIDCOPY_ERRNO_BASE + ENFILE
#define RAPIDCOPY_ERRNO_EMFILE 		RAPIDCOPY_ERRNO_BASE + EMFILE
#define RAPIDCOPY_ERRNO_EFBIG 		RAPIDCOPY_ERRNO_BASE + EFBIG
#define RAPIDCOPY_ERRNO_ENOSPC 		RAPIDCOPY_ERRNO_BASE + ENOSPC
#define RAPIDCOPY_ERRNO_EROFS 		RAPIDCOPY_ERRNO_BASE + EROFS
#define RAPIDCOPY_ERRNO_EMLINK 		RAPIDCOPY_ERRNO_BASE + EMLINK
//blank math
#define RAPIDCOPY_ERRNO_EAGAIN 		RAPIDCOPY_ERRNO_BASE + EAGAIN
//blank ipc/network
#define RAPIDCOPY_ERRNO_ENOTSUP 	RAPIDCOPY_ERRNO_BASE + ENOTSUP
#define RAPIDCOPY_ERRNO_ENETDOWN 	RAPIDCOPY_ERRNO_BASE + ENETDOWN
#define RAPIDCOPY_ERRNO_ENETUNREACH RAPIDCOPY_ERRNO_BASE + ENETUNREACH
#define RAPIDCOPY_ERRNO_ENETRESET 	RAPIDCOPY_ERRNO_BASE + ENETRESET
#define RAPIDCOPY_ERRNO_ECONNABORTED RAPIDCOPY_ERRNO_BASE + ECONNABORTED
#define RAPIDCOPY_ERRNO_ECONNRESET	RAPIDCOPY_ERRNO_BASE + ECONNRESET
#define RAPIDCOPY_ERRNO_ENOBUFS		RAPIDCOPY_ERRNO_BASE + ENOBUFS
#define RAPIDCOPY_ERRNO_ETIMEDOUT	RAPIDCOPY_ERRNO_BASE + ETIMEDOUT
//blank network
#define RAPIDCOPY_ERRNO_ELOOP 		RAPIDCOPY_ERRNO_BASE + ELOOP
#define RAPIDCOPY_ERRNO_ENAMETOOLONG RAPIDCOPY_ERRNO_BASE + ENAMETOOLONG
//blank
#define RAPIDCOPY_ERRNO_EDQUOT 		 RAPIDCOPY_ERRNO_BASE + EDQUOT
//blank nfs

#define RAPIDCOPY_ERRNO_ENOSYS 		 RAPIDCOPY_ERRNO_BASE + ENOSYS
//blank
//#define RAPIDCOPY_ERRNO_EDEVERR 	    RAPIDCOPY_ERRNO_BASE + EDEVERR
//#define RAPIDCOPY_ERRNO_EOVERFLOW 	  RAPIDCOPY_ERRNO_BASE + EOVERFLOW
//blankmann
#define RAPIDCOPY_ERRNO_ENOATTR 	 RAPIDCOPY_ERRNO_BASE + ENOATTR
//blank
#define RAPIDCOPY_ERRNO_EOPNOTSUPP 	 RAPIDCOPY_ERRNO_BASE + EOPNOTSUPP


//5xxxx is error counter message ID
#define RAPIDCOPY_COUNTER_BASE            50000
#define RAPIDCOPY_COUNTER_XATTR_ENOTSUP   RAPIDCOPY_COUNTER_BASE
#define RAPIDCOPY_COUNTER_ACL_EOPNOTSUPP  RAPIDCOPY_COUNTER_BASE + 1
#define RAPIDCOPY_COUNTER_UTIMES_EAGAIN   RAPIDCOPY_COUNTER_BASE + 2
#define RAPIDCOPY_COUNTER_XATTR_ENOTSUP_EA RAPIDCOPY_COUNTER_BASE + 3

// sentinel
#define IDS_SENTINEL 				   0xffffffff


