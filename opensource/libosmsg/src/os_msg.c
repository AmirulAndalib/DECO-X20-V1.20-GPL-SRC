/*  Copyright(c) 2010-2011 Shenzhen TP-LINK Technologies Co.Ltd.
 *
 * file	os_msg.c
 * brief	Linux general IPC method. 
 *
 * author	Yang Xv
 * version	1.0.0
 * date	28Apr11
 *
 * history 	\arg 1.0.0, 28Apr11, Yang Xv, Create the file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <assert.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>


#include "os_msg.h"


/**************************************************************************************************/
/*                                           DEFINES                                              */
/**************************************************************************************************/

/* 
 * brief Different OS have different path prefix
 */
//#define OS_PATH_PREFIX "/var/run/"
#define OS_PATH_PREFIX "/var/tmp/"


/* 
 * brief Max path length, should smaller than sockaddr_un.sun_path length	
 */
#define MAX_PATH_LEN	64

/**************************************************************************************************/
/*                                           GLOBAL_FUNCTIONS                                     */
/**************************************************************************************************/

/* 
 * fn		int msg_init(CMSG_FD *pMsgFd)
 * brief	Create an endpoint for msg
 *	
 * param[out]	pMsgFd - return msg descriptor that has been create	
 *
 * return	-1 is returned if an error occurs, otherwise is 0
 *
 * note 	Need call msg_cleanup() when you no longer use this msg which is created by msg_init()
 */
int msg_init(CMSG_FD *pMsgFd)
{
	assert(pMsgFd != NULL);

	if (-1 == (pMsgFd->fd = socket(AF_LOCAL, SOCK_DGRAM, 0))) 	
	{		
		perror("socket");		
		return -1;	
	}
	
	/* set FD_CLOEXEC */
	if (-1 == fcntl(pMsgFd->fd, F_SETFD, 1))
	{
		perror("msg fcntl");
		close(pMsgFd->fd);
		return -1;
	}
	
	return 0;
}


/* 
 * fn		int msg_srvInit(CMSG_ID msgId, CMSG_FD *pMsgFd)
 * brief	Init an endpoint as a server and bind a name to this endpoint msg	
 *
 * param[in]	msgId - server name	
 * param[in]	pMsgFd - server endpoint msg fd
 *
 * return	-1 is returned if an error occurs, otherwise is 0	
 */
int msg_srvInit(CMSG_ID msgId, CMSG_FD *pMsgFd)
/* 本来应该是传入一个name，之后拼接成path，但是如果由开发者传入name，因为随意命名，可能会出现冲突
 * 因此这里直接传入ID，用ID做文件名
 */
{
	char path[MAX_PATH_LEN + 1] = {0};

	assert(pMsgFd != NULL);

	/* prepare domain path */
	snprintf(path, MAX_PATH_LEN, "%s%d", OS_PATH_PREFIX, msgId);
	DEBUG_PRINT("Server path is %s\n", path);
	unlink(path);
	
	/* bind socket to specify path */
	memset(&(pMsgFd->_localAddr), 0, sizeof(pMsgFd->_localAddr));
	pMsgFd->_localAddr.sun_family = AF_LOCAL;	
	strncpy(pMsgFd->_localAddr.sun_path, path, sizeof(pMsgFd->_localAddr.sun_path));	

	if (-1 == bind(pMsgFd->fd, (struct sockaddr *)(&(pMsgFd->_localAddr)), 
		SUN_LEN(&(pMsgFd->_localAddr))))
	{		
		perror("bind");		
		return -1;	
	}
	
	return 0;
}



/* 
 * fn		int msg_connSrv(CMSG_ID msgId, CMSG_FD *pMsgFd)
 * brief	Init an endpoint as a client and specify a server name	
 *
 * param[in]		msgId - server name that we want to connect	
 * param[in/out]	pMsgFd - client endpoint msg fd	
 *
 * return	-1 is returned if an error occurs, otherwise is 0
 */
int msg_connSrv(CMSG_ID msgId, CMSG_FD *pMsgFd)
{
	char path[MAX_PATH_LEN + 1] = {0};

	assert(pMsgFd != NULL);

	/* prepare domain path */
	snprintf(path, MAX_PATH_LEN, "%s%d", OS_PATH_PREFIX, msgId);
	DEBUG_PRINT("Client connect server path is %s\n", path);
	
	/* bind socket to specify path */
	memset(&(pMsgFd->_remoteAddr), 0, sizeof(pMsgFd->_remoteAddr));
	pMsgFd->_remoteAddr.sun_family = AF_LOCAL;	
	strncpy(pMsgFd->_remoteAddr.sun_path, path, sizeof(pMsgFd->_remoteAddr.sun_path));

	return 0;
}


/* 
 * fn		int msg_recv(const CMSG_FD *pMsgFd, CMSG_BUFF *pMsgBuff)
 * brief	Receive a message form a msg	
 *
 * param[in]	pMsgFd - msg fd that we want to receive message
 * param[out]	pMsgBuff - return recived message
 *
 * return	-1 is returned if an error occurs, otherwise is 0
 *
 * note		we will clear msg buffer before recv
 */
int msg_recv(const CMSG_FD *pMsgFd, CMSG_BUFF *pMsgBuff)
/* 这里使用_remoteAddr是为了后续可能使用msg_send的情况(msg_sendAndGetReplyWithTimeout()) */
{
	int len = sizeof(pMsgFd->_remoteAddr);
	
	assert((pMsgFd != NULL) && (pMsgBuff != NULL));

	memset(pMsgBuff, 0, MSG_SIZE);
	
	if (-1 == recvfrom(pMsgFd->fd, pMsgBuff, MSG_SIZE, 0,
			(struct sockaddr *)(&(pMsgFd->_remoteAddr)), (socklen_t *)&len))
	{
		perror("recvfrom");
		return -1;
	}

	return 0;
}


/* 
 * fn		int msg_send(const CMSG_FD *pMsgFd, const CMSG_BUFF *pMsgBuff)
 * brief	Send a message from a msg	
 *
 * param[in]	pMsgFd - msg fd that we want to send message	
 * param[in]	pMsgBuff - msg that we wnat to send
 *
 * return	-1 is returned if an error occurs, otherwise is 0
 *
 * note 	This function will while call sendto() if sendto() return ENOENT error
 */
int msg_send(const CMSG_FD *pMsgFd, const CMSG_BUFF *pMsgBuff)
/* 如果sendto()返回的是ENOENT，那么我们将继续调用sendto，直到成功或者返回其他错误为止
 * 主要目的是用来处理服务器还未启动，但是客户端已经启动的情况(主要是系统初始化的时候)
 * 这里有一种可能，就是这个域套接字的路径是存在的，但是服务器已经关闭，暂时不处理
 */
{
	int ret = 0;
	int flag = 0;
	
	assert((pMsgFd != NULL) && (pMsgBuff != NULL));
	
	do
	{
		ret = sendto(pMsgFd->fd, pMsgBuff, MSG_SIZE, flag, 
					(struct sockaddr *)(&(pMsgFd->_remoteAddr)), SUN_LEN(&(pMsgFd->_remoteAddr)));

		if ((-1 == ret) && (ENOENT == errno))
		{
			usleep(10000);
			perror("sendto");
			printf("pid %d send %d error\n", getpid(), pMsgBuff->type);
		}
	}while((-1 == ret) && (ENOENT == errno || EINTR == errno || EAGAIN == errno));

	if (-1 == ret)
	{
		perror("sendto");
		printf("pid %d send %d error, errno is %d\n", getpid(), pMsgBuff->type, errno);
		return -1;
	}
	
	return 0;
}


/* 
 * fn		int msg_cleanup(CMSG_FD *pMsgFd)
 * brief	Close a message fd
 * details	
 *
 * param[in]	pMsgFd - message fd that we want to close		
 *
 * return	-1 is returned if an error occurs, otherwise is 0		
 */
int msg_cleanup(CMSG_FD *pMsgFd)
{
	assert(pMsgFd != NULL);

	if (-1 == close(pMsgFd->fd))
	{
		perror("close");		
		return -1;		
	}

	/* TODO:
	 * 这里可以考虑增加删除域套接字的路径，不过由于服务器都是启动之后就不再退出，
	 * 因此暂时可以不考虑
	 */

	return 0;
}


/* 
 * fn		int msg_connCliAndSend(CMSG_ID msgId, CMSG_FD *pMsgFd, CMSG_BUFF *pMsgBuff)
 * brief	init a client msg and send msg to server which is specified by msgId	
 *
 * param[in]	msgId -	server ID that we want to send
 * param[in]	pMsgFd - message fd that we want to send
 * param[in]	pMsgBuff - msg that we wnat to send
 *
 * return	-1 is returned if an error occurs, otherwise is 0	
 */
int msg_connCliAndSend(CMSG_ID msgId, CMSG_FD *pMsgFd, CMSG_BUFF *pMsgBuff)
/* 将向server发送消息的四步操作封装起来，方便使用 */
{
	assert((pMsgFd != NULL) && (pMsgBuff != NULL));
	
	if (msg_init(pMsgFd) < 0)
	{
		printf("Init %d msg client error\n", msgId);
		return -1;
	}
	
	if (msg_connSrv(msgId, pMsgFd) < 0)
	{
		printf("Connect %d msg client error\n", msgId);
		msg_cleanup(pMsgFd);
		
		return -1;
	}

	msg_send(pMsgFd, pMsgBuff);

	msg_cleanup(pMsgFd);

	return 0;
}


/* 
 * fn		int msg_sendAndGetReply(CMSG_FD *pMsgFd, CMSG_BUFF *pMsgBuff)
 * brief	
 *
 * param[in]	pMsgFd - msg fd that we want to use
 * param[in/out]pMsgBuff - send msg and get reply
 * param[in]	timeSeconds - timeout in second
 *
 * return	-1 is returned if an error occurs, otherwise is 0	
 */
int msg_sendAndGetReplyWithTimeout(CMSG_FD *pMsgFd, CMSG_BUFF *pMsgBuff, int timeSeconds)
{
	int fd = 0;
	int ret = 0;
	struct sockaddr_un tmpAddr;
	char tempFile[]= "/var/tmp_XXXXXX";
	struct timeval tv;
	int errHappen = 0;

	assert((pMsgFd != NULL) && (pMsgBuff != NULL));

	if (-1 == (fd = mkstemp(tempFile)))
	{
		perror("mkstemp");
		return -1;
	}
	
	memset(&tmpAddr, 0, sizeof(tmpAddr));
	tmpAddr.sun_family = AF_LOCAL;
	strncpy(tmpAddr.sun_path, tempFile, sizeof(tmpAddr.sun_path));
	unlink(tmpAddr.sun_path);

	/* bind socket to a temp path for recive */
	if (-1 == bind(pMsgFd->fd, (struct sockaddr *)&tmpAddr, SUN_LEN(&tmpAddr))) 	
	{		
		perror("bind");		
		return -1;	
	}

	do
	{
		ret = sendto(pMsgFd->fd, pMsgBuff, MSG_SIZE, 0, 
				(struct sockaddr *)(&(pMsgFd->_remoteAddr)), SUN_LEN(&(pMsgFd->_remoteAddr)));

		if ((-1 == ret) && (ENOENT == errno))
		{
			usleep(10000);
			perror("sendto");
			printf("send %d error %d, %d\n", pMsgBuff->type, getpid(), ret);
		}
	}while((-1 == ret) && (ENOENT == errno));

	if (-1 == ret)
	{
		perror("sendto");
		errHappen = 1;
		goto error;		
	}

	/* set recvfrom timeout */
	tv.tv_sec = timeSeconds;
	tv.tv_usec = 0;
	
	if (-1 == setsockopt(pMsgFd->fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)))
	{
		perror("setsockopt");
		errHappen = 1;
		goto error;
	}

	if (-1 == recvfrom(pMsgFd->fd, pMsgBuff, MSG_SIZE, 0, NULL, NULL))
	{
		perror("recvfrom");
		errHappen = 1;
		goto error;
	}

error:

	/* set recvfrom no timeout */
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	
	if (-1 == setsockopt(pMsgFd->fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)))
	{
		perror("setsockopt");
	}

	/* delete file after get reply */
	close(fd);
	unlink(tmpAddr.sun_path);

	/* rebind method not found,so close and create socket again, ugly I know... */
	close(pMsgFd->fd);

	if (-1 == (pMsgFd->fd = socket(AF_LOCAL, SOCK_DGRAM, 0))) 	
	{		
		perror("new socket");		
		return -1;	
	}

	if (1 == errHappen)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

