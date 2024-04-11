#include "option.hpp"
#include "protocol.h"
#include <assert.h>
#include <types.h>


namespace LIBHeisenKernel{
    namespace engine{
        /**
         * @brief Structures defined here 
        */
        struct option_t{
            const char * var;
            bool declare;
            const char* init;
            const char * type;
            const char * extra;
            const char * val;
        };

        /**
         * @brief variables are defined here
        */

        static option_t Option[] = {

        { "Hash", true, "16", "spin", "min 4 max 1024", NULL },

        { "Ponder", true, "false", "check", "", NULL },

        { "OwnBook",  true, "true",           "check",  "", NULL },
        { "BookFile", true, "book_small.bin", "string", "", NULL },

        { "NullMove Pruning",       true, "Fail High", "combo", "var Always var Fail High var Never", NULL },
        { "NullMove Reduction",     true, "3",         "spin",  "min 1 max 3", NULL },
        { "Verification Search",    true, "Endgame",   "combo", "var Always var Endgame var Never", NULL },
        { "Verification Reduction", true, "5",         "spin",  "min 1 max 6", NULL },

        { "History Pruning",     true, "true", "check", "", NULL },
        { "History Threshold",   true, "60",   "spin",  "min 0 max 100", NULL },

        { "Futility Pruning", true, "false", "check", "", NULL },
        { "Futility Margin",  true, "100",   "spin",  "min 0 max 500", NULL },

        { "Delta Pruning", true, "false", "check", "", NULL },
        { "Delta Margin",  true, "50",    "spin",  "min 0 max 500", NULL },

        { "Quiescence Check Plies", true, "1", "spin", "min 0 max 2", NULL },

        { "Material",        true, "100", "spin", "min 0 max 400", NULL },
        { "Piece Activity",  true, "100", "spin", "min 0 max 400", NULL },
        { "King Safety",     true, "100", "spin", "min 0 max 400", NULL },
        { "Pawn Structure",  true, "100", "spin", "min 0 max 400", NULL },
        { "Passed Pawns",    true, "100", "spin", "min 0 max 400", NULL },

        { NULL, false, NULL, NULL, NULL, NULL, },
        };


        /**
         * @brief Defining some prototypes
        */

        static option_t * option_find(const char var[]);

        /**
         * @brief Implementing functions here
        */

        void option_init(){
            option_t *opt;

            for (opt = &Option[0];opt->var;opt++){
                option_set(opt->var, opt->init);
            }
        }

        void option_list(){
            option_t *opt;

            for (opt = &Option[0];opt->val != NULL;opt++){
                if (opt->declare){
         if (opt->extra != NULL && *opt->extra != '\0') {
            send("option name %s type %s default %s %s",opt->var,opt->type,opt->val,opt->extra);
         } else {
            send("option name %s type %s default %s",opt->var,opt->type,opt->val);
                }
            }
        }

        bool option_set(const char var[],const char val[]){
            option_t * opt;
            assert(var!= NULL);
            assert(val!= NULL);
            opt = option_find(var);
            if (opt == NULL){
                return false;
            }
            opt->val = val;
            return true;
        }

        const char* option_get(const char var[]){
            option_t * opt;

            ASSERT(var!=NULL);

            opt = option_find(var);
            if (opt == NULL) return NULL;

            return opt->val;
        }

    };
};