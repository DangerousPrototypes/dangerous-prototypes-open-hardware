<?php if( !defined( 'MEDIAWIKI' ) ) die( -1 );

/**
 * MonoBook nouveau
 *
 * Translated from gwicke's previous TAL template version to remove
 * dependency on PHPTAL.
 *
 * @todo document
 * @file
 * @ingroup Skins
 */

//SidebarOverride Line: 170
define('use_sidebars', true);

/**
 * Inherit main code from SkinTemplate, set the CSS and template filter.
 * @todo document
 * @ingroup Skins
 */
class SkinMonoBook extends SkinTemplate {
	/** Using monobook. */
	var $skinname = 'monobook', $stylename = 'monobook',
		$template = 'MonoBookTemplate', $useHeadElement = true;

	function setupSkinUserCss( OutputPage $out ) {
		global $wgHandheldStyle;

		parent::setupSkinUserCss( $out );
        
        //TODO: Add one Global Reset, Global Stylesheet
		$out->addStyle( 'monobook/reset.css', 'screen' );
		// Append to the default screen common & print styles...
		$out->addStyle( 'monobook/main.css', 'screen' );
		$out->addStyle( 'http://fonts.googleapis.com/css?family=Francois One');
		$out->addStyle( 'http://fonts.googleapis.com/css?family=Oswald');
		
		if( $wgHandheldStyle ) {
			// Currently in testing... try 'chick/main.css'
			//$out->addStyle( $wgHandheldStyle, 'handheld' );
		}

		//$out->addStyle( 'monobook/IE50Fixes.css', 'screen', 'lt IE 5.5000' );
		//$out->addStyle( 'monobook/IE55Fixes.css', 'screen', 'IE 5.5000' );
		//$out->addStyle( 'monobook/IE60Fixes.css', 'screen', 'IE 6' );
		//$out->addStyle( 'monobook/IE70Fixes.css', 'screen', 'IE 7' );

		//$out->addStyle( 'monobook/rtl.css', 'screen', '', 'rtl' ); 
	}
}

/**
 * @todo document
 * @ingroup Skins
 */
class MonoBookTemplate extends QuickTemplate {
	var $skin;
	/**
	 * Template filter callback for MonoBook skin.
	 * Takes an associative array of data set from a SkinTemplate-based
	 * class, and a wrapper for MediaWiki's localization database, and
	 * outputs a formatted page.
	 *
	 * @access private
	 */
	function execute() {
		global $wgRequest;

		$this->skin = $skin = $this->data['skin'];
		$action = $wgRequest->getText( 'action' );

		// Suppress warnings to prevent notices about missing indexes in $this->data
		wfSuppressWarnings();

		$this->html( 'headelement' );
?>
	<!-- Begin PageWrapper //-->
	<!--// TODO: remove all stupid divs -->
	<div id="globalWrapper" class="home blog two-sidebars">
		<div id="page">
			<div id="page-inner">
				<a id="navigation-top"></a>
				<div id="skip-to-nav"><a href="#navigation">Skip to Navigation</a></div>
<?php 
	//don't use this atm
	//Global Header from Wordpress on all Pages
	//require('path/to/wordpress/wp-blog-header.php');
	//get_header();
?>
				<!-- Begin Header //-->
				<div id="header">
					<div class="clearfix" id="header-inner">
						<div class="region region-header" id="header-blocks">
							<!-- Begin Widget TODO: remove this Crap, make real Header //-->
							<div class="widget-container widget_text logo" id="text-4">
								<div class="textwidget">
									<a href="/"><img alt="Dangerous Prototypes" src="http://dangerousprototypes.com/wp-content/themes/cwantwm-child/logo.png" /></a>
								</div>
							</div><!--//End Widget -->
							<!-- Begin Widget //-->
							<div class="widget-container widget_text banner" id="text-11">
								<div id="announce" class="textwidget"><?php include('/home/dp/www/announce/announce.php');?></div>
							</div><!--// End Widget -->
						</div><!--// End Region -->
					</div><!--// inner -->
				</div><!--// End Header -->
<?php 
	//dont use this atm
	//Global Navigation from Wordpress on all Pages
	//$args = array( matches theme args );
	//wp_nav_menu($args);
?>
				<!-- Begin TopNavigation //-->
				<!--// TODO: Add SideWide Global Navigation -->
				<div id="navbar">
					<div class="clear-block region region-navbar" id="navbar-inner">
						<a id="navigation" name="navigation"></a>
						<div class="menu-nav">
							<ul class="menu" id="menu-header-4">
								<li><a href="http://dangerousprototypes.com">Blog</a></li>
								<li><a href="http://dangerousprototypes.com/docs/Main_Page#Projects">Projects</a></li>
								<li><a href="http://dangerousprototypes.com/forum">Forum</a></li>
								<li><a href="http://dangerousprototypes.com/about">About</a></li>
								<li><a href="http://dangerousprototypes.com/contact">Contact</a></li>
								<li ><a href="http://www.seeedstudio.com/depot/wherelabs-m-9.html">Shop</a></li>
								<li><a href="http://dangerousprototypes.com/store/">Free PCBs</a></li>
							</ul>
						</div>
						<div class="widget-container widget_text social" id="text-10">
							<div class="textwidget">
								<a id="facebook" title="Visit our Facebook page" href="http://www.facebook.com/pages/Dangerous-Prototypes/127701397281222">Facebook</a>
								<a id="twitter" title="Follow us on twitter" href="http://twitter.com/#!/dangerousproto">Twitter</a>
								<a id="rss" title="Subscribe to rss feed" href="http://dangerousprototypes.com/feed">RSS</a>
								<a id="comrss" href="http://dangerousprototypes.com/comments/feed/" title="Subcribe to comments">Comments</a>
							</div>
						</div>
					</div>
				</div><!--// End TopNavigation -->
			
				<!-- Begin Main //-->
				<div id="main">
					<div class="clearfix with-navbar" id="main-inner">
						<div id="content">
							<div id="content-inner">
								<div id="content-area">
									<a id="top"></a>
									<!-- Begin Notices //-->
									<?php if($this->data['sitenotice']) { ?>
									<div id="siteNotice"><?php $this->html('sitenotice') ?></div>
									<?php } ?>
									<!--// End Notices -->
									<h1 id="firstHeading" class="firstHeading"><?php $this->html('title') ?></h1>
									<div id="bodyContent">
										<h3 id="siteSub"><?php $this->msg('tagline') ?></h3>
										<div id="contentSub"<?php $this->html('userlangattributes') ?>><?php $this->html('subtitle') ?></div>
										<?php if($this->data['undelete']) { ?>
										<div id="contentSub2"><?php $this->html('undelete') ?></div>
										<?php } ?><?php if($this->data['newtalk'] ) { ?>
										<div class="usermessage"><?php $this->html('newtalk')  ?></div>
										<?php } ?><?php if($this->data['showjumplinks']) { ?>
										<div id="jump-to-nav">
											<?php $this->msg('jumpto') ?>
											<a href="#column-one">
												<?php $this->msg('jumptonavigation') ?>
											</a>, <a href="#searchInput"><?php $this->msg('jumptosearch') ?></a>
										</div>
										<?php } ?>
										<!-- start content -->
										<?php $this->html('bodytext') ?>
										<?php if($this->data['catlinks']) { $this->html('catlinks'); } ?>
										<!-- end content -->
										<?php if($this->data['dataAfterContent']) { $this->html ('dataAfterContent'); } ?>
										<div class="visualClear"></div>
									</div><!--// End ContentBody -->
								</div><!--// End ContenArea -->
							</div><!--// inner -->
						</div><!--// End Content -->
						
						<?php if ( defined('use_sidebars') ): ?>
<?php
	//Don't use it atm
	//global Sidebars from Wordpress for all other Pages WIKI/Forum/ etc
	//No SIDEBARS in WIKI and Forum
	//get_sidebar('left');
?>
						<!--// TODO: Add Wiki Navigation to TopNav, remove Sidebars from Wiki -->
						<!-- Begin Sidebar left //-->
						<div id="sidebar-left">
							<div class="region region-left" id="sidebar-left-inner">
							<script type="<?php $this->text('jsmimetype') ?>"> if (window.isMSIE55) fixalpha(); </script>
							<?php
								$sidebar = $this->data['sidebar'];
								if ( !isset( $sidebar['SEARCH'] ) ) $sidebar['SEARCH'] = true;
								if ( !isset( $sidebar['TOOLBOX'] ) ) $sidebar['TOOLBOX'] = true;
								if ( !isset( $sidebar['LANGUAGES'] ) ) $sidebar['LANGUAGES'] = true;
								foreach ($sidebar as $boxName => $cont) {
									if ( $boxName == 'SEARCH' ) {
										$this->searchBox();
									} elseif ( $boxName == 'TOOLBOX' ) {
										$this->toolbox();
									} elseif ( $boxName == 'LANGUAGES' ) {
										$this->languageBox();
									} else {
										$this->customBox( $boxName, $cont );
									}
								}
							?>
							</div>
						</div><!--// End Sidebar left -->
<?php
	//Don't use it atm
	//global Sidebars from Wordpress for all other Pages WIKI/Forum/ etc
	//No SIDEBARS in WIKI and Forum	
	//get_sidebar('right');
?>			
						<!-- Begin Sidebar right //-->
						<div id="sidebar-right">
							<div class="region region-right" id="sidebar-right-inner">
								<div id="pcactions" class="portlet">
									<h5><?php $this->msg('views') ?></h5>
									<div class="pBody">
										<ul>
										<?php
											foreach($this->data['content_actions'] as $key => $tab) {
												echo '<li id="' . Sanitizer::escapeId( "ca-$key" ) . '"';
												if( $tab['class'] ) {
													echo ' class="'.htmlspecialchars($tab['class']).'"';
												}
												echo '><a href="'.htmlspecialchars($tab['href']).'"';
												# We don't want to give the watch tab an accesskey if the
												# page is being edited, because that conflicts with the
												# accesskey on the watch checkbox.  We also don't want to
												# give the edit tab an accesskey, because that's fairly su-
												# perfluous and conflicts with an accesskey (Ctrl-E) often
												# used for editing in Safari.
												if (
													in_array( $action, array( 'edit', 'submit' ) ) &&
													in_array( $key, array( 'edit', 'watch', 'unwatch' ))
													) 
												{
													echo $skin->tooltip( "ca-$key" );
												} else {
													echo $skin->tooltipAndAccesskey( "ca-$key" );
												}
												echo '>'.htmlspecialchars($tab['text']).'</a></li>';
											}
										?>
										</ul>
									</div>
								</div>
								<div class="portlet" >
									<h5><?php $this->msg('personaltools') ?></h5>
									<div class="pBody">
										<ul<?php $this->html('userlangattributes') ?>>
											<?php foreach($this->data['personal_urls'] as $key => $item) { ?>
											<li id="<?php echo Sanitizer::escapeId( "pt-$key" ) ?>"<?php
												if ($item['active']) { ?> class="active"<?php } ?>><a href="<?php
													echo htmlspecialchars($item['href']) ?>"<?php echo $skin->tooltipAndAccesskey('pt-'.$key) ?><?php
													if(!empty($item['class'])) { ?> class="<?php
													echo htmlspecialchars($item['class']) ?>"<?php } ?>><?php
													echo htmlspecialchars($item['text']) ?></a>
											</li>
											<?php } ?>
										</ul>
									</div>
								</div>
							</div>
						</div><!--// End Sidebar right -->
						<?php endif; //SideBar override ?>
					</div>
				</div><!--// End Main -->				
				<div id="push"></div>
			</div><!--// page-inner -->
		</div><!--// page -->
	</div><!--// End Global Wrapper -->
	
	<!--// TODO: Add real Clearfix -->
	<div class="visualClear"></div>
<?php
	//Don't use it atm
	//global Footer from Wordpress for all other Pages WIKI/Forum/ etc	
	//get_footer();
?>
	<!-- Begin Footer //-->
	<!--// TODO: Add SideWide Global Footer -->
	<div id="footer">
		<div class="region region-footer" id="footer-inner">
			<div class="widget-container widget_text contact" id="text-6">
				<h3 class="widget-title">Site</h3>
				<div class="textwidget">
				<?php
					// Generate additional footer links
					$footerlinks = array( 'lastmod', );
					$validFooterLinks = array();
					foreach( $footerlinks as $aLink ) {
						if( isset( $this->data[$aLink] ) && $this->data[$aLink] )
						{
							$validFooterLinks[] = $aLink;
						}
					}
					
					if( count( $validFooterLinks ) > 0 ) : ?>
					<ul id="f-list">
					<?php foreach( $validFooterLinks as $aLink ) : ?>
					<?php if( isset( $this->data[$aLink] ) && $this->data[$aLink] ) : ?>
						<li id="<?php echo $aLink ?>">
							<?php $this->html($aLink) ?>
						</li>
					<?php endif; endforeach; ?>
				 	</ul>
				 	<?php endif; // if(count..) ?>
					<br />
					Copyright 2011 Where Labs, LLC.<br />
					CC BY-SA unless otherwise noted.
				</div>
			</div>
			<div class="widget-container widget_text connect" id="text-7">
				<h3 class="widget-title">Connect</h3>
				<div class="textwidget">
					<ul>
						<li><a title="Follow us on twitter" href="http://twitter.com/#!/dangerousproto">Follow us on Twitter</a></li>
						<li><a href="http://dangerousprototypes.com/feed" title="Subscribe to rss feed">Subscribe to our feed</a></li>
						<li><a href="http://dangerousprototypes.com/comments/feed" title="Subcribe to comments">Subscribe to our comments</a></li>
						<li><a title="Visit our Facebook page" href="http://www.facebook.com/pages/Dangerous-Prototypes/127701397281222">Visit our Facebook page</a></li>
						<li><a href="http://dangerousprototypes.com/contact-us">Send us an email</a></li>
					</ul>
				</div>
			</div>
			<div class="widget-container widget_text projects" id="text-8">
				<h3 class="widget-title">Projects</h3>
				<div class="textwidget">
					<ul>
						<li><a title="Bus Blaster v2" href="http://www.seeedstudio.com/depot/bus-blaster-v2-jtag-debugger-p-807.html">Get a Bus Blaster v2</a></li>
						<li><a href="http://www.seeedstudio.com/depot/bus-pirate-v3-assembled-p-609.html?cPath=61_68">Get a Bus Pirate v3</a></li>
						<li><a href="http://www.seeedstudio.com/depot/flash-destroyer-eeprom-tester-p-630.html?cPath=61_68">Get a Flash Destroyer kit</a></li>
						<li><a href="http://www.seeedstudio.com/depot/preorder-open-workbench-logic-sniffer-p-612.html?cPath=75">Get a Logic Sniffer</a></li>
						<li><a href="http://www.seeedstudio.com/depot/usb-infrared-toy-v2-p-831.html?cPath=174">Get a USB Infrared Toy</a></li>
					</ul>
				</div>
			</div>
			<div class="widget-container widget_text about-us" id="text-9">
				<h3 class="widget-title">About Us</h3>
				<div class="textwidget">Our goal is to release a new open source hardware project every month.  Copies of our projects are available through Seeed Studio and our distributors.</div>
			</div>
		</div>
	</div><!--// End Footer -->
	<!-- Begin JavaScripts //-->
	<?php $this->html('bottomscripts'); /* JS call to runBodyOnloadHook */ ?>
	<!--// End JavaScripts -->
	<?php $this->html('reporttime') ?>
	<?php if ( $this->data['debug'] ): ?>
	<!-- Debug output:
		<?php $this->text( 'debug' ); ?>
	-->
	<?php endif; ?>
	</body>
</html>

<?php
		wfRestoreWarnings();
	} // end of execute() method
	
	/*************************************************************************************************/
	function searchBox() {
		global $wgUseTwoButtonsSearchForm;
		
		//TODO: Fix the label in H5
?>
	<!-- Begin Search //-->
	<div id="p-search" class="portlet">
		<h5><label for="searchInput"><?php $this->msg('search') ?></label></h5>
		<div id="searchBody" class="pBody">
			<form action="<?php $this->text('wgScript') ?>" id="searchform">
				<input type='hidden' name="title" value="<?php $this->text('searchtitle') ?>" />
				<?php
					echo Html::input( 'search',
						isset( $this->data['search'] ) ? $this->data['search'] : '', 'search',
						array(
							'id' => 'searchInput',
							'title' => $this->skin->titleAttrib( 'search' ),
							'accesskey' => $this->skin->accesskey( 'search' )
						)
					); 
				?>
				<input type="submit" name="go" class="searchButton" id="searchGoButton"	value="<?php $this->msg('searcharticle') ?>"<?php echo $this->skin->tooltipAndAccesskey( 'search-go' ); ?> />
				<?php if ($wgUseTwoButtonsSearchForm) : ?>
				&nbsp;
				<input type='submit' name="fulltext" class="searchButton" id="mw-searchButton" value="<?php $this->msg('searchbutton') ?>"<?php echo $this->skin->tooltipAndAccesskey( 'search-fulltext' ); ?> />
				<?php else : ?>
				<div><a href="<?php $this->text('searchaction') ?>" rel="search"><?php $this->msg('powersearch-legend') ?></a></div>
				<?php endif; ?>
			</form>
		</div>
	</div><!--// End Search -->
<?php
	} //end of searchbox function
	
	/*************************************************************************************************/
	function toolbox() {
?>
	<!-- Begin ToolBox //-->
	<div class="portlet" id="p-tb">
		<h5><?php $this->msg('toolbox') ?></h5>
		<div class="pBody">
			<ul>
			<?php
				if($this->data['notspecialpage']) : ?>
				<li id="t-whatlinkshere">
					<a href="<?php echo htmlspecialchars($this->data['nav_urls']['whatlinkshere']['href']) ?>"<?php echo $this->skin->tooltipAndAccesskey('t-whatlinkshere') ?>>
						<?php $this->msg('whatlinkshere') ?>
					</a>
				</li>
			<?php
				if( $this->data['nav_urls']['recentchangeslinked'] ) : ?>
				<li id="t-recentchangeslinked">
					<a href="<?php echo htmlspecialchars($this->data['nav_urls']['recentchangeslinked']['href']) ?>"<?php echo $this->skin->tooltipAndAccesskey('t-recentchangeslinked') ?>>
						<?php $this->msg('recentchangeslinked-toolbox') ?>
					</a>
				</li>
			<?php endif; endif; ?>
				
			<?php if( isset( $this->data['nav_urls']['trackbacklink'] ) && $this->data['nav_urls']['trackbacklink'] ) : ?>
				<li id="t-trackbacklink">
					<a href="<?php echo htmlspecialchars($this->data['nav_urls']['trackbacklink']['href']) ?>"<?php echo $this->skin->tooltipAndAccesskey('t-trackbacklink') ?>>
						<?php $this->msg('trackbacklink') ?>
					</a>
				</li>
			<?php endif; ?>
			
			<?php if($this->data['feeds']) : ?>
				<li id="feedlinks">
					<?php foreach($this->data['feeds'] as $key => $feed) : ?>
					<a id="<?php echo Sanitizer::escapeId( "feed-$key" ) ?>" href="<?php echo htmlspecialchars($feed['href']) ?>" rel="alternate" type="application/<?php echo $key ?>+xml" class="feedlink"<?php echo $this->skin->tooltipAndAccesskey('feed-'.$key) ?>><?php echo htmlspecialchars($feed['text'])?>
					</a>&nbsp;
					<?php endforeach; ?>
				</li>
			<?php endif; ?>
				
			<?php foreach( array('contributions', 'log', 'blockip', 'emailuser', 'upload', 'specialpages') as $special ) : ?>
				<?php if($this->data['nav_urls'][$special]) : ?>
				<li id="t-<?php echo $special ?>">
					<a href="<?php echo htmlspecialchars($this->data['nav_urls'][$special]['href']) ?>"<?php echo $this->skin->tooltipAndAccesskey('t-'.$special) ?>>
					<?php $this->msg($special) ?>
				 	</a>
				 </li>
			 <?php	endif; endforeach; ?>
				 
			 <?php if(!empty($this->data['nav_urls']['print']['href'])) : ?>
				 <li id="t-print">
				 	<a href="<?php echo htmlspecialchars($this->data['nav_urls']['print']['href']) ?>" rel="alternate"<?php echo $this->skin->tooltipAndAccesskey('t-print') ?>>
				 	<?php $this->msg('printableversion') ?>
				 	</a>
			 	</li>
		 	<?php endif; ?>
			 	
		 	<?php if(!empty($this->data['nav_urls']['permalink']['href'])) : ?>
			 	<li id="t-permalink">
				 	<a href="<?php echo htmlspecialchars($this->data['nav_urls']['permalink']['href']) ?>"<?php echo $this->skin->tooltipAndAccesskey('t-permalink') ?>>
					<?php $this->msg('permalink') ?>
					</a>
				</li>
			<?php elseif ($this->data['nav_urls']['permalink']['href'] === '') : ?>
				<li id="t-ispermalink"<?php echo $this->skin->tooltip('t-ispermalink') ?>>
					<?php $this->msg('permalink') ?>
				</li>
			<?php endif;
					
					wfRunHooks( 'MonoBookTemplateToolboxEnd', array( &$this ) );
					wfRunHooks( 'SkinTemplateToolboxEnd', array( &$this ) );
			?>
			</ul>
		</div>
	</div><!--// End Toolbox -->
	
<?php
	}//end of toolboxfunction

	/*************************************************************************************************/
	function languageBox() {
		if( $this->data['language_urls'] ) {
?>
	<!-- Begin LanguageBox //-->
	<div id="p-lang" class="portlet">
		<h5<?php $this->html('userlangattributes') ?>><?php $this->msg('otherlanguages') ?></h5>
		<div class="pBody">
			<ul>
				<?php foreach($this->data['language_urls'] as $langlink) : ?>
				<li class="<?php echo htmlspecialchars($langlink['class'])?>">
					<a href="<?php echo htmlspecialchars($langlink['href']) ?>"><?php echo $langlink['text'] ?></a>
				</li>
				<?php endforeach; ?>
			</ul>
		</div>
	</div><!--// End LanguageBox -->

<?php
	}
}//end of languagebox function

	/*************************************************************************************************/
	function customBox( $bar, $cont ) {
?>
	<!-- Begin CustomBox //-->
	<div class='generated-sidebar portlet' id='<?php echo Sanitizer::escapeId( "p-$bar" ) ?>'<?php echo $this->skin->tooltip('p-'.$bar) ?>>
		<h5><?php $out = wfMsg( $bar ); if (wfEmptyMsg($bar, $out)) echo htmlspecialchars($bar); else echo htmlspecialchars($out); ?></h5>
		<div class='pBody'>
		<?php if ( is_array( $cont ) ) : ?>
			<ul>
				<?php foreach($cont as $key => $val) : ?>
				<li id="<?php echo Sanitizer::escapeId($val['id']) ?>"<?php	if ( $val['active'] ) { ?> class="active" <?php } ?>>
					<a href="<?php echo htmlspecialchars($val['href']) ?>"<?php echo $this->skin->tooltipAndAccesskey($val['id']) ?>>
						<?php echo htmlspecialchars($val['text']) ?>
					</a>
				</li>
				<?php endforeach; ?>
			</ul>
		<?php else :
			# allow raw HTML block to be defined by extensions
			print $cont;
			endif;
		?>
		</div>
	</div><!--// End CustomBox -->

<?php
	} //end of custombox function
} // end of class
?>