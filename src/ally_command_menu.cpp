#include "ally_command_menu.h"
#include "game.h"
#include "creature.h"
#include "character.h"
#include "player.h"
#include "npc.h"
#include "monster.h"
#include "ui.h"

int draw_npc_window( npc &np, WINDOW *w_main, int top, int height, int width )
{
    int bottom = 
    for( int i = 0; i < TERMX; i++ ) {
        mvwputch( w_head, top - 1, i, c_white, LINE_OXOX );
    }
}

void command_allies( player &u )
{
    const int left = 0;
    const int right = TERMX;
    const int top = 3;
    const int bottom = TERMY;
    const int width = right - left;
    const int height = bottom - top;
    WINDOW *w_head = newwin( top, TERMX, 0, 0 );
    WINDOW *w_main = newwin( height, width, top, left );

    static const std::string header_message = _( "\
c to describe creatures, f to describe furniture, t to describe terrain, esc/enter to close." );
    mvwprintz( w_head, 0, 0, c_white, header_message.c_str() );

    // Set up line drawings
    for( int i = 0; i < TERMX; i++ ) {
        mvwputch( w_head, top - 1, i, c_white, LINE_OXOX );
    }

    wrefresh( w_head );

    input_context ctxt( "COMMAND_ALLIES" );
    ctxt.register_action( "UP", _( "Next ally" ) );
    ctxt.register_action( "DOWN", _( "Previous ally" ) );

    // @todo Less g->u centric
    std::vector<npc *> npc_allies = g->allies();
    // @todo Command dogs too

    if( npc_allies.empty() ) {
        static const std::string alone_msg = _( "You have no allies" );
        popup( alone_msg.c_str() );
        return;
    }

    size_t selected = 0;
    do {
        int cur_line = 0;
        for( npc *np : npc_allies ) {
            cur_line += draw_npc_window( *np, w_main, cur_line, height, width );
            if( cur_line >= height ) {
                break;
            }
        }

        const std::string action = ctxt.handle_input();
        if( action == "DOWN" ) {
            if( selected == npc_allies.size() - 1 ) {
                selected = 0;    // Wrap around
            } else {
                selected++;
            }
        } else if( action == "UP" ) {
            if( selected == 0 ) {
                selected = npc_allies.size() - 1;    // Wrap around
            } else {
                selected--;
            }
        } else if( action == "QUIT" ) {
            break;
        }
    } while( true );

    werase( w_head );
    werase( w_main );
    wrefresh( w_head );
    wrefresh( w_main );
    delwin( w_head );
    delwin( w_main );
}
