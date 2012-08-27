<?php
/*
Template Name: Contest
*/
/**
 *
 * @package WordPress
 * @subpackage Starkers
 * @since Starkers 3.0
 */

get_header(); ?>

<?php if ( have_posts() ) while ( have_posts() ) : the_post(); ?>

					<?php if ( is_front_page() ) { ?>
						<h2 ><?php the_title(); ?><span class='diode'></span></h2>
					<?php } else { ?>	
						<h1 ><?php the_title(); ?><span class='diode'></span></h1>
					<?php } ?>				

						<?php the_content(); ?>
						<?php wp_link_pages( array( 'before' => '' . __( 'Pages:', 'twentyten' ), 'after' => '' ) ); ?>
						<?php edit_post_link( __( 'Edit', 'twentyten' ), '', '' ); ?>

				<?php comments_template( '', true ); ?>

<?php endwhile; ?>
       
        <script type="text/javascript">
        	
        	jQuery(function($) {
        	  var theWindow        = $(window),
        	      aspectRatio,
        	      $bg              = $("<img>"),
        	      bg               = $bg[0];
        	
        	  $bg.hide().load(bgLoad);
        	  bg.id = "bg";
        	  bg.src = "wp-content/themes/cwantwm-child/contestbg2.jpg";
        	
        	  $bg.appendTo(document.body);
        	
        	  theWindow.resize(resizeBg);
        	
        	  function bgLoad() {
        	    aspectRatio = $bg.width() / $bg.height();
        	
        	    resizeBg();
        	
        	    //$bg.fadeIn();
        	    $bg.show();
        	   
        	  }
        	
        	  function resizeBg() {
        	
        	      if ( (theWindow.width() / theWindow.height()) < aspectRatio ) {
        	          $bg
        	              .removeClass()
        	              .addClass('bgheight');
        	      } else {
        	          $bg
        	              .removeClass()
        	              .addClass('bgwidth');
        	      }
        	
        	  }
        	});
        	        	</script>

<?php get_footer(); ?>