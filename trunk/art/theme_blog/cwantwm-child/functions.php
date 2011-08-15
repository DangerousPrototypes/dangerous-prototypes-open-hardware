<?php
 /*
 * @package WordPress
 * @subpackage Starkers
 * @since Starkers 3.0
 */

function twentyten_posted_on() {


	printf( __( '<div class="meta">%2$s in %4$s <span class="meta-sep">by</span> %3$s  | %5$s<div class="fuse' . rand(1,8) . '"></div></div>', 'twentyten' ),
		'meta-prep meta-prep-author',
		sprintf( '<span class="entry-date">%3$s</span>',
			get_permalink(),
			esc_attr( get_the_time() ),
			get_the_date()
		),
		sprintf( '<span class="author vcard"><a class="url fn n" href="%1$s" title="%2$s">%3$s</a></span>',
			get_author_posts_url( get_the_author_meta( 'ID' ) ),
			sprintf( esc_attr__( 'View all posts by %s', 'twentyten' ), get_the_author() ),
			get_the_author()
		),
		get_the_category_list( ', ' ),
		sprintf( '<span class="meta-comment-count"><a class="url fn n" href="%1$s" title="%2$s">%3$s</a></span>',
                       get_permalink() . '#comments-wrap', // use #comments to jump to top of comments; use #respond to jump to comment form
                        'jump to comments', // link alt text
                        (get_comments_number() != 1) ? get_comments_number().' comments' : get_comments_number().' comment'  // comments number
                )
	);

	
}


function twentyten_posted_in() {
	// Retrieves tag list of current post, separated by commas.
	$tag_list = get_the_tag_list( '', ', ' );
	if ( $tag_list ) {
		$posted_in = __( 'This entry was posted in %1$s and tagged %2$s.', 'twentyten' );
	} elseif ( is_object_in_taxonomy( get_post_type(), 'category' ) ) {
		$posted_in = __( 'This entry was posted in %1$s.', 'twentyten' );
	} else {
		$posted_in = "";
	}
	// Prints the string, replacing the placeholders.
	printf(
		$posted_in,
		get_the_category_list( ', ' ),
		$tag_list,
		get_permalink(),
		the_title_attribute( 'echo=0' )
	);
}


add_filter('widget_text', 'do_shortcode');

function banner_func($atts) {
     return get_option('site_banner');
}
add_shortcode('banner', 'banner_func');
function banner_func_link($atts) {
     return get_option('site_banner_link');
}
add_shortcode('banner_link', 'banner_func_link');
add_action('admin_init', 'add_some_settings');

 function add_some_settings() {
     // Add the field with the names and function to use for our new settings, put it in our new section
     add_settings_field('site_banner', 'Home Page Banner', 'banner_callback', 'general', 'default');
  add_settings_field('site_banner_link', 'Home Page Banner Link', 'banner_callback_link', 'general', 'default');
     // Register our setting so that $_POST handling is done for us and our callback function just has to echo the <input>
     register_setting('general','site_banner');
 register_setting('general','site_banner_link');
 }

 function banner_callback() {
    settings_fields( 'general' );
    echo '<input type="text" class="regular-text code" value="'.get_option('site_banner').'" id="site_banner" name="site_banner">';
}

function banner_callback_link() {
    settings_fields( 'general' );
    echo '<input type="text" class="regular-text code" value="'.get_option('site_banner_link').'" id="site_banner_link" name="site_banner_link">';
}