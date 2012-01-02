<?php

/**

 * Common Template - tpl_header.php

 *

 * this file can be copied to /templates/your_template_dir/pagename<br />

 * example: to override the privacy page<br />

 * make a directory /templates/my_template/privacy<br />

 * copy /templates/templates_defaults/common/tpl_footer.php to /templates/my_template/privacy/tpl_header.php<br />

 * to override the global settings and turn off the footer un-comment the following line:<br />

 * <br />

 * $flag_disable_header = true;<br />

 *

 * @package templateSystem

 * @copyright Copyright 2003-2006 Zen Cart Development Team

 * @copyright Portions Copyright 2003 osCommerce

 * @license http://www.zen-cart.com/license/2_0.txt GNU Public License V2.0

 * @version $Id: tpl_header.php 4813 2006-10-23 02:13:53Z drbyte $

 */

?>
<?php

  // Display all header alerts via messageStack:

  if ($messageStack->size('header') > 0) {

    echo $messageStack->output('header');

  }

  if (isset($_GET['error_message']) && zen_not_null($_GET['error_message'])) {

  echo htmlspecialchars(urldecode($_GET['error_message']));

  }

  if (isset($_GET['info_message']) && zen_not_null($_GET['info_message'])) {

   echo htmlspecialchars($_GET['info_message']);

} else {



}

?>
<!--bof-header logo and navigation display-->
<?php

if (!isset($flag_disable_header) || !$flag_disable_header) {

?>
<div id="header">
 <div class="clearfix" id="header-inner">
  <div class="region region-header" id="header-blocks">
   <div class="widget-container widget_text logo" id="text-4">
    <div class="textwidget"><a href="/"><img alt="Dangerous Prototypes" src="http://dangerousprototypes.com/theme/logo.png"></a></div>
   </div>
   <div class="widget-container widget_text banner" id="text-11">
    <div id="announce" class="textwidget"><?php include('/home/dp/webroot/announce/announce.php');?></div>
   </div>
  </div>
 </div>
</div>
<div id="navbar">
 <div class="clear-block region region-navbar" id="navbar-inner"> <a id="navigation" name="navigation"></a>
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
   <div class="textwidget"><a id="facebook" title="Visit our Facebook page" href="http://www.facebook.com/pages/Dangerous-Prototypes/127701397281222">Facebook</a><a id="twitter" title="Follow us on twitter" href="http://twitter.com/#!/dangerousproto">Twitter</a><a id="rss" title="Subscribe to rss feed" href="http://dangerousprototypes.com/feed">RSS</a><a id="comrss" href="http://dangerousprototypes.com/comments/feed/" title="Subcribe to comments">Comments</a></div>
  </div>
 </div>
</div>
<?php } ?>
