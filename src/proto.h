
#include <stdint-gcc.h>
#include "user.h"

enum {
    Ok = 0,
    UsernameNotExist = 1,
    PasswordError = 2,
    UserExist = 3,
    ParamError = -2,
};

// login

typedef struct {
    char Username[32];
    char Password[32];
    int ReqId;
} LoginReq_t;

typedef struct {
    LoginReq_t req;
    int Result;
} LoginResp_t;


//user
typedef struct {
    char Username[32];
    char Password[32];
    int ReqId;
} CreateUserReq_t;

typedef struct {
    CreateUserReq_t req;
    int result;
} FindUserResp_t;

// group

typedef struct {
    char GroupName[32];
    int ReqId;
} GroupCreateReq_t;

typedef struct {
    GroupCreateReq_t req;
    int Result;
} GroupCreateResp_t;

typedef struct {
    char GroupName[32];
    int ReqId;
} GroupJoinReq_t;

typedef struct {
    GroupJoinReq_t Req;
    int Result;
} GroupJoinResp_t;


// chat
typedef struct {
    char DataLen;
    char *Data;
    int Sender;
    int Receiver;
    int GroupId;
} Msg_t;
typedef struct {
    int ReqId;
    int msgLen;
    Msg_t Msg;
} SendMsgReq_t;

typedef struct {
    int ReqId;
    int MsgId;
    int Result;
} SendMsgResp_t;


typedef struct {
    int ReqId;
    int FromIdx;
    int Count;
    int Sender;
    int Receiver;
    int Group;
} PullMsgReq_t;

typedef struct {
    int ReqId;
    int index;
    Msg_t Msg;
} PullMsgResp_t;

