#pragma once
#include ".\stdwin.h"
#include ".\Work.h"
#include ".\Worker.h"

class WorkersParse
{
	const int numWorkers=7;
	vector<Worker*> workers;

public:
	WorkersParse(concurrency::concurrent_vector<StructInfoFile> cv)
	{
		for (int i = 0; i < numWorkers; i++)
		{
			Worker *work = new Worker();
			work->Start();
			workers.push_back(work);			
		}

		int numtasks = 0;
		int i = 0;
		for (const auto& e: cv)
		{			
			workers[i]->AddTask(e);
			i++;
			if (numtasks > numWorkers)i = 0;
			numtasks++;
		}
	};

	~WorkersParse()
	{
		for (int i = 0; i < numWorkers; i++)
		{			
			workers[i]->Join();
			workers[i]->Stop();			
			delete workers[i];
		}
	}
};