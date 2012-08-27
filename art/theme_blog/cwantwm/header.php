<?php
/**
 * @package WordPress
 * @subpackage Starkers
 * @since Starkers 3.0
 */
?><!DOCTYPE html>
<!--[if lt IE 7 ]> <html class="no-js ie6" <?php language_attributes(); ?>> <![endif]-->
<!--[if IE 7 ]>    <html class="no-js ie7" <?php language_attributes(); ?>> <![endif]-->
<!--[if IE 8 ]>    <html class="no-js ie8" <?php language_attributes(); ?>> <![endif]-->
<!--[if (gte IE 9)|!(IE)]><!--> <html class="no-js" <?php language_attributes(); ?>> <!--<![endif]-->
<head>
<meta charset="<?php bloginfo( 'charset' ); ?>" />
<title><?php wp_title( '|', true, 'right' );?></title>
<link rel="stylesheet" type="text/css" media="all" href="<?php bloginfo( 'stylesheet_url' ); ?>" />
<?php if(is_page_template('project.php')) :?>
<link rel="stylesheet" type="text/css" href="/wp-content/themes/cwantwm-child/project.css" media="screen" />
<?php endif;?>
<?php if(is_page_template('contest.php')) :?>
<link rel="stylesheet" type="text/css" href="/wp-content/themes/cwantwm-child/contest.css" media="screen" />
<?php endif;?>
<link rel="pingback" href="<?php bloginfo( 'pingback_url' ); ?>" />
 <script src="/wp-content/themes/cwantwm/js/modernizr-1.7.min.js"></script>
<?php
	/* Comment form javascript */
	if ( is_singular() && get_option( 'thread_comments' ) )
		wp_enqueue_script( 'comment-reply' );
	wp_head();
?>
</head>

<body <?php body_class(); ?>>

<div id="page"><div id="page-inner">
    <a id="navigation-top"></a>
    <div id="skip-to-nav"><a href="#navigation"><?php print 'Skip to Navigation'; ?></a></div>
    <header id="header"><div id="header-inner" class="clearfix">
     <?php if ( function_exists('is_sidebar_active') && is_sidebar_active('region-header') ) { ?>		
        <div id="header-blocks" class="region region-header">
          <?php dynamic_sidebar( 'region-header' ); ?>
        </div>
      <?php } ?>
    </div></header>

    <?php if (has_navbar() != '') { ?>
          <nav id="navbar"><div id="navbar-inner" class="clear-block region region-navbar">
              <a name="navigation" id="navigation"></a>
             <?php wp_nav_menu( array( 'sort_column' => 'menu_order', 'container_class' => 'menu-nav', 'theme_location' => 'primary'  ) ); ?>
             <?php if ( function_exists('is_sidebar_active') && is_sidebar_active('region-left') ) { ?>
             <?php dynamic_sidebar('region-navbar'); ?>
          <?php } ?>
             
             
            </div></nav> 
          <?php } ?>

    <div id="main"><div id="main-inner" class="clearfix <?php print has_navbar(); ?>">
		<div id="content"><div id="content-inner">
			<?php if ( function_exists('is_sidebar_active') && is_sidebar_active('region-content-top') ) { ?>		
				<div id="content-top" class="region region-content_top">
					<?php dynamic_sidebar('region-content-top'); ?>
				</div> <!-- /#content-top -->
			<?php } ?>  
			<div id="content-area">