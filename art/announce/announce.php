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

<?php

$cfg = require( 'bconfig.php' );

$base = 'http://' . $_SERVER[ 'SERVER_NAME' ] . $cfg->base_dir . '/img/';

// What to echo if no banners are found
$noBanner = 'No banners are found';

mysql_connect( $cfg->mysql_server, $cfg->mysql_user, $cfg->mysql_password );
mysql_select_db( $cfg->mysql_db );

if( isset( $_GET[ 'redirect' ] ) && $_GET[ 'redirect' ] == 'true' && isset( $_GET[ 'id' ] ) ) {

	$id = ( int ) $_GET[ 'id' ];
	$query = mysql_query( "select url from banner where id = $id" );
	if( $banner = mysql_fetch_row( $query ) ) {
		mysql_query( "update banner set clicks = clicks + 1 where id = $id" );
		header( "Location: $banner[0]" );
	}

} else {

	$sql = <<<SQL
from banner where ( 
	start_date is null or start_date <= now() ) 
and ( 
	end_date is null or end_date >= now() )
SQL;
	
	$query = mysql_query( "select count(*) $sql" );
	$n = mysql_fetch_row( $query, 0 );
	
	if( ! ( $n && $n[ 0 ] ) ) 
		$banner = $noBanner;
	else {
		
		$query = mysql_query( "select id, url, ext, click_tracking, display_tracking $sql limit 1 offset " 
			. rand( 0, $n[ 0 ] - 1 ) );
		
		$row = mysql_fetch_row( $query );
		if( ! $row ) // In the case of bad luck, if banners were deleted or expired between two requests
			$row = mysql_fetch_row( mysql_query( "select id, url, ext $sql limit 1" ) );
		
		if( $row ) {
			$url = $row[ 3 ] ? 
				'http://' . $_SERVER[ 'SERVER_NAME' ] . $cfg->base_dir . '/announce.php?redirect=true&&id='
					. $row[ 0 ]
				: $row[ 1 ];
			$banner = '<a href="' . $url . '"><img src="' . $base . $row[ 0 ] . '.' . $row[ 2 ] . '" /></a>';
			if( $row[ 4 ] )
				mysql_query( 'update banner set displays = displays + 1 where id = ' . $row[ 0 ] );
		} else // ALL banners are deleted or expired
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
	} else
		echo $banner;
} 

?>
