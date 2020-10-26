﻿#pragma once

#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <WinSock2.h>

namespace inner_network
{
	namespace ReceivingManager
	{
		static std::thread receivingThread;

		void startReceivingLoop(SOCKET sListen);

		void initReceivingManager(int receivingPort);
	};
}
