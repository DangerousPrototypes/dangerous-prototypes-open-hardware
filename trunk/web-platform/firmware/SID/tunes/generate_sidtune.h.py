##inFile = '1988_Top_40_MEGAMIX.sid'
##inFile = 'Commando_REMIX.sid'
##inFile = 'D_Y_S_P_I_D_C_E.sid'
##inFile = 'Des_Magiers_Kugel.sid'
##inFile = 'FAME_On_The_Run_1.sid'
##inFile = 'Gyruss.sid'
##inFile = 'Hawkeye_Remix.sid'
##inFile = 'Ikari_Intro.sid'
##inFile = 'Ikari_Intro_Song.sid'
##inFile = 'Ikari_Warriors_USA_Version.sid'
##inFile = 'Jump_Out.sid'
##inFile = 'Layla_Mix.sid'
##inFile = 'MCG_Intromusic.sid'
##inFile = 'Musique.sid'
##inFile = 'Nexion.sid'
##inFile = 'PCW-Tune_88.sid'
##inFile = 'R1D1.sid'
##inFile = 'Sad_Intro.sid'
##inFile = 'S-Express.sid'
##inFile = 'Starman.sid'
inFile = 'Treasure_Island.sid'
f = open( inFile, 'rb' ); data = f.read(); f.close()

f = open( 'sidtune.h', 'wt' );
##f.write( '#ifndef SID_TUNE\n' )
##f.write( '#define SID_TUNE\n' )
f.write( 'const unsigned char sidtune[] = {\n' )
for i, byte in enumerate( data ):
    ##print str( i ).zfill( 4 ), hex( byte )[ 2 : ].zfill( 2 ), bin( byte )[ 2 : ].zfill( 8 ).replace( '0', '.' )
    f.write( str( ord( byte ) ) + ', ' )
    if ( i + 1 ) % 8 == 0:
        print( i // 8 )
        f.write( '// %s\n' % ( ( i - 1 ) // 8 ) )
f.write( '};\n' )
##f.write( '#endif\n' )
f.close()
