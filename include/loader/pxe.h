#ifndef __PXE_H__
#define __PXE_H__

#include <loader/types.h>

struct PXE_ENVPLUS {
	uint8_t         Signature[6];        /* "PXENV+" */
	uint16_t	Version;             /* Version, must be >= 0x201 */
	uint8_t		Length;              /* Length in bytes */
	uint8_t		Checksum;            /* Checksum */
	uint32_t	RMEntry;             /* Realmode entry point */
	uint32_t	PMOffset;            /* Do not use */
	uint16_t	PMSelector;          /* Do not use */
	uint16_t	StackSeg;            /* Stack segment address */
	uint16_t	StackSize;           /* Stack segment size in bytes */
	uint16_t	BC_CodeSeg;          /* BC code segment address */
	uint16_t	BC_CodeSize;         /* BC code segment size */
	uint16_t	BC_DataSeg;          /* BC data segment address */
	uint16_t	BC_DataSize;         /* BC data segment size */
	uint16_t	UNDIDataSeg;         /* UNDI data segment address */
	uint16_t	UNDIDataSize;        /* UNDI data segment size */
	uint16_t	UNDICodeSeg;         /* UNDI code segment address */
	uint16_t	UNDICodeSize;        /* UNDI code segment size */
	uint16_t	PXEPtr;              /* Realmode segment to !PXE structure */
} __attribute__((packed));

struct PXE_BANGPXE {
	uint8_t         Signature[4];        /* '!PXE' */
	uint8_t		StructLength;        /* Length in bytes */
	uint8_t		StructCksum;         /* Checksum */
	uint8_t		StructRev;           /* Revision (0) */
	uint8_t		_Reserved1;          /* 0 */
	uint32_t	UNDIROMID;           /* UNDI ROM ID structure address */
	uint32_t	BASEROMID;           /* BaseROM ID structure address */
	uint32_t	EntryPointSP;        /* PXE API entry point (real mode) */
	uint32_t	EntryPointESP;       /* PXE API entry point (protected mode) */
	uint32_t	StatusCallout;       /* DHCP/TFTP callout procedure */
	uint8_t		_Reserved2;          /* 0 */
	uint8_t		SegDescCnt;          /* Number of descriptors needed */
	uint32_t	FirstSelector;       /* First protected mode descriptor for PXE */
} __attribute__((packed));

#define PXENV_UNDI_SHUTDOWN 0x0005
#define PXENV_STOP_UNDI 0x0015

#define PXENV_TFTP_OPEN 0x0020
typedef struct s_PXENV_TFTP_OPEN {
	uint16_t	Status;
	uint32_t	ServerIPAddress;
	uint32_t	GatewayIPAddress;
	uint8_t		FileName[128];
	uint16_t	TFTPPort;
	uint16_t	PacketSize;
} __attribute__((packed)) t_PXENV_TFTP_OPEN;

#define PXENV_TFTP_CLOSE 0x0021
typedef struct s_PXENV_TFTP_CLOSE {
	uint16_t	Status;
} __attribute__((packed)) t_PXENV_TFTP_CLOSE;

#define PXENV_TFTP_READ 0x0022
typedef struct s_PXENV_TFTP_READ {
	uint16_t	Status;
	uint16_t	PacketNumber;
	uint16_t	BufferSize;
	uint16_t	BufferOffset;
	uint16_t	BufferSegment;
} __attribute__((packed)) t_PXENV_TFTP_READ;

#define PXENV_UDP_OPEN 0x0030
typedef struct s_PXENV_UDP_OPEN {
	uint16_t	status;
	uint32_t	src_ip;
} __attribute__((packed)) t_PXENV_UDP_OPEN;

#define PXENV_UDP_CLOSE 0x0031
typedef struct s_PXENV_UDP_CLOSE {
	uint16_t	status;
} __attribute__((packed)) t_PXENV_UDP_CLOSE;

#define PXENV_UDP_READ 0x0032
typedef struct s_PXENV_UDP_READ {
	uint16_t	status;
	uint32_t	src_ip;
	uint32_t	dst_ip;
	uint16_t	s_port;
	uint16_t	d_port;
	uint16_t	buffer_size;
	uint16_t	buffer_offset;
	uint16_t	buffer_segment;
} __attribute__((packed)) t_PXENV_UDP_READ;

#define PXENV_UDP_WRITE 0x0033
typedef struct s_PXENV_UDP_WRITE {
	uint16_t	status;
	uint32_t	ip;
	uint32_t	gw;
	uint16_t	src_port;
	uint16_t	dst_port;
	uint16_t	buffer_size;
	uint16_t	buffer_offset;
	uint16_t	buffer_segment;
} __attribute__((packed)) t_PXENV_UDP_WRITE;

#define PXENV_UNLOAD_STACK 0x0070
typedef struct s_PXENV_UNLOAD_STACK {
	uint16_t	Status;
	uint8_t		Reserved[10];
} __attribute__((packed)) t_PXENV_UNLOAD_STACK;

#define PXENV_GET_CACHED_INFO 0x0071
typedef struct s_PXENV_GET_CACHED_INFO {
	uint16_t	Status;
	uint16_t	PacketType;
#define PXENV_PACKET_TYPE_DHCP_DISCOVER 1
#define PXENV_PACKET_TYPE_DHCP_ACK      2
#define PXENV_PACKET_TYPE_CACHED_REPLY  3
	uint16_t	BufferSize;
	uint16_t	BufferOffset;
	uint16_t	BufferSegment;
	uint16_t	BufferLimit;
} __attribute__((packed)) t_PXENV_GET_CACHED_INFO;

#define PXENV_STOP_BASE 0x0076

#define PXENV_EXIT_SUCCESS 0x0
#define PXENV_EXIT_FAILURE 0x1

#define PXENV_STATUS_SUCCESS 0x0000
#define PXENV_STATUS_FAILURE 0x0001

struct BOOTP {
	uint8_t  opcode;                /* Message opcode */
#define BOOTP_REQ 1               /* Request */
#define BOOTP_REP 2               /* Response */
	uint8_t  hardware;              /* Hardware type */
	uint8_t  hardlen;               /* Hardware address length */
	uint8_t  gatehops;              /* Used for relaying */
	uint32_t ident;                 /* Transaction ID */
	uint16_t seconds;               /* Seconds elapsed since process */
	uint16_t flags;                 /* BOOTP/DHCP broadcast flags */
#define BOOTP_BCAST 0x8000
	uint32_t cip;                   /* Client IP addresss */
	uint32_t yip;                   /* 'Your' IP addresss */
	uint32_t sip;                   /* Server IP addresss */
	uint32_t gip;                   /* Gateway IP addresss */
	uint8_t  caddr[6];              /* Client hardware address */
	uint8_t  sname[64];             /* Server host name */
	uint8_t  bootfile[128];         /* Boot file name */
};

#endif /* __PXE_H__ */
