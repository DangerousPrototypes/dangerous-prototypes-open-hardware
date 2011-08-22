
/*
       Simple announcement banner rotator with impression and click tracking.

   Used for site-wide announcements at DangerousPrototypes.com
   Copyright (C) 2011 Where Labs, LLC (http://dangerousprototypes.com)
   Written by Vyacheslav V Sokolov

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see<http://www.gnu.org/licenses/>.

*/



//AJAX banner loader
//Set announce server location below:
//    var url = 'http://dangerousprototypes.com/announce/announce.php?ajax=1&t=' + now.getTime();
//USE example, add to the html/php/etc:
//    <div id="announce"></div><script type="text/javascript" src="announce.js"></script>
//
function makeHttpRequest(url, callback_function, return_xml)
{
   var http_request = false;

   if (window.XMLHttpRequest) { // Mozilla, Safari,...
       http_request = new XMLHttpRequest();
       if (http_request.overrideMimeType) {
           http_request.overrideMimeType('text/xml');
       }

   } else if (window.ActiveXObject) { // IE
       try {
           http_request = new ActiveXObject("Msxml2.XMLHTTP");
       } catch (e) {
           try {
               http_request = new ActiveXObject("Microsoft.XMLHTTP");
           } catch (e) {}
       }
   }

   if (!http_request) {
       //alert('Unfortunatelly you browser doesn\'t support this feature.');
       return false;
   }
   http_request.onreadystatechange = function() {
       if (http_request.readyState == 4) {
           if (http_request.status == 200) {
               if (return_xml) {
                   eval(callback_function + '(http_request.responseXML)');
               } else {
                   eval(callback_function + '(http_request.responseText)');
               }
           } else {
               //alert('There was a problem with the request.(Code: ' + http_request.status + ')');
           }
       }
   }
   http_request.open('GET', url, true);
   http_request.send(null);
}

function loadBanner(xml)
{
    var html_content = xml.getElementsByTagName('content').item(0).firstChild.nodeValue;
    document.getElementById('announce').innerHTML = html_content;
}

function getBanner()
{
    var now = new Date();
    var url = 'http://dangerousprototypes.com/announce/announce.php?ajax=1&t=' + now.getTime();
    makeHttpRequest(url, 'loadBanner', true);
}

try{
	//onload_functions.push('getBanner'); //phpBB3
	window.onload = getBanner();
	}catch(e){

	}