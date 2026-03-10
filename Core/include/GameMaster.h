#ifndef GAMEMASTER_H
#define GAMEMASTER_H

namespace Core {

	class GameMaster
	{
	public:
		bool isRunning();

	private:
		bool m_isRunning{ false };
	};

}

#endif