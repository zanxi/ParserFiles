#pragma once
#include ".\stdwin.h"
#include ".\Response.h"

class Report
{
	concurrency::concurrent_queue<Response> responses;

public:
	void Add(Response resp)
	{
		responses.push(resp);
	}


};