<?php
/**
 *
 * @package WordPress
 * @subpackage Dangerous
 * @copyright DangerousPrototypes
 * @author SvenW
 * @version 1.0
 * 
 */
	get_header();
?>
	<div id="content-left">
	<!-- Begin Projectslist -->
	<div id="projectslist">
		<h1>Our Projects</h1>
			<ul>
			
<?php
	if ( have_posts() ) : 
	while ( have_posts() ) : 
	the_post(); 
?>
	<li>
		<h2><a href="<?php the_permalink(); ?>" title="<?php the_title(); ?>"><?php the_title(); ?></a></h2>
<?php if ( has_post_thumbnail()) { ?>
		<div class="post-image-holder pngfix">
			<div class="post-image">
				<a href="<?php the_permalink(); ?>" title="<?php the_title_attribute(); ?>">
					<?php the_post_thumbnail(array(200, 200)); ?>
				</a>
			</div>
		</div>
<?php
		}
		the_content();
?>
	</li>	
<?php
	endwhile;
	endif;
?>
		</ul>
</div><!-- End Projectslist -->
<?php		// Pagination
		if(function_exists('wp_pagenavi')) :
		    wp_pagenavi();
		else : ?>
		    <div class="navigation">
			    <div class="alignleft"><?php previous_posts_link() ?></div>
			    <div class="alignright"><?php next_posts_link() ?></div>
		    </div>
<?php		endif; ?>
</div>
<div id="content-right">
<?php get_sidebar(); ?>
</div>
<?php get_footer();?>
