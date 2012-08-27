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

    /* ProjectsPostType */
    function post_type_projects() {
       register_post_type(
          'projects',
          array('label' => __('Projects'),
                'singular_label' => __('Project'),
               'public' => true,
               'publicly_queryable' => true,
               'show_ui' => true,
               'show_in_menu' => true,
               'show_in_nav_menus' => true,
               'capability_type' => 'post',
               'hierarchical' => false,
               'has_archive' => true,
               'rewrite' => array( 'slug' => 'projects', 'with_front' => true),
               'supports' => array('title','editor', 'thumbnail','custom-fields'),
               'menu_position' => null
               )
       );
    }

    function admin_init() {
       add_meta_box("buy_url-meta", "Buy Url", "buy_url", "projects", "side", "core");
       add_meta_box("project_info-meta", "Project Informations", "projects_meta", "projects", "side", "core");
    }

    /*
        This url is the MainURL for Seeedstudio
        other urls are done with Shortcodes
    */
    function buy_url() {
       global $post;
       $custom = get_post_custom($post->ID);
       $buy_url = $custom["_buy_url"][0];
    ?>
       <p><label for="buy_url">Buy URL:</label><input name="buy_url" value="<?php echo $buy_url; ?>" /></p>
    <?php
    }

    function projects_meta() {
       global $post;
       $custom = get_post_custom($post->ID);
       $price = $custom["_price"][0];
       $status = $custom["_status"][0];
       $manufacturing = $custom["_manufacturing"][0];
       $documentation = $custom["_documentation"][0];
       $forum = $custom["_forum"][0];
    ?>
       <input type="hidden" name="project_noncename" id="project_noncename" value="<?php echo wp_create_nonce( 'project_type' . $post->ID );?>" />
       <p><label for="price">Price:</label><br /><input name="price" value="<?php echo $price; ?>" /></p>
       <p><label for="status">Status:</label><br /><input name="status" value="<?php echo $status; ?>" /></p>
       <p><label for="manufacuring">Manufacturing:</label><br /><input name="manufacturing" value="<?php echo $manufacturing; ?>" /></p>
       <p><label for="documentation">Documentation:</label><br /><input name="documentation" value="<?php echo $documentation; ?>" /></p>
       <p><label for="forum">Forum:</label><br /><input name="forum" value="<?php echo $forum; ?>" /></p>
    <?php
    }


    function save_project_infos( $post_id ) {
       // verify if this is an auto save routine.
       // If it is our form has not been submitted, so we dont want to do anything
       
       if ( defined( 'DOING_AUTOSAVE' ) && DOING_AUTOSAVE )
          return $post_id;
          
       // verify this came from the our screen and with proper authorization,
       // because save_post can be triggered at other times
       
       if ( !wp_verify_nonce( $_POST['project_noncename'], 'project_type'.$post_id )) {
          return $post_id;
       }
       
       // Check permissions : only Admins can modify this Page
       if( !current_user_can('administrator') ) {
          return $post_id;
       }

       // OK, we're authenticated: we need to find and save the data
       
       $post = get_post($post_id);
       
       if ($post->post_type == 'projects') {
          update_post_meta($post_id, '_buy_url', esc_attr($_POST['buy_url']) );
          update_post_meta($post_id, '_price', esc_attr($_POST['price']) );
          update_post_meta($post_id, '_status', esc_attr($_POST['status']) );
          update_post_meta($post_id, '_manufacturing', esc_attr($_POST['manufacturing']) );
          update_post_meta($post_id, '_documentation', esc_attr($_POST['documentation']) );
          update_post_meta($post_id, '_forum', esc_attr($_POST['forum']) );
          return $post_id;
       }
       return $post_id;
    }

    add_action( "init", "post_type_projects");
    add_action( "admin_init", "admin_init");
    add_action( "save_post", "save_project_infos" );


//------

    //TODO: StripOut non-exclusives
    //TODO: ExtractAtts WPCODEX

    /* Shortcode: FeaturesListStyle */
    function dp_features($atts, $content = null) {
       return '<!-- Begin Features --><div id="project-features" class="featurelist"><h3>Features</h3>'.$content.'</div><!-- End Features -->';
    }

    add_shortcode('features', 'dp_features');

    /* Shortcode: ProjectImageGallery */
    function projectGallery($atts, $content = null) {
       $GLOBALS['image_count'] = 0;
       
       do_shortcode( $content );
       
       /* TODO: image class */
       if( is_array( $GLOBALS['images'] ) ) {
          foreach( $GLOBALS['images'] as $image )
          {
             $images[] = '<a class="thickbox" rel="gallery" href="'.$image['content'].'"><img src="'.$image['content'].'" alt="" class="'. $image['class'] . '" title="' . $image['title'] . '" /></a>';
          }
          $result = "\n".'<!-- Begin ProductImages --><div class="project-gallery">'.implode( "\n", $images ).'</div>'."\n".'<!-- End ProductImages -->'."\n<div class=\"clearfix\"></div>\n";
       }
       return $result;
    }

    add_shortcode('productimages', 'projectGallery');

    /* Shortcode: Image */
    function project_image( $atts, $content = null ) {
       $title = $atts['title'];
       $class = $atts['class'];
       
       $x = $GLOBALS['image_count'];
       $GLOBALS['images'][$x] = array( 'title' => $title, 'class' => $class, 'content' =>  $content );
       $GLOBALS['image_count']++;
    }

    add_shortcode( 'image', 'project_image' );

    /* Project Demonstrations */
    function projectTutorials( $att, $content = null ) {
       $GLOBALS['demo_count'] = 0;
       
       do_shortcode( $content );
       
       if( is_array( $GLOBALS['demos'] ) ) {
          foreach( $GLOBALS['demos'] as $tutorial )
          {
             $tutorials[] = '<li><a href="'.$tutorial['url'].'"><img src="'.$tutorial['image'].'" alt="" title="' . $tutorial['title'] . '" width="100" height="100" /></a></li>';
          }
          $final = "\n".'<!-- Begin Demonstrations -->
                      <div id="project-demos">
                         <h3>Demonstrations</h3>
                         <a href="#" class="prev"><<</a>
                         <div class="carousel">
                            <ul>'.implode( "\n", $tutorials ).'</ul>
                         </div>'."\n".'
                         <a href="#" class="next">>></a>
                      </div>
                      <!-- End Demonstrations -->'."\n<div class=\"clearfix\"></div>\n";
       }
       return $final;   
    }

    add_shortcode('productdemos', 'projectTutorials');

    /* Shortcode: Demo */
    function project_demo( $atts, $content = null ) {
       $title = $atts['title'];
       $url = $atts['url'];
       $image = $atts['image'];
       
       $x = $GLOBALS['demo_count'];
       $GLOBALS['demos'][$x] = array( 'title' => $title, 'url' => $url, 'image' =>  $image );
       $GLOBALS['demo_count']++;
    }

    add_shortcode( 'demo', 'project_demo' );


