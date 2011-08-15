<?php
/**
 * The template for displaying the footer.
 *
 * Contains the closing of the id=main div and all content
 * after.  Calls sidebar-footer.php for bottom widgets.
 *
 * @package WordPress
 * @subpackage Starkers
 * @since Starkers 3.0
 */
?>

			</div>
			<?php if ( function_exists('is_sidebar_active') && is_sidebar_active('region-content-bottom') ) { ?>
				<section id="content-bottom" class="region region-content_bottom">
				<?php dynamic_sidebar('region-content-bottom'); ?>
				</section> 
			<?php } ?>
		</div></div>

		<?php if (has_navbar() != '') { ?>
      <nav id="navbar"><div id="navbar-inner" class="clear-block region region-navbar">
          <a name="navigation" id="navigation"></a>
			<?php wp_nav_menu( array( 'sort_column' => 'menu_order', 'container_class' => 'menu-nav', 'theme_location' => 'primary'  ) ); ?>
			<?php if ( function_exists('is_sidebar_active') && is_sidebar_active('region-left') ) { ?>
			<?php dynamic_sidebar('region-navbar'); ?>
      <?php } ?>
			
			
        </div></nav>  
		<?php } ?>
 

     
	<?php if ( function_exists('is_sidebar_active') && is_sidebar_active('region-left') ) { ?>
        <section id="sidebar-left"><div id="sidebar-left-inner" class="region region-left">
         <?php dynamic_sidebar('region-left'); ?>
        </div></section>
      <?php } ?>

   
	<?php if ( function_exists('is_sidebar_active') && is_sidebar_active('region-right') ) { ?>
        <section id="sidebar-right"><div id="sidebar-right-inner" class="region region-right">
          <?php dynamic_sidebar('region-right'); ?>
        </div></section> 
      <?php } ?>

    </div></div> 
	<div id="push"></div>
	</div></div>
    <footer id="footer"><div id="footer-inner" class="region region-footer">
		<?php if ( function_exists('is_sidebar_active') && is_sidebar_active('region-footer') ) { ?>
            <?php dynamic_sidebar('region-footer'); ?>
		<?php }?>
   </div></footer> 
  <?php wp_footer(); ?>
</body>
</html>