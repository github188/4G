/******************************************************************************
  @file    qmi_i.h
  @brief   Common, internal QMI definitions

  DESCRIPTION
  This file contains common, internal to QMI header file definitions.

  INITIALIZATION AND SEQUENCING REQUIREMENTS
  N/A

  ---------------------------------------------------------------------------
  Copyright (c) 2007-2012 QUALCOMM Technologies Incorporated.
  All Rights Reserved. QUALCOMM Proprietary and Confidential.
  ---------------------------------------------------------------------------
******************************************************************************/

#ifndef QMI_I_H
#define QMI_I_H

#include <linux/module.h>
#include <linux/byteorder/generic.h>
#include "qmi_port_defs.h"

//to support big/little edage alignment
//add by qiao 2013.05.02
#define LC_BIGEDAGE_SUPPORT_DEF

#define QMI_CONN_ID_IS_VALID(id) (((int)QMI_MAX_CONN_IDS > (int)id) && (0 <= (int)id))

#define QMI_CONN_ID_IS_PROXY(id) ( ( id == QMI_CONN_ID_PROXY ) ? 1 : 0 )

/* Define for an invalid file descriptor */
#define LINUX_QMI_INVALID_FD               (-1)

#define QMI_QMUX_INVALID_QMUX_CLIENT_ID    (-1)
#define QMI_QMUX_INVALID_QMI_CLIENT_ID     (0xFF)
#define QMI_QMUX_BROADCAST_QMI_CLIENT_ID   QMI_QMUX_INVALID_QMI_CLIENT_ID

typedef int qmi_qmux_clnt_id_t;
#define QMI_QMUX_CLIENT_ID_SIZE  (sizeof(qmi_qmux_clnt_id_t))

//#include "qmi_platform.h"
#include "qmi.h"

#ifdef QMI_MSGLIB_MULTI_PD /* QMI_MSGLIB_MULTI_PD, if on, defined in qmi_platform.h */
#include "qmi_platform_qmux_if.h"
#endif

/* Typedef of internally used client ID type */
typedef unsigned char qmi_client_id_type;

#ifndef QMI_MSGLIB_MULTI_PD
#define QMI_QMUX_IF_PLATFORM_SPECIFIC_HDR_SIZE 0
#endif


#define LOG_FUNC_ENTER() QMI_DEBUG_MSG_1  ("Entering function %s\n",__FUNCTION__)
#define LOG_FUNC_EXIT() QMI_DEBUG_MSG_1  ("Exiting function %s\n",__FUNCTION__)


/* QMUX I/F message ID/structure definitions.  See IMPORTANT note below
** about adding system indication message ID's */

typedef enum
{
  QMI_QMUX_IF_FIRST_MSG_ID,
  QMI_QMUX_IF_QMI_MSG_ID = QMI_QMUX_IF_FIRST_MSG_ID,
  QMI_QMUX_IF_ALLOC_QMI_CLIENT_ID_MSG_ID,
  QMI_QMUX_IF_RELEASE_QMI_CLIENT_ID_MSG_ID,
  QMI_QMUX_IF_SET_DATA_FORMAT_MSG_ID,
  QMI_QMUX_IF_ADD_QMUX_CLIENT_MSG_ID,
  QMI_QMUX_IF_DELETE_QMUX_CLIENT_MSG_ID,
  QMI_QMUX_IF_REG_PWR_SAVE_MODE_MSG_ID,
  QMI_QMUX_IF_CONFIG_PWR_SAVE_SETTINGS_MSG_ID,
  QMI_QMUX_IF_SET_PWR_STATE_MSG_ID,
  QMI_QMUX_IF_GET_PWR_STATE_MSG_ID,
  QMI_QMUX_IF_GET_VERSION_INFO,
  QMI_QMUX_IF_SEND_RAW_QMI_CTL_MSG_ID,

  /* IMPORTANT!!! Put ALL system indications in this block of ID's (between
  ** QMI_QMUX_IF_FIRST_SYS_IND_MSG_ID and QMI_QMUX_IF_LAST_SYS_IND_MSG_ID (move
  ** definition of QMI_QMUX_IF_LAST_SYS_IND_MSG_ID if necessary
  */
  QMI_QMUX_IF_PWR_STATE_IND_MSG_ID,
  QMI_QMUX_IF_FIRST_SYS_IND_MSG_ID = QMI_QMUX_IF_PWR_STATE_IND_MSG_ID,
  QMI_QMUX_IF_SYNC_IND_MSG_ID,
  QMI_QMUX_IF_MODEM_OUT_OF_SERVICE_MSG_ID,
  QMI_QMUX_IF_MODEM_IN_SERVICE_MSG_ID,
  QMI_QMUX_IF_LAST_SYS_IND_MSG_ID = QMI_QMUX_IF_MODEM_IN_SERVICE_MSG_ID,

  QMI_QMUX_IF_MAX_NUM_MSGS /* Must stay last in enum */
} qmi_qmux_if_msg_id_type;



typedef struct
{
  qmi_qmux_if_msg_id_type    msg_id;
  qmi_qmux_clnt_id_t         qmux_client_id;
  unsigned long              qmux_txn_id;
  int                        sys_err_code;
  int                        qmi_err_code;
  qmi_connection_id_type     qmi_conn_id;
  qmi_service_id_type        qmi_service_id;
//  qmi_client_id_type         qmi_client_id;
  unsigned char              control_flags;
} qmi_qmux_if_msg_hdr_type;


/* QMI message header sizes */
#define QMI_QMUX_HDR_SIZE         (6)
#define QMI_SRVC_STD_TXN_HDR_SIZE (3)
#define QMI_SRVC_STD_MSG_HDR_SIZE (4)

/* The service header will be the bigger of the QMUX header and the
** SRVC <-> QMUX message header.  The two will never be needed at
** the same time.  Current assumption is that the qmi_qmux_if_msg_hdr_type
** will always be bigger than the size of a QMUX header (6 bytes).
*/
#define QMI_QMUX_IF_HDR_SIZE  (sizeof (qmi_qmux_if_msg_hdr_type))

/* Size of header that goes on each message buffer */
#define QMI_MAX_HDR_SIZE (QMI_QMUX_IF_PLATFORM_SPECIFIC_HDR_SIZE + \
                          QMI_QMUX_IF_HDR_SIZE + \
                          QMI_SRVC_STD_TXN_HDR_SIZE + \
                          QMI_SRVC_STD_MSG_HDR_SIZE)


/* Min size of a message (header info) between SRVC <-> QMUX */
#define QMI_QMUX_IF_MSG_HDR_SIZE  (QMI_QMUX_IF_HDR_SIZE + QMI_QMUX_IF_PLATFORM_SPECIFIC_HDR_SIZE)

#define QMI_TLV_HDR_SIZE         (3)

/* Total message size numbers */
#define QMI_MAX_STD_MSG_SIZE         (512)
#define QMI_MAX_MSG_SIZE             (2048)

/* Some utility macros to help adjust pointers and counts to allow
** room for headers
*/
#define QMI_SRVC_PDU_PTR(ptr) (unsigned char *)((unsigned char *)ptr + QMI_MAX_HDR_SIZE)
#define QMI_SRVC_PDU_SIZE(initial_size) (initial_size - QMI_MAX_HDR_SIZE)
#define QMI_CLIENT_TLV_PTR(ptr) QMI_SRVC_PDU_PTR(ptr)

/* Synchronous message default timeouts (in seconds) */
#define QMI_SYNC_MSG_DEFAULT_TIMEOUT  5
#define QMI_SYNC_MSG_EXTENDED_TIMEOUT 30

/* Turn off debug message macros if QMI_DEBUG isn't defined */
#ifndef QMI_DEBUG

#undef QMI_DEBUG_MSG_0
#undef QMI_DEBUG_MSG_1
#undef QMI_DEBUG_MSG_2
#undef QMI_DEBUG_MSG_3
#undef QMI_DEBUG_MSG_4

#define QMI_DEBUG_MSG_0(str)
#define QMI_DEBUG_MSG_1(str,arg1)
#define QMI_DEBUG_MSG_2(str,arg1,arg2)
#define QMI_DEBUG_MSG_3(str,arg1,arg2,arg3)
#define QMI_DEBUG_MSG_4(str,arg1,arg2,arg3,arg4)

#endif /* ifndef QMI_DEBUG */


/* Utility macros for reading/writing various quantities from buffers.  Note
** that buffer pointers are changed by calling these.  Also note that these
** will only work for little-endian processors.
*/
#define SIZE_8_BIT_VAL   (1)
#define SIZE_16_BIT_VAL  (2)
#define SIZE_32_BIT_VAL  (4)

#ifndef LC_BIGEDAGE_SUPPORT_DEF
#define WRITE_8_BIT_VAL(buf,val) \
 do { unsigned char *b_ptr = buf; \
      unsigned long val_copy = (unsigned long) val; \
      unsigned char *v_ptr = (unsigned char *) &val_copy; \
      int unlikely_cntr; \
      for (unlikely_cntr=0; unlikely_cntr<SIZE_8_BIT_VAL; unlikely_cntr++) {*b_ptr++ = *v_ptr++;} \
      buf = b_ptr; \
    } while (0)

#define WRITE_16_BIT_VAL(buf,val) \
do { unsigned char *b_ptr = buf; \
      unsigned long val_copy = (unsigned long) val; \
      unsigned char *v_ptr = (unsigned char *) &val_copy; \
      int unlikely_cntr; \
      for (unlikely_cntr=0; unlikely_cntr<SIZE_16_BIT_VAL; unlikely_cntr++) {*b_ptr++ = *v_ptr++;} \
      buf = b_ptr; \
    } while (0)

#define WRITE_32_BIT_VAL(buf,val) \
do { unsigned char *b_ptr = buf; \
      unsigned long val_copy = (unsigned long) val; \
      unsigned char *v_ptr = (unsigned char *) &val_copy; \
      int unlikely_cntr; \
      for (unlikely_cntr=0; unlikely_cntr<SIZE_32_BIT_VAL; unlikely_cntr++) {*b_ptr++ = *v_ptr++;} \
      buf = b_ptr; \
    } while (0)


#define READ_8_BIT_VAL(buf,dest) \
do { unsigned char *b_ptr = buf; \
     unsigned char *d_ptr = (unsigned char *) &dest; \
     int unlikely_cntr; \
     dest = 0; \
     for (unlikely_cntr=0; unlikely_cntr<SIZE_8_BIT_VAL; unlikely_cntr++) {*d_ptr++ = *b_ptr++;} \
     buf = b_ptr; \
   } while (0)

#define READ_16_BIT_VAL(buf,dest) \
do { unsigned char *b_ptr = buf; \
     unsigned char *d_ptr = (unsigned char *) &dest; \
     int unlikely_cntr; \
     dest = 0; \
     for (unlikely_cntr=0; unlikely_cntr<SIZE_16_BIT_VAL; unlikely_cntr++) {*d_ptr++ = *b_ptr++;} \
     buf = b_ptr; \
   } while (0)

#define READ_32_BIT_VAL(buf,dest) \
do { unsigned char *b_ptr = buf; \
     unsigned char *d_ptr = (unsigned char *) &dest; \
     int unlikely_cntr; \
     dest = 0; \
     for (unlikely_cntr=0; unlikely_cntr<SIZE_32_BIT_VAL; unlikely_cntr++) {*d_ptr++ = *b_ptr++;} \
     buf = b_ptr; \
   } while (0)
#else
#define WRITE_8_BIT_VAL(buf,val) \
 do { unsigned char *b_ptr = buf; \
      unsigned char val_copy = val; \
      memcpy(buf,&val_copy,sizeof(unsigned char)); \
      b_ptr++; \
      buf = b_ptr; \
    } while (0)

#define WRITE_16_BIT_VAL(buf,val) \
do {  unsigned char *b_ptr = buf; \
      unsigned short val_copy = cpu_to_le16(val); \
      memcpy(buf,&val_copy,sizeof(unsigned short)); \
      b_ptr += 2; \
      buf = b_ptr; \
    } while (0)

#define WRITE_32_BIT_VAL(buf,val) \
do { unsigned char *b_ptr = buf; \
      unsigned long val_copy = cpu_to_le32(val); \
      memcpy(buf,&val_copy,sizeof(unsigned long)); \
      b_ptr += 4; \
      buf = b_ptr; \
    } while (0)


#define READ_8_BIT_VAL(buf,dest) \
do { unsigned char *d_ptr = (unsigned char *) buf; \
	dest = (( unsigned char)*buf); \
     d_ptr += 1; \
     buf = d_ptr; \
   } while (0)

#define READ_16_BIT_VAL(buf,dest) \
do { unsigned char *d_ptr = (unsigned char *) buf; \
	unsigned short tmp = 0; \
    memcpy(&tmp,buf,sizeof(unsigned short)); \
	dest = le16_to_cpu(tmp); \
     d_ptr += 2; \
     buf = d_ptr; \
   } while (0)

#define READ_32_BIT_VAL(buf,dest) \
do { unsigned char *d_ptr = (unsigned char *) buf; \
	unsigned long tmp = 0; \
    memcpy(&tmp,buf,sizeof(unsigned long)); \
	dest = le32_to_cpu(tmp); \
     d_ptr += 4; \
     buf = d_ptr; \
   } while (0)
#endif

/* Macro to declare and initialize variables used in
** creating an "envelope" TLV
*/
#define INIT_ENVELOPE_TLV_HDR(buf_ptr,buf_size) \
  unsigned char *tlv_hdr = buf_ptr; \
  int           tlv_length = 0; \
  buf_ptr += QMI_TLV_HDR_SIZE; \
  buf_size -= QMI_TLV_HDR_SIZE


/* Macro to set the envelope TLV type and length fields
** and add the header length to the tlv_length variable
*/
#define SET_ENVELOPE_TLV_HDR(tlv_msg_id) \
do {\
  WRITE_8_BIT_VAL (tlv_hdr,tlv_msg_id); \
  WRITE_16_BIT_VAL (tlv_hdr,tlv_length); \
  tlv_length += QMI_TLV_HDR_SIZE; \
} while (0)


/* Singly linked lists are used throughout the library.... Macroized
** the commonly used operations */

#define QMI_SLL_ADD(item,head) \
{\
  item->next = head; \
  head = item; \
}

#define QMI_SLL_FIND(item,prev,head,test) \
{\
  prev = NULL;\
  item = head;\
  while (item != NULL)\
  {\
    if test\
    {\
      break;\
    }\
    prev = item;\
    item = item->next;\
  }\
}

#define QMI_SLL_REMOVE(item,prev,head) \
{\
  if (item != NULL)\
  {\
    if (prev == NULL)\
    {\
      head = item->next;\
    }\
    else\
    {\
      prev->next = item->next;\
    }\
    item->next = NULL;\
  }\
}

#define QMI_SLL_FIND_AND_REMOVE(item,prev,head,test) \
  QMI_SLL_FIND(item,prev,head,test) \
  QMI_SLL_REMOVE(item,prev,head)


#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif


#endif /* QMI_I_H */

