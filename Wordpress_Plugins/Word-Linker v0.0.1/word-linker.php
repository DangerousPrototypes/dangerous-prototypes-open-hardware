<?php
/*
Plugin Name: Word Linker
Documentation: http://dangerousprototypes.com/docs/Wordpress_plugin:_Word_Linker
Plugin URI: http://dangerousprototypes.com/docs/Wordpress_Word_Link_plugin
Description: Replace words with anchored links
Author: Rob Holmes
Author URI: http://www.cwantwm.co.uk
Version: 0.0.1
Tags: Wordpress

*/


add_action('admin_menu', 'create_menu');

add_filter('the_content', 'replace_words_content');
add_filter('the_excerpt', 'replace_words_excerpt');
add_filter('comment_text', 'replace_words_comment');


// Add the options page to the admin screen
function create_menu() {
	add_options_page('Word Linker', 'Word Linker', 'manage_options', __FILE__, 'settings_page');
	add_action( 'admin_init', 'register_settings' );
}

// Register plugin options on the settings page
function register_settings() {
	register_setting( 'words-group', 'words' );
	register_setting( 'words-group', 'filter-content' );
	register_setting( 'words-group', 'filter-excerpts');
	register_setting( 'words-group', 'filter-comments');
}


// Output the settings page html using the Settings API
function settings_page() {
?>
<div class="wrap">
<h2>Word Linker</h2>

<form method="post" action="options.php">
    <?php settings_fields( 'words-group' ); ?>
   
    <table class="form-table">
        <tr valign="top">
        <th scope="row">Word / URL Pairs</th>
        <td><textarea name="words" cols='80' ><?php echo get_option('words'); ?></textarea>
		<div><b>Insutructions</b><br/>
		Put each word and url pair on a new line<br/>
		Separate the word from the url by a pipe <br/>
		e.g. google | http://google.com
		</div></td>
        </tr>
		<tr valign="top">
        <th scope="row">Replace in main content?</th>
        <td><input type="checkbox" name="filter-content" <?php checked( get_option('filter-content'), 1 ); ?> value='1'  /></td>
        </tr>
		<tr valign="top">
        <th scope="row">Replace in excerpts?</th>
        <td><input type="checkbox" name="filter-excerpts" <?php checked( get_option('filter-excerpts'), 1 ); ?> value='1'  /></td>
        </tr>
         <tr valign="top">
        <th scope="row">Replace in comments?</th>
        <td><input type="checkbox" name="filter-comments" <?php checked( get_option('filter-comments'), 1 ); ?> value='1'  /></td>
        </tr>
     
    </table>
    
    <p class="submit">
    <input type="submit" class="button-primary" value="<?php _e('Save Changes') ?>" />
    </p>

</form>
</div>
<?php } 


// Called whenever PREG finds a match, 
function replace_callback($matches) { 
    $pair=getpairs();
	return '<a href="' . get_url($pair, $matches[0]). '">' . $matches[0]. '</a>';
} 

// Retrieve the url associated with a text string
function get_url($pair, $match) {
    foreach ($pair as $key => $value) {
		if (strtolower($key) == strtolower($match)) {
			return $value;
		}
	}
	return '';
}
   
// Return an array containing all word/url pairs entered on the options page
function getpairs() {
	$lines = preg_split( '/\r\n|\r|\n/',get_option('words') ); 
		foreach ($lines as $line) {
		   $explode = explode('|',$line);
		   $pair[trim($explode[0])] = $explode[1]; 
		}
		return $pair;
   }
  
// Replace the first occurance of each word with a link
function replace_words($text) {
	global $t;
	
	// Loop through each entry
	$lines = preg_split( '/\r\n|\r|\n/',get_option('words') ); 
	foreach ($lines as $line) {
		// split the line into two
	    $pair = explode('|',$line);
		// Reomve whitespace and prepare string
		$escaped_words = preg_quote(trim($pair[0]), '/');
		// Find the first matching word regardless of case that does not appear inside another link and send to the callback 'replace_callback'
		$text = preg_replace_callback('\'(?!((<.*?)|(<a.*?)))(\b'. $escaped_words . '\b)(?!(([^<>]*?)>)|([^>]*?</a>))\'si','replace_callback', $text,1);
		  
	}
	return $text;
}

// Filter the content
function replace_words_content($text) {
	if (get_option('filter-content') == 1) {
		return replace_words($text);
	} else {
		return $text;
	}
}


// Filter the excerpt
function replace_words_excerpt($text) {
	if (get_option('filter-excerpt') == 1) {
		return replace_words($text);
	} else {
		return $text;
	}
}

// Filter the comments
function replace_words_comment($text) {
	if (get_option('filter-comments') == 1) {
		return replace_words($text);
	} else {
		return $text;
	}
}
