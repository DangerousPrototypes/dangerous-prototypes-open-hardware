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
       
