#ifndef QMI_WDS_SRVC_I_H
#define QMI_WDS_SRVC_I_H
/******************************************************************************
  @file    qmi_wds_srvc_i.h
  @brief   QMI message library WDS service definitions for "internal" use...
  not publicly available API's

  DESCRIPTION
  This file contains common, external header file definitions for QMI
  interface WDS "internal" functionality.

  INITIALIZATION AND SEQUENCING REQUIREMENTS
  qmi_wds_srvc_init_client() must be called to create one or more clients
  qmi_wds_srvc_release_client() must be called to delete each client when 
  finished.

  ---------------------------------------------------------------------------
  Copyright (c) 2007 - 2009 QUALCOMM Technologies Incorporated.
  All Rights Reserved. QUALCOMM Proprietary and Confidential.
  ---------------------------------------------------------------------------
******************************************************************************/

#define QMI_WDS_STD_MSG_SIZE                              QMI_MAX_STD_MSG_SIZE

#define QMI_WDS_CREATE_PROFILE_MSG_ID                     0x0027
#define QMI_WDS_GET_PROFILE_DATA_MSG_ID                   0x002B
#define QMI_WDS_MODIFY_PROFILE_MSG_ID                     0x0028
#define QMI_WDS_GET_PROFILE_LIST_MSG_ID                     0x002A

/* Profile list TLV */
#define QMI_WDS_PROFILE_LIST_TLV_ID                         0x01

#define QMI_WDS_GET_PROFILE_LIST_TECH_TYPE_TLV_ID           0x10

/*Extended error codes TLV IDs*/
#define QMI_WDS_EXTENDED_ERROR_CODE_TLV_ID                  0xE0


/* Profile related Request/response/indication TLV ID's */
#define QMI_WDS_PROFILE_ID_TLV_ID                                           0x01
#define QMI_WDS_PROFILE_IS_PERSISTENT_TLV_ID                                0x8F

/* UMTS related profile param TLV IDs */
#define QMI_WDS_UMTS_PROFILE_NAME_TLV_ID                                    0x10
#define QMI_WDS_UMTS_PROFILE_PDP_TYPE_TLV_ID                                0x11
#define QMI_WDS_UMTS_PROFILE_APN_NAME_TLV_ID                                0x14
#define QMI_WDS_UMTS_PROFILE_PRIM_DNS_TLV_ID                                0x15
#define QMI_WDS_UMTS_PROFILE_SEC_DNS_TLV_ID                                 0x16
#define QMI_WDS_UMTS_PROFILE_UMTS_REQ_QOS_TLV_ID                            0x17
#define QMI_WDS_UMTS_PROFILE_UMTS_MIN_QOS_TLV_ID                            0x18
#define QMI_WDS_UMTS_PROFILE_GPRS_REQ_QOS_TLV_ID                            0x19
#define QMI_WDS_UMTS_PROFILE_GPRS_MIN_QOS_TLV_ID                            0x1A
#define QMI_WDS_UMTS_PROFILE_USERNAME_TLV_ID                                0x1B
#define QMI_WDS_UMTS_PROFILE_PASSWORD_TLV_ID                                0x1C
#define QMI_WDS_UMTS_PROFILE_AUTH_PREF_TLV_ID                               0x1D
#define QMI_WDS_UMTS_PROFILE_IPV4_ADDR_PREF_TLV_ID                          0x1E
#define QMI_WDS_UMTS_PROFILE_PCSCF_ADDR_VIA_PCO_TLV_ID                      0x1F
#define QMI_WDS_UMTS_PROFILE_HEADER_COMPRESSION_TLV_ID                      0x12
#define QMI_WDS_UMTS_PROFILE_DATA_COMPRESSION_TLV_ID                        0x13
#define QMI_WDS_UMTS_PROFILE_PDP_ACCESS_CONTROL_TLV_ID                      0x20
#define QMI_WDS_UMTS_PROFILE_PCSCF_VIA_DHCP_TLV_ID                          0x21
#define QMI_WDS_UMTS_PROFILE_IM_CN_FLAG_TLV_ID                              0x22
#define QMI_WDS_UMTS_PROFILE_TFT_FILTER_ID_1_TLV_ID                         0x23
#define QMI_WDS_UMTS_PROFILE_TFT_FILTER_ID_2_TLV_ID                         0x24
#define QMI_WDS_UMTS_PROFILE_PDP_CONTEXT_NUMBER_TLV_ID                      0x25
#define QMI_WDS_UMTS_PROFILE_PDP_CONTEXT_SECONDARY_TLV_ID                   0x26
#define QMI_WDS_UMTS_PROFILE_PDP_PRIMARY_ID_TLV_ID                          0x27
#define QMI_WDS_UMTS_PROFILE_IPV6_ADDR_PREF_TLV_ID                          0x28
#define QMI_WDS_UMTS_PROFILE_UMTS_REQ_QOS_EXT_TLV_ID                        0x29
#define QMI_WDS_UMTS_PROFILE_UMTS_MIN_QOS_EXT_TLV_ID                        0x2A
#define QMI_WDS_UMTS_PROFILE_PRIMARY_DNS_IPV6_ADDR_PREF_TLV_ID              0x2B
#define QMI_WDS_UMTS_PROFILE_SECONDARY_DNS_IPV6_ADDR_PREF_TLV_ID            0x2C

/* CDMA related profile param TLV IDs */
#define QMI_WDS_CDMA_PROFILE_DNS_SERVER_PREF_TLV_ID                         0x90
#define QMI_WDS_CDMA_PROFILE_PPP_SESSION_CLOSE_TIMER_DO_TLV_ID              0x91
#define QMI_WDS_CDMA_PROFILE_PPP_SESSION_CLOSE_TIMER_1X_TLV_ID              0x92
#define QMI_WDS_CDMA_PROFILE_ALLOW_LINGER_TLV_ID                            0x93
#define QMI_WDS_CDMA_PROFILE_LCP_ACK_TIMEOUT_TLV_ID                         0x94
#define QMI_WDS_CDMA_PROFILE_IPCP_ACK_TIMEOUT_TLV_ID                        0x95
#define QMI_WDS_CDMA_PROFILE_AUTH_TIMEOUT_TLV_ID                            0x96
#define QMI_WDS_CDMA_PROFILE_LCP_CONFIG_RETRY_RECOUNT_TLV_ID                0x97
#define QMI_WDS_CDMA_PROFILE_IPCP_CONFIG_RETRY_RECOUNT_TLV_ID               0x98
#define QMI_WDS_CDMA_PROFILE_AUTH_RETRY_RECOUNT_TLV_ID                      0x99
#define QMI_WDS_CDMA_PROFILE_AUTH_PROTOCOL_TLV_ID                           0x9A
#define QMI_WDS_CDMA_PROFILE_USERNAME_TLV_ID                                0x9B
#define QMI_WDS_CDMA_PROFILE_PASSWORD_TLV_ID                                0x9C
#define QMI_WDS_CDMA_PROFILE_DATA_RATE_TLV_ID                               0x9D
#define QMI_WDS_CDMA_PROFILE_APP_TYPE_TLV_ID                                0x9E
#define QMI_WDS_CDMA_PROFILE_DATA_MODE_TLV_ID                               0x9F
#define QMI_WDS_CDMA_PROFILE_APP_PRIORITY_TLV_ID                            0xA0
#define QMI_WDS_CDMA_PROFILE_APN_STRING_TLV_ID                              0xA1
#define QMI_WDS_CDMA_PROFILE_PDN_TYPE_TLV_ID                                0xA2
#define QMI_WDS_CDMA_PROFILE_IS_PCSCF_ADDR_NEEDED_TLV_ID                    0xA3
#define QMI_WDS_CDMA_PROFILE_PRIM_V4_DNS_ADDR_TLV_ID                        0xA4
#define QMI_WDS_CDMA_PROFILE_SEC_V4_DNS_ADDR_TLV_ID                         0xA5
#define QMI_WDS_CDMA_PROFILE_PRIM_V6_DNS_ADDR_TLV_ID                        0xA6
#define QMI_WDS_CDMA_PROFILE_SEC_V6_DNS_ADDR_TLV_ID                         0xA7
#define QMI_WDS_CDMA_PROFILE_RAT_TYPE_TLV_ID                                0xA8


#endif
