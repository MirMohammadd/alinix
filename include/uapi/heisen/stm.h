
/**
 * MIT License
 *
 * Copyright (c) 2024 Heisenberg
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * @author Heisenberg
 * @file smt.h

 */
#ifndef _UAPI_HESIEN_STM_H
#define _UAPI_HESIEN_STM_H
/*
SMT stands for Simultaneous Multi-Threading. It is a technology that allows multiple threads to run concurrently on a single processor core*/

#include <heisen/typing.h>


#define STP_MASTER_MASK 0xffff
#define STP_CHANNEL_MAX	0xffff

struct stp_policy_id{
    uint32_t size;
    uint16_t master;
    uint16_t channel;
    uint16_t width;
    /*padding*/
	uint16_t	__reserved_0;
	uint32_t		__reserved_1;
	char		id[];
};

#define STP_POLICY_ID_SET	_IOWR('%', 0, struct stp_policy_id)
#define STP_POLICY_ID_GET	_IOR('%', 1, struct stp_policy_id)
#define STP_SET_OPTIONS		_IOW('%', 2, __u64)


#endif // _UAPI_HESIEN_STM_H