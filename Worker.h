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
			StructInfoFile sf;
			cv.try_pop(sf);
			Work work(sf);
			work.Save();			
		};
	};
	
public:
	
	Worker(){  	}

	void SetListFile(concurrency::concurrent_queue<StructInfoFile> _cv)		
	{
		//for(const auto& e: _cv)
		//cv = _cv;
	}

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
