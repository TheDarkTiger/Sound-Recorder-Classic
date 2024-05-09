/*
 Sound Recorder Classic
 
 A recreation of Windows 98/XP sound recorder
 Mostly for nostalgic and learning purpose, use at your own risks!
*/

#include <stdio.h>
#include <stdlib.h>
#include <iup.h>
#include "iupdraw.h"

float global_tmpWaveformIndex = 0.0f;


/**************************************************************************//**
 * Placeholder callback
 * 
 * @param [in] self   Handle
 * 
 * @return Default IUP value
 *****************************************************************************/
int placeholder_callback( Ihandle *self )
{
	printf( "Placeholder callback\n" );
	return IUP_DEFAULT;
}


/**************************************************************************//**
 * Menu file exit callback
 * 
 * @param [in] self   Menu file handle
 * 
 * @return Termination signal
 *****************************************************************************/
int mnu_file_exit_cb( Ihandle *self )
{
	// Exits the main loop
	return IUP_CLOSE;
}


/**************************************************************************//**
 * Canvas calback
 * 
 * @param [in] ih   Canvas handle
 * 
 * @return IUP error
 *****************************************************************************/
static int cnv_wavform_cb( Ihandle *ih )
{
	int error = IUP_CLOSE;
	
	if( ih != NULL )
	{
		IupDrawBegin( ih );
		IupSetAttributes( ih, "DRAWCOLOR=\"128 255 0\"" );
		IupDrawLine( ih, 0,18, 112,18 );
		
		int x = 112.0f * global_tmpWaveformIndex;
		IupDrawLine( ih, x,0, x,35 );
		IupDrawEnd( ih );
		
		error = IUP_DEFAULT;
	}else{
		error = IUP_CLOSE;
	}
	
	return error;
}


/**************************************************************************//**
 * Canvas calback
 * 
 * @param [in] ih   Slider handle
 * @param [in] a    Slider value
 * 
 * @return IUP error
 *****************************************************************************/
int val_position_cb( Ihandle *ih, double a )
{
	int error = IUP_CLOSE;
	
	if( ih != NULL )
	{
		char* tmp = IupGetAttribute( IupGetHandle( "val_position" ), "VALUE" );
		sscanf( tmp, "%lf", &a );
		global_tmpWaveformIndex = a;
		IupUpdate( IupGetHandle( "cnv_wavform" ) );
		
		char tmpstr[40];
		sprintf( tmpstr, "TITLE=\"Position:\n%4.2f Sec.\"", a );
		IupSetAttributes( IupGetHandle( "lbl_position" ), tmpstr );
		
		error = IUP_DEFAULT;
	}else{
		error = IUP_CLOSE;
	}
	
	return error;
}


// Main
int main( int argc, char** argv )
{
	IupOpen( &argc, &argv );
	
	IupImageLibOpen();
	
	// Try to load the GUI from the external file
	char *error = NULL;
	error = IupLoad( "res/main.led" );
	if( error )
	{
		printf( "%s\n", error );
		return 1 ;
	}
	
	
	// Registers callbacks
	
	// Menu 'File'
	IupSetCallback( IupGetHandle( "mnu_file_new" ), "ACTION", (Icallback) placeholder_callback );
	IupSetCallback( IupGetHandle( "mnu_file_open" ), "ACTION", (Icallback) placeholder_callback );
	IupSetCallback( IupGetHandle( "mnu_file_save" ), "ACTION", (Icallback) placeholder_callback );
	IupSetCallback( IupGetHandle( "mnu_file_saveAs" ), "ACTION", (Icallback) placeholder_callback );
	IupSetCallback( IupGetHandle( "mnu_file_revert" ), "ACTION", (Icallback) placeholder_callback );
	IupSetCallback( IupGetHandle( "mnu_file_properties" ), "ACTION", (Icallback) placeholder_callback );
	IupSetCallback( IupGetHandle( "mnu_file_exit" ), "ACTION", (Icallback) mnu_file_exit_cb );
	
	// Menu 'Edit'
	IupSetCallback( IupGetHandle( "mnu_edit_copy" ), "ACTION", (Icallback) placeholder_callback );
	IupSetCallback( IupGetHandle( "mnu_edit_pasteInsert" ), "ACTION", (Icallback) placeholder_callback );
	IupSetCallback( IupGetHandle( "mnu_edit_pasteMix" ), "ACTION", (Icallback) placeholder_callback );
	IupSetCallback( IupGetHandle( "mnu_edit_insertFile" ), "ACTION", (Icallback) placeholder_callback );
	IupSetCallback( IupGetHandle( "mnu_edit_mixWithFile" ), "ACTION", (Icallback) placeholder_callback );
	IupSetCallback( IupGetHandle( "mnu_edit_deleteBeforeCurrentPos" ), "ACTION", (Icallback) placeholder_callback );
	IupSetCallback( IupGetHandle( "mnu_edit_deleteAfterCurrentPos" ), "ACTION", (Icallback) placeholder_callback );
	IupSetCallback( IupGetHandle( "mnu_edit_audioProperties" ), "ACTION", (Icallback) placeholder_callback );
	
	// Menu 'Effect'
	IupSetCallback( IupGetHandle( "mnu_effect_increaseVolume" ), "ACTION", (Icallback) placeholder_callback );
	IupSetCallback( IupGetHandle( "mnu_effect_decreaseVolume" ), "ACTION", (Icallback) placeholder_callback );
	IupSetCallback( IupGetHandle( "mnu_effect_increaseSpeed" ), "ACTION", (Icallback) placeholder_callback );
	IupSetCallback( IupGetHandle( "mnu_effect_decreaseSpeed" ), "ACTION", (Icallback) placeholder_callback );
	IupSetCallback( IupGetHandle( "mnu_effect_addEcho" ), "ACTION", (Icallback) placeholder_callback );
	IupSetCallback( IupGetHandle( "mnu_effect_reverse" ), "ACTION", (Icallback) placeholder_callback );
	
	// Menu 'Help'
	IupSetCallback( IupGetHandle( "mnu_help_helpTopics" ), "ACTION", (Icallback) placeholder_callback );
	IupSetCallback( IupGetHandle( "mnu_help_aboutSRC" ), "ACTION", (Icallback) placeholder_callback );
	
	// slider
	IupSetCallback( IupGetHandle( "cnv_wavform" ), "ACTION", (Icallback) cnv_wavform_cb );
	IupUpdate( IupGetHandle( "cnv_wavform" ) );
	IupSetCallback( IupGetHandle( "val_position" ), "VALUECHANGED_CB", (Icallback) val_position_cb );
	
	
	// Get the main window handle and run the GUI
	Ihandle *dlg = IupGetHandle( "dlg" );
	
	if( dlg != NULL )
	{
		IupShowXY( dlg, IUP_CENTER, IUP_CENTER );
		
		IupMainLoop();
		
		IupClose();
		return EXIT_SUCCESS;
	}else{
		return 2;
	}
}