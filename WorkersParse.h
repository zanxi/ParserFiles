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
			if (numtasks % numWorkers==0)i = 0;
			numtasks++;
		}

		while (true) 
		{				
			int cols = 0;
			for (int i = 0; i < numWorkers; i++)
			{				
				if (workers[i]->EmptyTask())cols++;
			}
			if (cols == numtasks)break;
			std::chrono::milliseconds(5000);
			cout << "Continue parse files .........\n";						
		}

		std::chrono::milliseconds(500);
		cout << "End finished parse files\n";

		workers[i]->Stop();
		workers[i]->Join();
		delete workers[i];
		
	};

	~WorkersParse()
	{
		for (int i = 0; i < numWorkers; i++)
		{			
			
		}
	}
};