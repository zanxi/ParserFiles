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
		for (int i = 0; i < numWorkers; i++) // запуск парсеров
		{
			Worker *work = new Worker();
			work->Start();
			workers.push_back(work);			
		}

		//int numtasks = 0;
		int i = 1;
		for (const auto& e: cv) // раздача заданий
		{			
			workers[i%numWorkers]->AddTask(e);
			i++;
			//if (numtasks % numWorkers==0)i = 0;
			//numtasks++;
		}
		int cols = 0;
		//numtasks = cv.size();
		while (true)  // цикл проверки выполнения задач
		{				
			cols = 0;
			for (int i = 0; i < numWorkers; i++)
			{				
				if (workers[i]->EmptyTask())cols++;
			}
			if (cols == numWorkers)break;
			std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
			cout << "Continue parse files ......... \n";						
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		cout << "End finished parse files! tasks=" << cols << "\n";

		for (int i = 0; i < numWorkers; i++)
		{
			workers[i]->Stop();
			workers[i]->Join();
			delete workers[i];
		}
		
	};

	~WorkersParse()
	{
		for (int i = 0; i < numWorkers; i++)
		{			
			
		}
	}
};