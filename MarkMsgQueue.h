#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

class CMarkMsgQueue
{
public:
	enum class Mark
	{
		Open,
		Close,
		Path,
		Done
	};

	struct MarkMsg
	{
		Mark Type;
		int Row;
		int Col;
	};

	void Push(const MarkMsg& Msg)
	{
		{
			std::scoped_lock lk(Mutex);
			Queue.push(Msg);
		}
		Cv.notify_one();
	}

	void WaitPop(MarkMsg& Msg)
	{
		std::unique_lock lk(Mutex);
		Cv.wait(lk, [&] { return !Queue.empty(); });
		Msg = Queue.front();
		Queue.pop();
	}

private:
	std::queue<MarkMsg> Queue;
	std::mutex Mutex;
	std::condition_variable Cv;

};

