/*
 Sound Recorder Classic
 
 A recreation of Windows 98/XP sound recorder
 Mostly for nostalgic and learning purpose, use at your own risks!
*/

#include <stdio.h>
#include <stdlib.h>
#include <iup.h>
#include "iupdraw.h"

Ihandle* val_position;
Ihandle* cnv_wavform;
float global_tmpWaveformIndex = 0.0f;

int mnu_file_exit_cb( Ihandle* self )
{
	// Exits the main loop
	return IUP_CLOSE;
}

static int canvas_action( Ihandle* ih )
{
	IupDrawBegin( ih );
	IupSetAttribute( ih, "DRAWCOLOR", "128 255 0" );
	IupDrawLine( ih, 0,18, 112,18 );
	
	int x = 112.0f*global_tmpWaveformIndex;
	IupDrawLine( ih, x,0, x,35 );
	IupDrawEnd( ih );
	
	return IUP_DEFAULT;
}

int val_position_cb( Ihandle* self, double a )
{
	char* tmp = IupGetAttribute( val_position, "VALUE" );
	sscanf( tmp, "%lf", &a );
	global_tmpWaveformIndex = a;
	IupUpdate( cnv_wavform );
	return IUP_DEFAULT;
}

int main( int argc, char** argv )
{
	IupOpen( &argc, &argv );
	
	IupImageLibOpen();
	
	
	Ihandle* mnu;
	Ihandle* mnu_file_exit = IupItem( "Exit", NULL );
	mnu = IupMenu(
	IupSubmenu( "File", IupMenu(
	IupSetAttributes( IupItem( "New", NULL), NULL ),
	IupSetAttributes( IupItem( "Open...", NULL), NULL ),
	IupSetAttributes( IupItem( "Save", NULL), NULL ),
	IupSetAttributes( IupItem( "Save As...", NULL), NULL ),
	IupSetAttributes( IupItem( "Revert", NULL), "ACTIVE=NO" ),
	IupSetAttributes( IupItem( "Properties", NULL), NULL ),
	IupSeparator(),
	IupSetAttributes( mnu_file_exit, NULL ),
	NULL) ),
	IupSubmenu( "Edit", IupMenu(
	IupSetAttributes( IupItem( "Copy\tCtrl+C", NULL), NULL ),
	IupSetAttributes( IupItem( "Paste Insert\tCtrl+V", NULL), "ACTIVE=NO" ),
	IupSetAttributes( IupItem( "Paste Mix", NULL), "ACTIVE=NO" ),
	IupSeparator(),
	IupSetAttributes( IupItem( "Insert File...", NULL), NULL ),
	IupSetAttributes( IupItem( "Mix with File...", NULL), NULL ),
	IupSeparator(),
	IupSetAttributes( IupItem( "Delete Before Current Position", NULL), "ACTIVE=NO" ),
	IupSetAttributes( IupItem( "Delete After Current Position", NULL), "ACTIVE=NO" ),
	IupSeparator(),
	IupSetAttributes( IupItem( "Audio Properties", NULL), NULL ),
	NULL) ),
	IupSubmenu( "Effects", IupMenu(
	IupSetAttributes( IupItem( "Increase Volume (by 25%)", NULL), NULL ),
	IupSetAttributes( IupItem( "Decrease Volume", NULL), NULL ),
	IupSeparator(),
	IupSetAttributes( IupItem( "Increase Speed (by 100%)", NULL), NULL ),
	IupSetAttributes( IupItem( "Decrease Speed", NULL), NULL ),
	IupSeparator(),
	IupSetAttributes( IupItem( "Add Echo", NULL), NULL ),
	IupSetAttributes( IupItem( "Reverse", NULL), NULL ),
	NULL) ),
	IupSubmenu( "Help", IupMenu(
	IupSetAttributes( IupItem( "Help Topics", NULL), NULL ),
	IupSeparator(),
	IupSetAttributes( IupItem( "About Sound Recorder Classic", NULL), NULL ),
	NULL) ),
	NULL);
	IupSetHandle( "mnu", mnu );
	
	Ihandle* hboxInfos;
	Ihandle* frmPosition;
	Ihandle* lblPosition;
	lblPosition = IupLabel( "Position:\n0.00 Sec." );
	frmPosition = IupFrame( lblPosition );
	IupSetAttributes( frmPosition, "SUNKEN=YES, MARGIN=5x3, RASTERSIZE=60x37" );
	
	// Ihandle* cnv_wavform;
	cnv_wavform = IupCanvas(NULL);
	IupSetAttribute( cnv_wavform, "BGCOLOR", "0 0 0" );
	IupSetAttribute( cnv_wavform, "DRAWSIZE", "112 35" );
	IupSetAttribute( cnv_wavform, "EXPAND", "NO" );
	IupSetAttribute( cnv_wavform, "RASTERSIZE", "114x37" );
	// IupSetAttribute(cnv_wavform,"CANFOCUS","NO");
	IupSetCallback( cnv_wavform, "ACTION", (Icallback) canvas_action );
	IupUpdate( cnv_wavform );
	
	Ihandle* frmLength;
	Ihandle* lblLength;
	lblLength = IupLabel( "Length:\n0.00 Sec." );
	frmLength = IupFrame( lblLength );
	IupSetAttributes( frmLength, "SUNKEN=YES, MARGIN=5x3, RASTERSIZE=60x37" );
	
	hboxInfos = IupHbox( frmPosition, cnv_wavform, frmLength );
	
	// Ihandle* val_position;
	val_position = IupVal( "HORIZONTAL" );
	IupSetAttribute( val_position, "MIN", "0" );
	IupSetAttribute( val_position, "MAX", "1" );
	IupSetAttribute( val_position, "VALUE", "0.0" );
	IupSetAttribute( val_position, "RASTERSIZE", "234x21" );
	
	Ihandle* hboxControls;
	Ihandle* btn_rewind,* btn_fastforward,* btn_play;
	btn_rewind = IupSetAttributes( IupButton( "", NULL ), "IMAGE=IUP_MediaGoToBegin" );
	btn_fastforward = IupSetAttributes( IupButton( "", NULL ), "IMAGE=IUP_MediaGoToEnd" );
	btn_play = IupSetAttributes( IupButton( "", NULL ), "IMAGE=IUP_MediaPlay" );
	hboxControls = IupHbox( btn_rewind, btn_fastforward, btn_play, IupSetAttributes(IupButton( "", NULL ), "IMAGE=IUP_MediaStop" ), IupSetAttributes(IupButton( "", NULL ), "IMAGE=IUP_MediaRecord" ) );
	
	Ihandle* vbox;
	vbox = IupVbox( hboxInfos, val_position, hboxControls, NULL );
	
	IupSetAttribute( vbox, "ALIGNMENT", "ACENTER" );
	IupSetAttribute( vbox, "GAP", "5" );
	IupSetAttribute( vbox, "MARGIN", "5x3" );
	
	Ihandle* dlg;
	dlg = IupDialog( vbox );
	
	IupSetAttribute( dlg, "MENU", "mnu" );
	IupSetAttribute( dlg, "TITLE", "Sound - Sound Recorder Classic" );
	// IupSetAttribute( dlg, "RASTERSIZE", "276x151" );
	
	// Registers callbacks
	IupSetCallback( val_position, "VALUECHANGED_CB", (Icallback) val_position_cb );
	IupSetCallback( mnu_file_exit, "ACTION", (Icallback) mnu_file_exit_cb );
	
	IupShowXY( dlg, IUP_CENTER, IUP_CENTER );
	
	IupMainLoop();
	
	IupClose();
	return EXIT_SUCCESS;
}