#ifndef __KST_SERVO_H__
#define __KST_SERVO_H__

/********************************************************************
 *                        Command Indicates
 * 1. Start reporting
 *********************************************************************/

typedef struct
{
    unsigned int ID;
    unsigned short Length;
    unsigned char Data[8];
} canopen_cmd_t;

#define CMD_START_REPORTING(nodeID) \
    {                               \
        .ID = (0U + nodeID),        \
        .Length = 2,                \
        .Data[0] = 0x01,            \
        .Data[1] = 0x00}

#define CMD_STOP_REPORTING(nodeID) \
    {                              \
        .ID = (0U + nodeID),       \
        .Length = 2,               \
        .Data[0] = 0x02,           \
        .Data[1] = 0x00}

#define CMD_SET_AUTO_REPOETING_FORMAT(nodeID, Low, High) \
    {                                                    \
        .ID = (0x580U + nodeID),                         \
        .Length = 4,                                     \
        .Data[0] = Low,                                  \
        .Data[1] = High,                                 \
        .Data[2] = 0,                                    \
        .Data[3] = 0}

#define CMD_SET_L0W_VOLTAGE_ALARM(nodeID) \
    {                                     \
        .ID = (0x380U + nodeID),          \
        .Length = 4,                      \
        .Data[0] = 0x0A,                  \
        .Data[1] = 0x02,                  \
        .Data[2] = 0,                     \
        .Data[3] = 0}

#define CMD_SET_AUTO_REPOETING_INTERVAL(nodeID, ms) \
    {                                               \
        .ID = (0x0600U + nodeID),                   \
        .Length = 8,                                \
        .Data[0] = 0x22,                            \
        .Data[1] = 0x00,                            \
        .Data[2] = 0x22,                            \
        .Data[3] = 0x00,                            \
        .Data[4] = ms,                              \
        .Data[5] = 0x00,                            \
        .Data[6] = 0x00,                            \
        .Data[7] = 0x00}

#define CMD_SET_BAUD_RATE(nodeID, baud) \
    {                                   \
        .ID = (0x0600U + nodeID),       \
        .Length = 8,                    \
        .Data[0] = 0x22,                \
        .Data[1] = 0x01,                \
        .Data[2] = 0x30,                \
        .Data[3] = 0x00,                \
        .Data[4] = baud,                \
        .Data[5] = 0x00,                \
        .Data[6] = 0x00,                \
        .Data[7] = 0x00}

// The default node number is 0x25.
#define CMD_SET_NODE_NUMBER(nodeID, nodeNumber) \
    {                                           \
        .ID = (0x0600U + nodeID),               \
        .Length = 8,                            \
        .Data[0] = 0x22,                        \
        .Data[1] = 0x00,                        \
        .Data[2] = 0x30,                        \
        .Data[3] = 0x00,                        \
        .Data[4] = nodeNumber,                  \
        .Data[5] = 0x00,                        \
        .Data[6] = 0x00,                        \
        .Data[7] = 0x00}

#define CMD_SET_POSITION(nodeID, low, high) \
    {                                       \
        .ID = (0x0600U + nodeID),           \
        .Length = 8,                        \
        .Data[0] = 0x22,                    \
        .Data[1] = 0x03,                    \
        .Data[2] = 0x60,                    \
        .Data[3] = 0x00,                    \
        .Data[4] = low,                     \
        .Data[5] = high,                    \
        .Data[6] = 0x00,                    \
        .Data[7] = 0x00}

#define CMD_SET_MIDPOINT(nodeID)  \
    {                             \
        .ID = (0x0600U + nodeID), \
        .Length = 8,              \
        .Data[0] = 0x22,          \
        .Data[1] = 0x09,          \
        .Data[2] = 0x30,          \
        .Data[3] = 0x00,          \
        .Data[4] = 0x00,          \
        .Data[5] = 0x00,          \
        .Data[6] = 0x00,          \
        .Data[7] = 0x00}

#define CMD_SET_SAVE_COMMAND(nodeID) \
    {                                \
        .ID = (0x0600U + nodeID),    \
        .Length = 8,                 \
        .Data[0] = 0x22,             \
        .Data[1] = 0x10,             \
        .Data[2] = 0x10,             \
        .Data[3] = 0x01,             \
        .Data[4] = 0x73,             \
        .Data[5] = 0x61,             \
        .Data[6] = 0x76,             \
        .Data[7] = 0x65}

#define CMD_READ_NODE_NUMBER(nodeID, X) \
    {                                   \
        .ID = (0x0600U + nodeID),       \
        .Length = 8,                    \
        .Data[0] = 0x40,                \
        .Data[1] = 0x00,                \
        .Data[2] = 0x30,                \
        .Data[3] = 0x00,                \
        .Data[4] = X,                   \
        .Data[5] = 0x00,                \
        .Data[6] = 0x00,                \
        .Data[7] = 0x00}

#define CMD_READ_LOCATION(nodeID) \
    {                             \
        .ID = (0x0600U + nodeID), \
        .Length = 8,              \
        .Data[0] = 0x40,          \
        .Data[1] = 0x02,          \
        .Data[2] = 0x60,          \
        .Data[3] = 0x00,          \
        .Data[4] = 0x00,          \
        .Data[5] = 0x00,          \
        .Data[6] = 0x00,          \
        .Data[7] = 0x00}

#define CMD_READ_STATUS(nodeID)   \
    {                             \
        .ID = (0x0600U + nodeID), \
        .Length = 8,              \
        .Data[0] = 0x40,          \
        .Data[1] = 0x05,          \
        .Data[2] = 0x60,          \
        .Data[3] = 0x00,          \
        .Data[4] = 0x00,          \
        .Data[5] = 0x00,          \
        .Data[6] = 0x00,          \
        .Data[7] = 0x00}

#define CMD_SET_FUNC_ENABLE_READ(nodeID) \
    {                                    \
        .ID = (0x0600U + nodeID),        \
        .Length = 8,                     \
        .Data[0] = 0x40,                 \
        .Data[1] = 0x0F,                 \
        .Data[2] = 0x30,                 \
        .Data[3] = 0x00,                 \
        .Data[4] = 0x00,                 \
        .Data[5] = 0x00,                 \
        .Data[6] = 0x00,                 \
        .Data[7] = 0x00}

#define CMD_SET_FUNC_ENABLE_WRITE(nodeID, X) \
    {                                        \
        .ID = (0x0600U + nodeID),            \
        .Length = 8,                         \
        .Data[0] = 0x22,                     \
        .Data[1] = 0x0F,                     \
        .Data[2] = 0x30,                     \
        .Data[3] = 0x00,                     \
        .Data[4] = X,                        \
        .Data[5] = 0x00,                     \
        .Data[6] = 0x00,                     \
        .Data[7] = 0x00}

#define CMD_READ_SOFTWARE_VERSION(nodeID) \
    {                                     \
        .ID = (0x0600U + nodeID),         \
        .Length = 8,                      \
        .Data[0] = 0x40,                  \
        .Data[1] = 0x0B,                  \
        .Data[2] = 0x10,                  \
        .Data[3] = 0x00,                  \
        .Data[4] = 0x00,                  \
        .Data[5] = 0x00,                  \
        .Data[6] = 0x00,                  \
        .Data[7] = 0x00}

		
void CAN_Servo_MainTask(void);

		
#endif //__KST_SERVO_H__
