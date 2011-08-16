<?php

/*
$Id: footer.php 195195 2010-01-19 04:11:37Z BAAP $

$URL: http://plugins.svn.wordpress.org/baap-mobile-version/trunk/themes/mobile_pack_base/footer.php $

Copyright (c) 2009 BAAP, portions mTLD Top Level Domain Limited, BAAP, Forum Nokia

Online support: http://wordpress.org/extend/plugins/baap-mobile-version/

This file is part of the BAAP Mobile Version.

The BAAP Mobile Version is Licensed under the Apache License, Version 2.0
(the "License"); you may not use this file except in compliance with the
License.

You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
*/

?>

      <div id="footer">
        <?php
          if (file_exists($wpmp_include = wpmp_theme_group_file('footer.php'))) {
            include_once($wpmp_include);
          } else {
            ?>
              <p><a onclick="document.cookie=&quot;wpmp_switcher=desktop;path=/;expires=Tue, 01-01-2030 00:00:00 GMT&quot;" href="?wpmp_switcher=desktop">Switch to our desktop site</a></p>
            <?php
          }
        ?>
        <?php wp_footer(); ?>
      </div>
    </div>
  </body>
</html>