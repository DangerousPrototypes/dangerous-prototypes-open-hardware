<?php
$cfg = require( 'bconfig.php' );

$base = 'http://' . $_SERVER[ 'SERVER_NAME' ] . $cfg->base_dir . '/img/';

// What to echo if no banners are found
$noBanner = 'No banners are found';

mysql_connect( $cfg->mysql_server, $cfg->mysql_user, $cfg->mysql_password );
mysql_select_db( $cfg->mysql_db );

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
	
	$query = mysql_query( "select id, url, ext $sql limit 1 offset " . rand( 0, $n[ 0 ] - 1 ) );
	
	$row = mysql_fetch_row( $query );
	if( ! $row ) // In the case of bad luck, if banners were deleted or expired between two requests
		$row = mysql_fetch_row( mysql_query( "select id, url, ext $sql limit 1" ) );
	
	if( $row )
		$banner = '<a href="' . $row[ 1 ] . '"><img src="' . $base . $row[ 0 ] . '.' . $row[ 2 ] . '" /></a>';
	else // ALL banners are deleted or expired
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
?>
