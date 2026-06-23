#pragma once

#include "Core/Types/Index2D.h"
#include "Core/Containers/Board/CellVisual.h"
#include "Core/Containers/Deck/Deck.h"
#include "Core/Lib/Matrix/Matrix.h"
#include "App/Game/Tetris/TetrominoBlock.h"
#include "App/Game/Tetris/TetrominoType.h"

#include "Core/Utils/Logger.h"


namespace App::Game::Tetris {

    class Tetromino
    {
    public:
        Tetromino() = delete;

        Tetromino(TetrominoType type, const Lib::Matrix::Matrix<int>& shape, const Core::Type::Index2D& topLeft)
        : m_type{ type }
        , m_shape{ shape }
        , m_spawnLocation { topLeft }
        {}

        TetrominoType getType() const { return m_type; }
        const std::vector<TetrominoBlock>& getBlocks() const { return m_blocks; }

        const Lib::Matrix::Matrix<int>& getShape() const { return m_shape; }
        void setShape(const Lib::Matrix::Matrix<int>& shape) { m_shape = shape; }

        void init();
        
        void setSpawnLocation(const Core::Type::Index2D& topLeft);

        void setColor(GfxUtils::Color blockColor);

        void translateLeft();
        void translateRight();

        void rotateLeft();
        void rotateRight();

        void animate();

    protected:
        bool m_isLockedDown{ false };

        TetrominoType m_type;
        std::vector<TetrominoBlock> m_blocks;
        Lib::Matrix::Matrix<int> m_shape;
        Core::Type::Index2D m_spawnLocation; // top left

        int m_v_speed;
        int m_v_gravity;
    };


    inline Tetromino createTetromino(TetrominoType type, size_t spawnRow)
    {
        switch (type)
        {
        case TetrominoType::I:
        {
            auto shape = Lib::Matrix::Matrix<int>(4, 4);
            shape(1, 0) = 1;
            shape(1, 1) = 2;
            shape(1, 2) = 3;
            shape(1, 3) = 4;

            auto tetromino = Tetromino(type, shape, { spawnRow, 3 });
            tetromino.init();
            tetromino.setColor(GfxUtils::Color::CYAN);
            return tetromino;
        }
        case TetrominoType::J:
        {
            auto shape = Lib::Matrix::Matrix<int>(3, 3);
            shape(0, 0) = 1;
            shape(1, 0) = 2;
            shape(1, 1) = 3;
            shape(1, 2) = 4;

            auto tetromino = Tetromino(type, shape, { spawnRow, 3 });
            tetromino.init();
            tetromino.setColor(GfxUtils::Color::BLUE);
            return tetromino;
        }
        case TetrominoType::L:
        {
            auto shape = Lib::Matrix::Matrix<int>(3, 3);
            shape(0, 2) = 1;
            shape(1, 0) = 2;
            shape(1, 1) = 3;
            shape(1, 2) = 4;

            auto tetromino = Tetromino(type, shape, { spawnRow, 3 });
            tetromino.init();
            tetromino.setColor(GfxUtils::Color::BRIGHT_ORANGE);
            return tetromino;
        }
        case TetrominoType::O:
        {
            auto shape = Lib::Matrix::Matrix<int>(2, 2);
            shape(0, 0) = 1;
            shape(0, 1) = 2;
            shape(1, 0) = 3;
            shape(1, 1) = 4;
            
            auto tetromino = Tetromino(type, shape, { spawnRow, 4 });
            tetromino.init();
            tetromino.setColor(GfxUtils::Color::YELLOW);
            return tetromino;
        }
        case TetrominoType::S:
        {
            auto shape = Lib::Matrix::Matrix<int>(3, 3);
            shape(0, 1) = 1;
            shape(0, 2) = 2;
            shape(1, 0) = 3;
            shape(1, 1) = 4;
            
            auto tetromino = Tetromino(type, shape, { spawnRow, 3 });
            tetromino.init();
            tetromino.setColor(GfxUtils::Color::GREEN);
            return tetromino;
        }
        case TetrominoType::T:
        {
            auto shape = Lib::Matrix::Matrix<int>(3, 3);
            shape(0, 1) = 1;
            shape(1, 0) = 2;
            shape(1, 1) = 3;
            shape(1, 2) = 4;
            
            auto tetromino = Tetromino(type, shape, { spawnRow, 3 });
            tetromino.init();
            tetromino.setColor(GfxUtils::Color::RED);
            return tetromino;
        }
        case TetrominoType::Z:
        {
            auto shape = Lib::Matrix::Matrix<int>(3, 3);
            shape(0, 0) = 1;
            shape(0, 1) = 2;
            shape(1, 1) = 3;
            shape(1, 2) = 4;
            
            auto tetromino = Tetromino(type, shape, { spawnRow, 3 });
            tetromino.init();
            tetromino.setColor(GfxUtils::Color::MAGENTA);
            return tetromino;
        }
        default:
            throw std::runtime_error("[Tetromino] createTetromino() Wrong Tetromino type");
        }
    }

    inline Core::Container::Deck<Tetromino> createTetrominoDeck(size_t spawnRow)
    {
		LOG_DEBUG("[Tetromino] Creating Tetromino deck, set up with spawnRow= %d", spawnRow);

        Core::Container::Deck<Tetromino> deck;
        for (auto type : App::Game::Tetris::allTetrominoTypes)
        {
            deck.add(createTetromino(type, spawnRow));
        }
        deck.init();
        return deck;
    }
}