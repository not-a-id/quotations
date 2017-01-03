//  Copyright (c) 2016-2017 The SWP Authors. All rights reserved.
//  Created on: 2016年12月30日 Author: kerry

#ifndef SWP_NET_COMM_HEAD_H_
#define SWP_NET_COMM_HEAD_H_

#include <list>
#include <string>

#include "basic/basictypes.h"

#define PASSWORD_SIZE   8 + 1
#define MAC_SIZE        16 + 1
#define TOKEN_SIZE      32 + 1
#define SIGNATURE_SIZE  16 ＋ 1
#define STORAGE_INFO_SIZE 32 + 1
#define IP_FORGEN_SIZE     31 + 1
#define UA_FORGEN_SIZE   251 + 1
#define HADRINFO_SIZE   16 + 1
#define URL_SIZE        256 + 1
#define NAME_SIZE       32 + 1
#define KEY_SIZE        32 + 1

enum PRS {
  NOZIP_AND_NOENCRYPT = 0,
  ZIP_AND_NOENCRYPT = 1,
  NOZIP_AND_ENCRYPT = 2,
  ZIP_AND_ENCRYPT = 3
};

enum operatorcode {
  HEART_PACKET = 0x64
};

//  packet_length 长度为原始数据长度
struct PacketHead {
  int16 packet_length;
  int8 is_zip_encrypt;
  int8 type;
  int16 signature;
  int16 operate_code;
  int16 data_length;
  int32 timestamp;
  int64 session_id;
  int32 reserved;
};

#define PACKET_HEAD_LENGTH (sizeof(int16) * 4 + sizeof(int8) * 2 + \
    sizeof(int32) * 2 + sizeof(int64))

#endif /*SWP_NET_COMM_HEAD_H_*/
