#pragma once

#include "Core/Containers/Board/Board.h"
#include "Core/Containers/Board/Cell.h"
#include "App/Game/Tetris/Tetromino.h"
#include "App/Game/Tetris/TetrominoBlock.h"

#include <cstddef>
#include <memory>
#include <variant>

namespace App::Game::Tetris {

    class TetrisBoard
    {
    public:
        TetrisBoard(size_t rows = 40, size_t cols = 10)
        : m_board{ rows, cols }
        {}

        void init();

        Core::Container::Board board() const;

        void setActiveTetromino(Tetromino tetromino);
        bool requestTetromino() const;

        void translateLeftActive();
        void translateRightActive();
        void softDropActive();
        void rotateActiveClockwise();
        void rotateActiveLeft();
        void rotateActiveRight();
        void hardDropActive();
        void holdActive();

    private:
        Core::Container::Board m_board;
        std::optional<Tetromino> m_activeTetromino;
    };

}
