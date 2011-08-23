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




$base = 'http://' . $_SERVER[ 'SERVER_NAME' ] . dirname( $_SERVER[ 'PHP_SELF' ] ) . '/img/';

if( isset( $_GET[ 'action' ] ) && $_GET[ 'action' ] == 'auth' && isset( $_POST[ 'remember' ] ) )
	session_set_cookie_params( 1296000 ); // 60 sec * 60 min * 24 h * 15 days
else
	session_set_cookie_params( 0 ); // Until user closes the browser

session_start();

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
	<meta http-equiv='Content-Type' content='text/html; charset=UTF-8' />
	<title>Banner rotation manager</title>
	<script type='text/javascript' src='datetimepicker_css.js'></script>
	<link rel='stylesheet' href='banner.css' type='text/css' />
	<script type='text/javascript' src='bmgr.js'></script>
</head><body>
<?php

if( isset( $_GET[ 'action' ] ) ) {
	$action = $_GET[ 'action' ]; 
	if( ! isset( $_SESSION[ 'logged_in' ] ) && $action != 'auth' )
		$action = 'login';
} else if( isset( $_SESSION[ 'logged_in' ] ) )
	$action = 'list';
else
	$action = 'login';

$cfg = require( 'bconfig.php' );
	
if( $action == 'auth' ) {
	if( isset( $_POST[ 'password' ] ) && $_POST[ 'password' ] == $cfg->admin_password ) {
		$_SESSION[ 'logged_in' ] = 1;
		$action = 'list';
	} else {
?>
	<div class='login_error'>Invalid password</div>
<?php
		$action = 'login';
	} 
}

if( $action == 'logout') {
	unset( $_SESSION[ 'logged_in' ] );
	$action = 'login';
}

if( $action == 'login' ) {
?>
	<div class='login_form'>
		<form method='post' action='bmgr.php?action=auth' >
			Password: <input type='password' name='password' /><br />
			<input type='checkbox' name='remember' value='yes' /> Remember<br />
			<input type='submit' value='Log in' />
		</form>
	</div>
<?php
}

mysql_connect( $cfg->mysql_server, $cfg->mysql_user, $cfg->mysql_password );
mysql_select_db( $cfg->mysql_db );

$dtid = 0;

function dateWithHint( $name, $value ) {
	global $dtid;
?>
<div class='date_with_hint'>
	<input type='text' maxlength='10' size='10' name='<?php echo $name; ?>' id='dt<?php echo $dtid; ?>' 
		value="<?php echo htmlentities( $value ); ?>" /><img src='http://<?php 
		echo $_SERVER[ 'SERVER_NAME' ] . dirname( $_SERVER[ 'PHP_SELF' ] ); 
		?>/dtp-images/cal.gif' onclick='NewCssCal( "dt<?php echo $dtid; ?>", "yyyyMMdd" );'
		style='cursor: pointer' />
	<div class='date_hint'>yyyy-mm-dd</div>
</div>
<?php
	++ $dtid;
}

function addBannerForm( $error, $hidden, 
	$url = '', $startDate = '', $endDate = '', 
	$track_clicks = 'checked', $track_displays = 'checked' ) {
?>	
	<form name='newBanner' 
			action='bmgr.php?action=add' 
			method='post'
			<?php if( $hidden ) { ?>
				style='display: none;'
			<?php } ?> 
			enctype='multipart/form-data' 
			onsubmit='return addBannerSubmit();' 
			onreset='return addBannerReset();'>
		<div class='error' id='addError' style='display: none;'><?php echo $error; ?></div>
		<span class='label_input'>
			URL: <input type='text' maxlength='255' size='50' name='url' 
				value="<?php echo htmlentities( $url );?>"/></span>
		<span class='input_join'>
			<span class='label_input'>Start date: <?php dateWithHint( 'start_date', $startDate ); ?></span>
			<span class='label_input'>End date: <?php dateWithHint( 'end_date', $endDate ); ?></span>
		</span>
		<span class='input_join'>
			<span class='label_input'>
				<input type='checkbox' name='track_clicks' <?php echo $track_clicks; ?> />
				Enable click tracking
			</span>
			<span class='label_input'>
				<input type='checkbox' name='track_displays' <?php echo $track_displays; ?> />
				Enable display tracking
			</span>
		</span>
		<br />
		<input type="hidden" name="MAX_FILE_SIZE" value="1048576" />
		<span class='label_input'>Image: <input type='file' size='50' name='image' /></span>
		<div class='buttons'>
			<input type='submit' value='Submit' />
			<input type='reset' value='Cancel' />
		</div>
	</form>
<?php
}

function showLogOut() {
?>
<div class='logout'><a href='bmgr.php?action=logout'>Log out</a></div>
<?php
}

if( $action == 'add' ) {
	if( $_FILES[ 'image' ][ 'error' ] != UPLOAD_ERR_OK ) {
		showLogOut();
		addBannerForm( 'Error uploading image', 
			false, 
			$_POST[ 'url'], 
			$_POST[ 'start_date' ], 
			$_POST[ 'end_date' ],
			isset( $_POST[ 'track_clicks' ] ) ? 'checked' : '',
			isset( $_POST[ 'track_displays' ] ) ? 'checked' : '' );
	} else {
		$url = mysql_real_escape_string( $_POST[ 'url' ] );
		
		$startDate = "'" . mysql_real_escape_string( $_POST[ 'start_date' ] ) . "'";
		if( $startDate == "''" )
			$startDate = 'null';
		
		$endDate = "'" . mysql_real_escape_string( $_POST[ 'end_date' ] ) . "'";
		if( $endDate == "''" )
			$endDate = 'null';
		
		$ext = pathinfo( $_FILES[ 'image' ][ 'name'], PATHINFO_EXTENSION );

		$sql = "insert into banner( url, ext, start_date, end_date, click_tracking, display_tracking ) "
			. "values( '$url', '$ext', $startDate, $endDate, "
			. ( isset( $_POST[ 'track_clicks' ] ) ? '1' : '0' ) . ", "
			. ( isset( $_POST[ 'track_displays' ] ) ? '1' : '0' ) . " )";
		
		if( ! mysql_query( $sql ) ) {
			showLogOut();
			addBannerForm( mysql_error(), 
				false, 
				$_POST[ 'url'], 
				$_POST[ 'start_date' ], 
				$_POST[ 'end_date' ],
				isset( $_POST[ 'track_clicks' ] ) ? 'checked' : '',
				isset( $_POST[ 'track_displays' ] ) ? 'checked' : '' );
		} else {
			$id = mysql_insert_id();
			
			$file = __DIR__ . '/img/' . $id . '.' . $ext;
			if( file_exists( $file ) )
				unlink( $file );
			
			if( ! move_uploaded_file( $_FILES[ 'image' ][ 'tmp_name' ], $file ) ) {
				mysql_query( 'delete from banner where id = ' . $id );
				showLogOut();
				addBannerForm( 'Error in uploading image', 
					false, 
					$_POST[ 'url'], 
					$_POST[ 'start_date' ], 
					$_POST[ 'end_date' ],
					isset( $_POST[ 'track_clicks' ] ) ? 'checked' : '',
					isset( $_POST[ 'track_displays' ] ) ? 'checked' : '' );
			} else
				$action = 'list';
		}
	}
}

$uploadID = -1;
$changeID = -1;
$error = '';

if( $action == 'change' ) {
	
	$id = mysql_real_escape_string( $_POST[ 'id' ] );
	
	$url = mysql_real_escape_string( $_POST[ 'url' ] );
	
	$startDate = "'" . mysql_real_escape_string( $_POST[ 'start_date' ] ) . "'";
	if( $startDate == "''" )
		$startDate = 'null';
	
	$endDate = "'" . mysql_real_escape_string( $_POST[ 'end_date' ] ) . "'";
	if( $endDate == "''" )
		$endDate = 'null';

	$sql = "update banner set url = '$url', start_date = $startDate, end_date = $endDate, click_tracking = "
		. ( isset( $_POST[ 'track_clicks' ] ) ? '1' : '0' ) . ", display_tracking = "
		. ( isset( $_POST[ 'track_displays' ] ) ? '1' : '0' ) . " where id = '$id'";

	if( ! mysql_query( $sql ) ) {
		$error = mysql_error();
		$changeID = $_POST[ 'id' ];
	}
	
	$action = 'list';
}

if( $action == 'upload' ) {

	$id = $_POST[ 'id' ];
	
	if( $_FILES[ 'image' ][ 'error' ] != UPLOAD_ERR_OK ) {
		$error = 'Error in uploading image';
		$uploadID = $id;
	} else {
		
		$query = mysql_query( 'select ext from banner where id = ' . $id );
		if( $rec = mysql_fetch_object( $query ) ) {
			$file = __DIR__ . '/img/' . $id . '.' . $rec->ext;
			if( file_exists( $file ) )
				unlink( $file );
		}
		
		$ext = pathinfo( $_FILES[ 'image' ][ 'name'], PATHINFO_EXTENSION );
		if( $rec && $rec->ext != $ext )
			mysql_query( "update banner set ext = '" . mysql_real_escape_string( $ext ) . "' where id = $id" );

		$file = __DIR__ . '/img/' . $id . '.' . $ext;
		if( file_exists( $file ) )
			unlink( $file );
		
		if( ! move_uploaded_file( $_FILES[ 'image' ][ 'tmp_name' ], $file ) ) {
			$error = 'Error in uploading image';
			$uploadID = $id;
		}
	}
	
	$action = 'list';
}

if( $action == 'delete' ) {
	$ids = $_POST[ 'id' ];
	$where = 'where id = ' . implode( ' or id = ', $ids );
	$query = mysql_query( 'select id, ext from banner ' . $where );
	while( $r = mysql_fetch_object( $query ) ) {
		$file = __DIR__ . '/img/' . $r->id . '.' . $r->ext;
		if( file_exists( $file ) )
			unlink( $file );
	}
	if( ! mysql_query( 'delete from banner ' . $where ) ) {
?>
	<div class='error'><?php echo mysql_error(); ?></div>
<?php 
	}
	
	$action = 'list';
}

if( $action == 'list' ) {
	showLogOut();
?>
	<button id='bAdd' onclick='showAddBanner();'>Add banner</button><br />
<?php 
	addBannerForm( '', true );
	
	$query = mysql_query( 'select * from banner' );
	if( mysql_num_rows( $query ) == 0 ) {
?>
	<div class='no_banners'>List of banners is empty.</div>
<?php
	} else { 
?>
	<span class='label_input'>
		Select:
		<button onclick='selectAll();' >All</button>
		<button onclick='selectNone();'>None</button>
		<button onclick='selectExpired();'>All expired</button>
	</span>
	<button onclick='deleteSelected();'>Delete selected</button>
<?php
		$n = 0;
		while( $b = mysql_fetch_object( $query ) ) {
?>
	<script type='text/javascript'>
		bannerList.push( { 
			id: <?php echo $b->id; ?>,
			dtEnd: Date.parse( '<?php echo addslashes( $b->end_date ); ?>' )
		} );
	</script>
	<div class='bannerItem'>
		<input type='checkbox' id='checkBox<?php echo $n; ?>' />
		<table class='bannerContent'><tr>
			<td>
				<span class='bannerLabel'>Image:</span>
				<img src='<?php echo $base . $b->id . '.' . $b->ext; ?>' />
				<form name='upload<?php echo $n; ?>'
						action='bmgr.php?action=upload' 
						method='post'
						<?php if( $uploadID != $b->id ) { ?>
							style='display: none;'
						<?php } ?> 
						enctype='multipart/form-data' 
						onsubmit='return uploadSubmit( <?php echo $n;?> );' 
						onreset='return uploadReset( <?php echo $n;?> );'>
					<div class='error' id='uploadErr<?php echo $n; ?>' style='display: none;'><?php echo $error; ?></div>
					<input type='hidden' name='id' value='<?php echo $b->id; ?>' />
					<input type="hidden" name="MAX_FILE_SIZE" value="1048576" />
					<span class='label_input'>Image: <input type='file' size='50' name='image' /></span>
					<div class='buttons'>
						<input type='submit' value='Submit' />
						<input type='reset' value='Cancel' />
					</div>
				</form>
			</td><td>
				<button onclick='changeImage( <?php echo $n; ?> );' id='btUpload<?php echo $n; ?>' >
					Change
				</button>
			</td></tr><tr><td>
				<span class='label_input'>
					<span class='bannerLabel'>URL:</span>
					<?php echo htmlentities( $b->url ); ?>
				</span>
				<span class='input_join'>
					<span class='label_input'>
						<span class='bannerLabel'>Start date:</span>
						<?php echo $b->start_date == null ? '-' : $b->start_date; ?>
					</span><span class='label_input'>
						<span class='bannerLabel'>End date:</span>
						<?php echo $b->end_date == null ? '-' : $b->end_date; ?>
					</span>
				</span>
				<span class='input_join'>
					<span class='label_input'>
						<span class='bannerLabel'>Click count</span> (<?php 
							echo ( $b->click_tracking ? 'enabled)' : 'disabled)' )
								. ': ' . $b->clicks; ?>
					</span><span class='label_input'>
						<span class='bannerLabel'>Display count</span> (<?php 
							echo ( $b->display_tracking ? 'enabled)' : 'disabled)' )
								. ': ' . $b->displays; ?>
					</span>
				</span>
				<form name='change<?php echo $n; ?>'
						action='bmgr.php?action=change' 
						method='post'
						<?php if( $changeID != $b->id ) { ?>
							style='display: none;'
						<?php } ?> 
						enctype='multipart/form-data' 
						onsubmit='return changeSubmit( <?php echo $n; ?> );' 
						onreset='return changeReset( <?php echo $n; ?> );'>
					<div class='error' id='changeErr<?php echo $n; ?>' style='display: none;'><?php echo $error; ?></div>
					<input type='hidden' name='id' value='<?php echo $b->id; ?>' />
					<span class='label_input'>
						URL: <input type='text' maxlength='255' size='50' name='url' 
							value="<?php echo htmlentities( $b->url );?>"/>
					</span><span class='input_join'>
						<span class='label_input'>
							Start date: <?php dateWithHint( 'start_date', $b->start_date ); ?>
						</span><span class='label_input'>
							End date: <?php dateWithHint( 'end_date', $b->end_date ); ?>
						</span>
					</span><span class='input_join'>
						<span class='label_input'>
							<input type='checkbox' name='track_clicks' <?php 
								if( $b->click_tracking ) echo 'checked '?>/> Enable click tracking
						</span>
						<span class='label_input'>
							<input type='checkbox' name='track_displays' <?php 
								if( $b->display_tracking ) echo 'checked '?>/> Enable display tracking
						</span>
					</span>
					<br />
					<div class='buttons'>
						<input type='submit' value='Submit' />
						<input type='reset' value='Cancel' />
					</div>
				</form>
			</td><td>
				<button onclick='changeData( <?php echo $n; ?> );' id='btChange<?php echo $n; ?>'>
					Change
				</button>
			</td></tr>
		</table>
		<hr />
	</div>
<?php 
			++ $n;
		}
	}
}
?>
<form name='deleter' style='display: none;' action='bmgr.php?action=delete' method='post'></form>
</body></html>
