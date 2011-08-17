<?php
/*
Plugin Name: Reader URLs
Description: Display a page of readers and the url they left.
Version: 1.0
Author: Kristiyan Ivanov
Author email: k.ivanow@gmail.com
Copyright: 2011 Where Labs, LLC, http://dangerousprototypes.com
License: CC BY-SA 3.0
*/

add_action('admin_menu', 'my_plugin_menu');

function my_plugin_menu() {
	add_options_page('Reader URL Options', 'Reader URLs', 'manage_options', 'reader-urls', 'reader_urls_options');
}

function reader_urls_options() {
	if (!current_user_can('manage_options'))  {
		wp_die( __('You do not have sufficient permissions to access this page.') );
	}
	
	$start=0;
	$prev=0;
	if(isset($_GET['start']) && is_numeric($start)) $start=$_GET['start'];
	
	$style=true;
	$mark=0;

	global $wpdb;
	/*$myrows = $wpdb->get_results( "SELECT comment_author, comment_author_url, comment_date, comment_ID FROM wp_comments WHERE comment_author_url != '' AND comment_author_url!='http://' LIMIT $start, 100", ARRAY_A );
*/
	$myrows = $wpdb->get_results( "SELECT comment_author, comment_author_url, comment_date, comment_ID FROM wp_comments WHERE comment_author_url != '' AND comment_author_url!='http://' AND comment_approved='1' GROUP BY comment_author ORDER BY comment_ID DESC LIMIT $start, 100", ARRAY_A );

	?><style type="text/css">
#table {
	margin-left:auto;
	margin-right:auto;
}
.left{
	border-right: solid 1px grey;
	padding-right:15px;
}
.mid{
	border-right: solid 1px grey; 
	padding-right:15px; 
	padding-left:15px;
}
.right{
	padding-left:15px;
}
</style>
<table id="table">
<th class="left"> ID </th>
<th class="left"> Reader </th>
<th class="left">URL</th>
<th class="right">Date</th>
<?php

	foreach ($myrows as $row) {
		print '<tr>
			<td class="left"><a href="comment.php?action=editcomment&c='.$row["comment_ID"].'">'.$row["comment_ID"].'</a></td> 
			<td class="mid">'.$row["comment_author"].'</td>
			<td class="mid"><a href="'.$row["comment_author_url"].'">'.$row["comment_author_url"].'</a></td>
			<td class="right">'.$row["comment_date"].'</td>
		</tr>';
	}
	
	$start+=100;
	$prev=$start-200;
	print '<tr><td>';
	if($prev>-1) print '<a href="?page=reader-urls&start='.$prev.'">Prev 100</a>';
	print '</td><td></td><td></td><td><a href="?page=reader-urls&start='.$start.'">Next 100</a></td></tr>';
	print '</table>';

}
?>