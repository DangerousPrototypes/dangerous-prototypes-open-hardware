<?php
/*
       Simple announcement banner rotator with impression and click tracking.

   Used for site-wide announcements at DangerousPrototypes.com
   Copyright (C) 2011 Where Labs, LLC (http://dangerousprototypes.com)
   Written by Vyacheslav V Sokolov

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see<http://www.gnu.org/licenses/>.

*/

$cfg = require( 'bconfig.php' );

$base = 'http://' . $_SERVER[ 'SERVER_NAME' ] . $cfg->base_dir . '/img/';

// What to echo if no banners are found
$noBanner = 'No banners are found';

mysql_connect( $cfg->mysql_server, $cfg->mysql_user, $cfg->mysql_password );
mysql_select_db( $cfg->mysql_db );

if( isset( $_GET[ 'redirect' ] ) && $_GET[ 'redirect' ] == 'true' && isset( $_GET[ 'id' ] ) ) {

	if(is_numeric($_GET[ 'id' ])){ //sanatize it
		$id = ( int ) $_GET[ 'id' ];
	}else{
		$id=0;
	}
	
	$query = mysql_query( "SELECT url FROM banner WHERE id = $id" );
	if( $banner = mysql_fetch_row( $query ) ) {
		mysql_query( "UPDATE banner SET clicks = clicks + 1 WHERE id = $id" );
		header( "Location: $banner[0]" );
	}

} else {
	
	$query = mysql_query('SELECT id, url, ext, click_tracking, display_tracking FROM banner WHERE ( start_date is null OR start_date <= NOW() ) AND ( end_date is null OR end_date >= NOW() ) ORDER BY RAND() LIMIT 1');
		
	$row = mysql_fetch_row( $query );

	if( $row ) {
		$url = $row[ 3 ] ? 
			'http://' . $_SERVER[ 'SERVER_NAME' ] . $cfg->base_dir . '/announce.php?redirect=true&&id='
				. $row[ 0 ]
			: $row[ 1 ];
		$banner = '<a href="' . $url . '"><img src="' . $base . $row[ 0 ] . '.' . $row[ 2 ] . '" /></a>';
		if( $row[ 4 ] )
			mysql_query( 'update banner set displays = displays + 1 where id = ' . $row[ 0 ] );
	} else{ // ALL banners are deleted or expired
		$banner = $noBanner;
	}

	
	if( isset( $_GET[ 'ajax' ] ) ) {
		header( 'Content-type: text/xml' );
		echo '<?xml version="1.0" ?>';
	?>
	<banner>
	<content><?php echo htmlentities( $banner ); ?></content>
	</banner>
	<?php
	} else {
		echo $banner;
	}
} 

?>
