#include <cstdlib> // for abs()
#include <assert.h>

#include "attack.h"
#include "board.h"
#include "colour.h"
#include "eval.h"
#include "material.h"
#include "move.h"
#include "option.hpp"
#include "pawn.h"
#include "piece.h"
#include "see.h"
#include "util.h"
#include "value.h"
#include "vector.h"

using namespace LIBHeisenKernel;
using namespace LIBHeisenKernel::engine;
using namespace HeisenOs::common;

namespace LIBHeisenKernel{
    namespace engine{
        #define THROUGH(piece) ((piece)==Empty)
        /**
         * @brief Define some constants here
        */
        const int DepthMax = 64;
        const int HeightMax = 256;

        /**
         * @brief Constants and variables
        */
        static /* const */ int PieceActivityWeight = 256; // 100%
        static /* const */ int KingSafetyWeight = 256; // 100%
        static /* const */ int PassedPawnWeight = 256; // 100%

        static const int KnightUnit = 4;
        static const int BishopUnit = 6;
        static const int RookUnit = 7;
        static const int QueenUnit = 13;

        static const int MobMove = 1;
        static const int MobAttack = 1;
        static const int MobDefense = 0;

        static const int KnightMobOpening = 4;
        static const int KnightMobEndgame = 4;
        static const int BishopMobOpening = 5;
        static const int BishopMobEndgame = 5;
        static const int RookMobOpening = 2;
        static const int RookMobEndgame = 4;
        static const int QueenMobOpening = 1;
        static const int QueenMobEndgame = 2;
        static const int KingMobOpening = 0;
        static const int KingMobEndgame = 0;

        static const bool UseOpenFile = true;
        static const int RookSemiOpenFileOpening = 10;
        static const int RookSemiOpenFileEndgame = 10;
        static const int RookOpenFileOpening = 20;
        static const int RookOpenFileEndgame = 20;
        static const int RookSemiKingFileOpening = 10;
        static const int RookKingFileOpening = 20;

        static const bool UseKingAttack = true;
        static const int KingAttackOpening = 20;

        static const bool UseShelter = true;
        static const int ShelterOpening = 256; // 100%
        static const bool UseStorm = true;
        static const int StormOpening = 10;

        static const int Rook7thOpening = 20;
        static const int Rook7thEndgame = 40;
        static const int Queen7thOpening = 10;
        static const int Queen7thEndgame = 20;

        static const int TrappedBishop = 100;

        static const int BlockedBishop = 50;
        static const int BlockedRook = 50;

        static const int PassedOpeningMin = 10;
        static const int PassedOpeningMax = 70;
        static const int PassedEndgameMin = 20;
        static const int PassedEndgameMax = 140;

        static const int UnstoppablePasser = 800;
        static const int FreePasser = 60;

        static const int AttackerDistance = 5;
        static const int DefenderDistance = 20;

        static const int KingAttackWeight[16] = {
             0, 0, 128, 192, 224, 240, 248, 252, 254, 255, 256, 256 ,256, 256, 256, 256,
        };
        
        /**
         * @brief Variables
        */
        static int MobUnit[ColourNb][PieceNb];

        static int KingAttackUnit[PieceNb];

        static void eval_draw          (const board_t * board, const material_info_t * mat_info, const pawn_info_t * pawn_info, int mul[2]);

static void eval_piece         (const board_t * board, const material_info_t * mat_info, const pawn_info_t * pawn_info, int * opening, int * endgame);
static void eval_king          (const board_t * board, const material_info_t * mat_info, int * opening, int * endgame);
static void eval_passer        (const board_t * board, const pawn_info_t * pawn_info, int * opening, int * endgame);
static void eval_pattern       (const board_t * board, int * opening, int * endgame);

static bool unstoppable_passer (const board_t * board, int pawn, int colour);
static bool king_passer        (const board_t * board, int pawn, int colour);
static bool free_passer        (const board_t * board, int pawn, int colour);

static int  pawn_att_dist      (int pawn, int king, int colour);
static int  pawn_def_dist      (int pawn, int king, int colour);

static void draw_init_list     (int list[], const board_t * board, int pawn_colour);

static bool draw_kpkq          (const int list[], int turn);
static bool draw_kpkr          (const int list[], int turn);
static bool draw_kpkb          (const int list[], int turn);
static bool draw_kpkn          (const int list[], int turn);

static bool draw_knpk          (const int list[], int turn);

static bool draw_krpkr         (const int list[], int turn);
static bool draw_kbpkb         (const int list[], int turn);

static int  shelter_square     (const board_t * board, int square, int colour);
static int  shelter_file       (const board_t * board, int file, int rank, int colour);

static int  storm_file         (const board_t * board, int file, int colour);

static bool bishop_can_attack  (const board_t * board, int to, int colour);


        void eval_init(){
            int Color;
            int piece;

            PieceActivityWeight = (option_get_int("Piece Activity") * 256 + 50) / 100;
            KingSafetyWeight    = (option_get_int("King Safety")    * 256 + 50) / 100;
            PassedPawnWeight    = (option_get_int("Passed Pawns")   * 256 + 50) / 100;

            for (Color = 0;Color < ColorNb;Color++){
                for (piece = 0;piece < PieceNb;piece++){
                    MobUnit[Color][piece] = 0;
                }
            }

               MobUnit[White][Empty] = MobMove;

                MobUnit[White][BP] = MobAttack;
                MobUnit[White][BN] = MobAttack;
                MobUnit[White][BB] = MobAttack;
                MobUnit[White][BR] = MobAttack;
                MobUnit[White][BQ] = MobAttack;
                MobUnit[White][BK] = MobAttack;

                MobUnit[White][WP] = MobDefense;
                MobUnit[White][WN] = MobDefense;
                MobUnit[White][WB] = MobDefense;
                MobUnit[White][WR] = MobDefense;
                MobUnit[White][WQ] = MobDefense;
                MobUnit[White][WK] = MobDefense;

                MobUnit[Black][Empty] = MobMove;

                MobUnit[Black][WP] = MobAttack;
                MobUnit[Black][WN] = MobAttack;
                MobUnit[Black][WB] = MobAttack;
                MobUnit[Black][WR] = MobAttack;
                MobUnit[Black][WQ] = MobAttack;
                MobUnit[Black][WK] = MobAttack;

                MobUnit[Black][BP] = MobDefense;
                MobUnit[Black][BN] = MobDefense;
                MobUnit[Black][BB] = MobDefense;
                MobUnit[Black][BR] = MobDefense;
                MobUnit[Black][BQ] = MobDefense;
                MobUnit[Black][BK] = MobDefense;

                for (piece = 0;piece < PieceNb;piece++){
                    KingAttackUnit[piece] = 0;
                }
                KingAttackUnit[WN] = 1;
                KingAttackUnit[WB] = 1;
                KingAttackUnit[WR] = 2;
                KingAttackUnit[WQ] = 4;

                KingAttackUnit[BN] = 1;
                KingAttackUnit[BB] = 1;
                KingAttackUnit[BR] = 2;
                KingAttackUnit[BQ] = 4;
        }
        int eval(const board_t* board){
            int opening,endgame;
            material_info_t mat_info[1];
            pawn_info_t pawn_info[1];
            int mul[ColourNb];
            int phase;
            int eval;
            int wb, bb;


            assert(board != NULL);
            assert(board_is_legal(board));
            assert(!board_is_check(board));

            opening = 0;
            endgame = 0;

            // material_get_info(mat_info,board);
        }

}}