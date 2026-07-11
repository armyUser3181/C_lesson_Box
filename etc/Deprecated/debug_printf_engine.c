/* static int debug_printf_engine(char* ch) {
    switch( debug_context.engine.line ) {
        default:
        if( strchr("-+0 #", *ch) == NULL ) {

        } else { 
            
            debug_context.engine.line = __LINE__; break; } case __LINE__:
        if( '0' <= *ch && *ch <= '9' ) {

            break;
        } else { 
            debug_context.engine.line = __LINE__;  } case __LINE__:
        if( '.' != *ch ) {

        } else {
            debug_context.engine.line = __LINE__; break; } case __LINE__:
       if( '0' <= *ch && *ch <= '9' ) {

            break;
        } else { 
            debug_context.engine.line = __LINE__;  } case __LINE__:
        if( *ch == 'h' || *ch == 'z' ) {
            debug_context.engine.line = __LINE__; break; case __LINE__:
        } else
        if( *ch == 'l' ) {
            debug_context.engine.line = __LINE__; break; case __LINE__:
            if( *ch == 'l') {
                debug_context.engine.line = __LINE__; break; case __LINE__:
            }
        }
        if( strchr("diufeEgGcsoxXp", *ch) == NULL ) {
            if( *ch == '%' ) {
                debug_context.engine.line = 0;
                return 2; // print %
            }
        } else {

            return 1; // print start
        }

        //debug_context.engine.line = __LINE__; break; case __LINE__:
        //debug_context.engine.line = __LINE__; break; case __LINE__:
        //debug_context.engine.line = __LINE__; break; case __LINE__:
    }
    return 0; // no print
} */