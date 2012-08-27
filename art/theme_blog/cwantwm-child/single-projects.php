<?php
/**
 * Single Projectpage.
 *
 * @package WordPress
 * @subpackage Dangerous
 * @author SvenW
 * @version 1.0
 * 
 */
get_header(); 
?>

<?php
	if ( have_posts() ) 
		the_post();
?>
	<!-- Begin Post -->
	<div id="post-<?php the_ID(); ?>" <?php post_class(); ?>>
    	<h1><?php the_title(); ?></h1>
        <?php the_content(); ?>
        
        <?php 
			$customs = get_post_custom($post->ID);
			$buy_url = $customs["_buy_url"][0];
			$price = $customs["_price"][0];
			$status = $customs["_status"][0];
			$manufacturing = $customs["_manufacturing"][0];
			$documentation = $customs["_documentation"][0];
			$forum = $customs["_forum"][0];
			//replaced with shortcodes in final
			//$productimages = $customs['productimage'];
		?>        
        
        <!-- Begin InfoBox -->
        <div class="project-info-box">
        	<h6>Project Summary</h6>
        	<ul>
            	<li><strong>Name:</strong>&nbsp;<?php the_title(); ?></li>
            	<li><strong>Price:</strong>&nbsp;<?php echo $price; ?> $</li>                
                <li><strong>Status:</strong>&nbsp;<a href="/docs/Project_status#Development_status" title="Development Status"><?php echo $status; ?></a></li>
                <li><strong>Manufacturing:</strong>&nbsp;<a href="/docs/Project_status#Manufacturing" title="Project Status"><?php echo $manufacturing; ?></a></li>
                <li><strong>Documentation:</strong>&nbsp;<a href="<?php echo $documentation; ?>" title="Documentation">Here</a></li>
                <li><strong>Forum:</strong>&nbsp;<a href="<?php echo $forum; ?>" title="Forum">Here</a></li>
            </ul>
        </div>
        <!-- End InfoBox -->
        <div class="clearfix"></div>
        <!-- Begin other Projects -->
<?php 
		echo '<div id="projects-other"><h3>Other Projects</h3><ul class="small-thumbs">';
		$args=array(
			'post_type' => array('projects'),
			'post__not_in' => array($post->ID),
			'showposts' => 5,
			'caller_get_posts' => 1
		);
		$my_query = new WP_Query($args);
		if( $my_query->have_posts() ) {
			while ($my_query->have_posts()) :
				$my_query->the_post();
?>
				<li>
				<span class="alignleft">
					<a href="<?php the_permalink() ?>" rel="bookmark" title="Permanent Link to <?php the_title_attribute(); ?>"><?php the_post_thumbnail( array(50,50) ); ?></a>				
				</span>
				<a class="teaser-title" href="<?php the_permalink() ?>" rel="bookmark" title="Permanent Link to <?php the_title_attribute(); ?>"><h5><?php the_title(); ?></h5></a>
				<div class="teaser-content">
					<?php the_excerpt(); ?>
				</div>
				<div class="clearfix"></div>
			</li>
<?php
			endwhile;
		}
		echo "</ul></div>";
		wp_reset_query(); 
?>
        <!-- End other Projects -->
        
        <!-- Begin ProjectPosts -->
<?php
		echo "<div id=\"projects-posts\"><h3>". get_the_title() ." on the Blog</h3><ul>";
		$args=array(
			'category_name' => strtolower(get_the_title($post->ID)),
			'post_type' => array('post'),
			'post__not_in' => array($post->ID),
			'showposts' => 5,
			'caller_get_posts' => 1
		);
		$my_query = new WP_Query($args);
		if( $my_query->have_posts() ) {
			while ($my_query->have_posts()) :
				$my_query->the_post();
?>
				<li>
				<span class="alignleft">
					<a href="<?php the_permalink() ?>" rel="bookmark" title="Permanent Link to <?php the_title_attribute(); ?>"><?php the_post_thumbnail( array(50,50) ); ?></a>				
				</span>
				<a class="teaser-title" href="<?php the_permalink() ?>" rel="bookmark" title="Permanent Link to <?php the_title_attribute(); ?>"><h5><?php the_title(); ?></h5></a>
				<div class="teaser-content">
					<?php the_excerpt(); ?>
				</div>
				<div class="clearfix"></div>
			</li>
<?php
			endwhile;
		}
		echo "</ul></div>";
		wp_reset_query(); 	
?>
        <!-- End ProjectsPosts -->
    </div>
    <!-- End Post -->    
<?php
	//Speed/Load Opt: Add Sliderscript only if there are Demos 
	if($GLOBALS['demo_count'] > 0) :
?>
<script type="text/javascript" src="<?php bloginfo('template_url'); ?>/js/jcarousellite_1.0.1.pack.js"></script>
<script type="text/javascript">
	$("#project-demos .carousel").jCarouselLite({
<?php //Do AutoScroll when there are more Demos
	if($GLOBALS['demo_count'] > 10) :
?>
		auto: 1000,
		speed: 1000,
<?php endif; ?>
		btnNext: ".next",
		btnPrev: ".prev"
    });
</script>
<?php
	endif; //demos
	
	//Footer
	get_footer();
?>
