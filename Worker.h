#pragma once
#include ".\stdwin.h"
#include ".\StructInfoFile.h"
#include ".\Work.h"
//#include ".\Response.h"
//#include ".\Report.h"

class Worker
{	
public:
	std::unique_ptr<std::thread> th_;
	std::mutex m_lock;
private:
	concurrency::concurrent_queue<StructInfoFile> cv;		
	bool ready = true;
	
	void Run()
	{
		while (ready)
		{
			if (cv.empty())
			{
				std::chrono::milliseconds(500);
				continue;
			}
			m_lock.lock();
			StructInfoFile sf;
			cv.try_pop(sf);
			Work work(sf);
			work.Save();				
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			m_lock.unlock();
			
		};
	};
	
public:
	
	Worker(){  	}
		
	void AddTask(StructInfoFile sf)
	{
		cv.push(sf);
	}

	bool EmptyTask()
	{
		return cv.empty();
	}

	void Start()
	{
		th_.reset(new std::thread([this]() { Run(); }));
	}

	void Join() {
		if (th_ && th_->joinable()) {
			th_->join();
		}
	}

	void Stop()
	{
		ready = false;
	}
};
