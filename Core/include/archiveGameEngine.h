#ifdef EXCLUDE_THIS_FILE

#pragma once

#include "EngineAction.h"
#include "EventManager.h"
#include "GameMaster.h"
#include "IRenderer.h"
#include "Menu.h"

#include <memory>
#include <string>

namespace archiveGameEngine {

	enum class EngineState
	{
		UNINITIALIZED,
		INITIALIZED,
		DISPLAY_RULES,
		RUNNING,
		PAUSED,
		RESUMED,
		QUITTED,
		TERMINATED
	};

	// Helper function to convert EngineState enum to string
	inline std::string enginestate_to_string(EngineState state)
	{
		switch (state)
		{
		case EngineState::UNINITIALIZED: return "UNINITIALIZED";
		case EngineState::INITIALIZED: return "INITIALIZED";
		case EngineState::DISPLAY_RULES: return "DISPLAY_RULES";
		case EngineState::RUNNING: return "RUNNING";
		case EngineState::PAUSED: return "PAUSED";
		case EngineState::RESUMED: return "RESUMED";
		case EngineState::QUITTED: return "QUITTED";
		case EngineState::TERMINATED: return "TERMINATED";
		}
	}

	class GameEngine
	{
	public:
		GameEngine(EventManager* em, IRenderer* re)
			: m_eventManager{ em }
			, m_renderer{ re }
		{}

		void init(Game::GameType gameType);
		void run();

	private: // todo ensure right order destruction because renderer owns terminal and evenmanager uses it
		EngineState m_state { EngineState::UNINITIALIZED };
		EngineState m_prevState { EngineState:: UNINITIALIZED };
		
		GameMaster m_gameMaster;
		EventManager* m_eventManager{ nullptr };
		IRenderer* m_renderer{ nullptr };
		Menu m_menu;
		
		bool isGameOver();

		void handleOnUninitializedAction(EngineAction action);
		void handleOnInitializedAction(EngineAction action);
		void handleOnDisplayRulesAction(MenuAction action);
		void handleOnRunAction(EngineAction action);
		void handleOnPauseAction(EngineAction action);

		void handleOnMenuAction(MenuAction action);
		void handleOnEngineAction(EngineAction action);
		template<typename T>
		void handleOnGameAction(const T& action);

		void processEvents();

		void render();

		void launch();
		void save();
		void reset();

		void onDisplayRules();
		void onRun();
		void onPause();
		void onResume();
		void onQuit();
		void onTerminate();
	};

}

// struct TerminalRenderer : IRenderer {
//     void render(const RenderDataVariant& data) override {
//         std::visit([this](auto&& d) {
//             using T = std::decay_t<decltype(d)>;
//             if constexpr (std::is_same_v<T, SpriteData>)
//                 renderSprite(d);
//             else if constexpr (std::is_same_v<T, TextData>)
//                 renderText(d);
//         }, data);
//     }

//     void renderSprite(const SpriteData& s) { /* render to terminal */ }
//     void renderText(const TextData& t) { /* render to terminal */ }
// };

#endif
