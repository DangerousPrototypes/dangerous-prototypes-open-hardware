<?php

/**

 * Common Template - tpl_footer.php

 *

 * this file can be copied to /templates/your_template_dir/pagename<br />

 * example: to override the privacy page<br />

 * make a directory /templates/my_template/privacy<br />

 * copy /templates/templates_defaults/common/tpl_footer.php to /templates/my_template/privacy/tpl_footer.php<br />

 * to override the global settings and turn off the footer un-comment the following line:<br />

 * <br />

 * $flag_disable_footer = true;<br />

 *

 * @package templateSystem

 * @copyright Copyright 2003-2010 Zen Cart Development Team

 * @copyright Portions Copyright 2003 osCommerce

 * @license http://www.zen-cart.com/license/2_0.txt GNU Public License V2.0

 * @version $Id: tpl_footer.php 15511 2010-02-18 07:19:44Z drbyte $

 */

require(DIR_WS_MODULES . zen_get_module_directory('footer.php'));

?>
<?php

if (!isset($flag_disable_footer) || !$flag_disable_footer) {

?>
<!-- Piwik --> 
<script type="text/javascript">
var pkBaseURL = (("https:" == document.location.protocol) ? "https://dangerousprototypes.com/piwik/" : "http://dangerousprototypes.com/piwik/");
document.write(unescape("%3Cscript src='" + pkBaseURL + "piwik.js' type='text/javascript'%3E%3C/script%3E"));
</script><script type="text/javascript">
try {
  var piwikTracker = Piwik.getTracker(pkBaseURL + "piwik.php", 1);
  piwikTracker.trackPageView();
  piwikTracker.enableLinkTracking();
} catch( err ) {}
</script><noscript><p><img src="http://dangerousprototypes.com/piwik/piwik.php?idsite=1" style="border:0" alt="" /></p></noscript>
<!-- End Piwik Tracking Code -->
<div id="footer">
 <div class="region region-footer" id="footer-inner">
  <div class="widget-container widget_text contact" id="text-6">
   <h3 class="widget-title">Mobile site</h3>
   <div class="textwidget"><a onclick="document.cookie=&quot;wpmp_switcher=mobile;path=/;expires=Tue, 01-01-2030 00:00:00 GMT&quot;" href="?wpmp_switcher=mobile">Switch to our mobile site</a> <br>
    <br>
    <br>
    Copyright 2011 Where Labs, LLC.<br>
    CC BY-SA unless otherwise noted. </div>
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
</div>
<?php

} // flag_disable_footer

?>
