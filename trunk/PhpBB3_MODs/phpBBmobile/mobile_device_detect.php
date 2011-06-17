<?php
//License: Creative Commons 0 (public domain)
//Example code should be free, droid face!
//http://dangerousprototypes.com

//This is a replacement mobile browser detection script for the phpBBmobile theme
//The original is poorly coded and has a crap license attached
//Get the mobile theme here: http://phpbbacademy.com/community/viewtopic.php?f=39&t=5386#p60847
//This version DOES NOT support device reporting
//DO NOT do (or undo) the MOD edits to posting.php before using this replacement

//goal: get out of here as fast as possible, this code runs every time!
//Dont: use regular expressions. They're super slow!
//Dont: try to identify the phone, who cares?
//Do: use strpos - fastest php search method
//Do: try to identify desktops first! They are most of the hits!

//references
// mobile headers http://www.zytrax.com/tech/web/mobile_ids.html
// code inspiration: http://notnotmobile.appspot.com/
// code inspiration: http://www.russellbeattie.com/blog/mobile-browser-detection-in-php

//same as old phpBBmobile function for drop-in compatability
function mobile_device_detect(){

	//store the user agent, all lower case for fast matching without stri
	$a=strtolower($_SERVER['HTTP_USER_AGENT']);
	
	//reject any mobile that shouldn't get mobile app (ipad for us)
	if( (strpos($a, 'ipad') !== false) //exclude iPad from mobile
	){
		return false;
	}

	//don't get this header until we know we need it
	$accept=strtolower($_SERVER['HTTP_ACCEPT']);
	
	//get anything that will mess up the desktop detection. 
	//also most obvious stuff
	if( (strpos($a, 'android') !== false) //most popular OS as of 2011, also seen as desktop because of Linux in UA, filter it here
		|| (strpos($a, 'phone') !== false) //obvious mobile device, also gets iphone 2nd most popular in 2011
		|| (strpos($a, 'mobile') !== false) //obvious "I'm a mobile" in the user agent
		|| (strpos($a, 'windows ce') !== false) //look for windows CE now, will mess with windows desktop detection
		|| (strpos($a, 'palm') !== false) //some palms have Windows 98/etc agent strings, will mess with windows desktop detection
		|| (isset($_SERVER['HTTP_X_OPERAMINI_PHONE'])) //look for stupid opera HTTP_X header
		|| (strpos($accept, 'application/vnd.wap.xhtml+xml') !== false) //obvious "I'm a mobile app"
		|| (strpos($accept, 'text/vnd.wap.wml') !== false) //obvious "I'm a mobile app" 
	  ){
		return true;
	}

	//eleminate majority of desktop users first before doing more extensive search
	if( (strpos($a, 'windows') !== false)
		//|| (strpos($a, 'linux') !== false) //disabled because so many phones report Linux in UA, needs deeper check
		|| (strpos($a, 'solaris') !== false)
		|| (strpos($a, 'bsd') !== false)
		//|| (strpos($a, 'os/') !== false) //can't really do this with mac as far as I can tell
	){
		return false;
	}

	//now the big list of potential browser strings
	//hopefully we never get here 99% of the time
	//should be ordered from most common to least common
	if( (strpos($a, ' mobi') !== false)
		//|| (strpos($a, 'iphone') !== false) //generic phone check takes care of this
		//|| (strpos($a, 'ipad') !== false) //dont want to use mobile on ipad, generic mobile check takes care of this too
		|| (strpos($a, 'wireless') !== false) 
		|| (strpos($a, 'blackberry') !== false) 	
		|| (strpos($a, 'opera mini') !== false) 
		|| (strpos($a, 'symbian') !== false) 
		|| (strpos($a, 'nokia') !== false) 
		|| (strpos($a, 'samsung') !== false) 
		|| (strpos($a, 'ericsson,') !== false) 	
		|| (strpos($a, 'vodafone/') !== false)
		|| (strpos($a, 'kindle') !== false) 
		|| (strpos($a, 'ipod') !== false) 
		|| (strpos($a, 'wap1.') !== false)
		|| (strpos($a, 'wap2.') !== false)
		|| (strpos($a, 'sony') !== false)
		|| (strpos($a, 'sanyo') !== false)
		|| (strpos($a, 'sharp') !== false)
		|| (strpos($a, 'panasonic') !== false)
		|| (strpos($a, 'philips') !== false)
		|| (strpos($a, 'pocketpc') !== false)
		|| (strpos($a, 'avantgo') !== false) //are these people still around? Really? I had that on my palm III
		|| (strpos($a, 'blazer') !== false)			
		|| (strpos($a, 'ipaq') !== false)	
		|| isset($_SERVER['HTTP_X_WAP_PROFILE']) //older headers
		|| isset($_SERVER['HTTP_PROFILE']) //older headers
	){
		return true;
	}

	//nothing matched, assume desktop and not mobile
	return false;
}
?>