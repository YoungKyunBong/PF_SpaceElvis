// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Protocols.h"
#include "Containers/Queue.h"

/**
 * 
 */
class MOJMOVIECLIENT_API RecvDataBox
{
private:
	TQueue<PACKET*, EQueueMode::Mpsc> dataQueue;

public:
	RecvDataBox();
	~RecvDataBox();

	bool Data_Enqueue(const PACKET& data) { return dataQueue.Enqueue(new PACKET(data)); }
	bool Data_Dequeue(PACKET*& outData) { return dataQueue.Dequeue(outData); }
	bool CheckEmpty() const { return dataQueue.IsEmpty(); }
	void ClearQueue() { PACKET* tmp = nullptr; while (dataQueue.Dequeue(tmp)) { delete tmp; } }

private:
	static RecvDataBox* Instance;

public:
	static RecvDataBox* GetInst()
	{
		if (Instance == NULL)
		{
			Instance = new RecvDataBox();
		}
		return Instance;
	}
};
