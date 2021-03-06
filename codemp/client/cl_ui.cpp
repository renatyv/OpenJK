//Anything above this #include will be ignored by the compiler
#include "qcommon/exe_headers.h"

#include "client.h"
#include "cl_uiapi.h"

/*
====================
CL_ShutdownUI
====================
*/
void CL_ShutdownUI( qboolean delayFreeVM ) {
	Key_SetCatcher( Key_GetCatcher( ) & ~KEYCATCH_UI );

	if ( !cls.uiStarted )
		return;

	cls.uiStarted = qfalse;

	CL_UnbindUI();
}

/*
====================
CL_InitUI
====================
*/

void CL_InitUI( void ) {
	// load the dll or bytecode
	//OJKFIXME: pure servers
	CL_BindUI();

	// init for this gamestate
	//rww - changed to <= CA_ACTIVE, because that is the state when we did a vid_restart
	//ingame (was just < CA_ACTIVE before, resulting in ingame menus getting wiped and
	//not reloaded on vid restart from ingame menu)
	UIVM_Init( (qboolean)(cls.state >= CA_AUTHORIZING && cls.state <= CA_ACTIVE) );
}

/*
====================
UI_GameCommand

See if the current console command is claimed by the ui
====================
*/
qboolean UI_GameCommand( void ) {
	if ( !cls.uiStarted )
		return qfalse;

	return UIVM_ConsoleCommand( cls.realtime );
}
