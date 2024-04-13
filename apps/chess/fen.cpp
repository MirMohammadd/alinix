#include <cctype>
#include <cstdio>
#include <cstdlib>

#include "board.h"
#include "colour.h"
#include "fen.h"
#include "piece.h"
#include "square.h"
#include "util.h"
#include <assert.h>

using namespace LIBHeisenKernel;
using namespace LIBHeisenKernel::engine;
using namespace HeisenOs::common;
using namespace LIBHeisenKernel::Chess::engine;

namespace LIBHeisenKernel{
    namespace engine{
        const char * const StartFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
        static const bool Strict = false;


        /**
         * @brief Defining some functions
        */
        void board_from_fen(board_t*board,const char fen[]){

            int pos;
            int file,rank,sq;
            int c;
            int i,len;
            int piece;
            int pawn;

            assert(board != NULL);
            assert(board != NULL);

            board_clear(board);

            pos = 0;
            c = fen[pos];

            for(rank=Rank8;rank >= Rank1;rank--){
                for (file = FileA; file <= FileH;){

                    if (c >= '1' && c <= '8'){
                        len = c -'0';

                        for (i = 0;i < len;i++){
                            if (file > FileH) my_fatal("board_from_fen(): bad FEN (pos=%d)\n",pos);
                            board->square[SQUARE_MAKE(file,rank)] = Empty;
                            file++;
                        }
                    }else {
                        piece = piece_from_char(c);
                        if (piece == PieceNone256) my_fatal("board_from_fen(): bad FEN (pos=%d)\n",pos);

                        board->square[SQUARE_MAKE(file,rank)] = piece;
                        file++;
                    }

                    c = fen[++pos];
                }
                if (rank > Rank1){
                    if (c != '/') my_fatal("board_from_fen(): bad FEN (pos=%d)\n",pos);
                    c = fen[++pos];
                }

                // Activate color
                if (c != ' ') my_fatal("board_from_fen(): bad FEN (pos=%d)\n",pos);
                c = fen[++pos];
                switch(c){
                    case 'w':
                        board->turn = White;

                }
        }
    };
}};
