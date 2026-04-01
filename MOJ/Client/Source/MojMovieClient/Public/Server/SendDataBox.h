// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Protocols.h"
#include "Containers/Queue.h"

/**
 * 
 */
class MOJMOVIECLIENT_API SendDataBox
{
private:
	TQueue<PACKET> dataQueue;
public:
	SendDataBox();
	~SendDataBox();

	inline bool Data_Enqueue(PACKET data) { return dataQueue.Enqueue(data); }

	inline bool Data_DeQueue(PACKET& data) { return dataQueue.Dequeue(data); }

	inline void ClearQueue() { dataQueue.Empty(); }

private:
	static SendDataBox* Instance;

public:
	static SendDataBox* GetInst()
	{
		if (Instance == NULL)
		{
			Instance = new SendDataBox();
		}
		return Instance;
	}
};
