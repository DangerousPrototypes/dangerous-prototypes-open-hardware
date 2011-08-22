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


bannerList = new Array();

showAddBanner = function() {
	document.forms.newBanner.style.display = 'block';
	document.getElementById( 'bAdd' ).disabled = true;
};

hideAddBanner = function() {
	document.forms.newBanner.style.display = 'none';
	document.getElementById( 'bAdd' ).disabled = false;
};

addBannerSubmit = function() {
	var form = document.forms.newBanner;
	var err = document.getElementById( 'addError' );
	
	var error = function( e ) {
		err.innerHTML = e;
		err.style.display = '';
		return false;
	}
	
	if( form.url.value.trim() == '' )
		return error( 'URL cannot be empty' );
	
	var rex = /\d{4}-\d{2}-\d{2}/;
	
	var checkDate = function ( dt ) {
		return dt != '' && ( ! rex.test( dt ) || isNaN( Date.parse( dt ) ) );
	}
	
	if( checkDate( form.start_date.value ) || checkDate( form.end_date.value ) )
		return error( 'Invalid date' );
	
	if( form.image.value.trim() == '' )
		return error( 'Please provide an image' );
	
	return true;
};

addBannerReset = function() {
	hideAddBanner();
	return false;
};

selectAll = function() {
	for( var i = 0; i < bannerList.length; ++ i )
		document.getElementById( 'checkBox' + i ).checked = true;
};

selectNone = function() {
	for( var i = 0; i < bannerList.length; ++ i )
		document.getElementById( 'checkBox' + i ).checked = false;
};

selectExpired = function() {
	for( var i = 0; i < bannerList.length; ++ i ) {
		var dt = bannerList[ i ].dtEnd;
		if( ! isNaN( dt ) && dt < new Date() )
			document.getElementById( 'checkBox' + i ).checked = true;
	}
};

changeData = function( n ) {
	document.forms[ 'change' + n ].style.display = 'block';
	document.getElementById( 'btChange' + n ).disabled = true;
};

changeReset = function( n ) {
	document.forms[ 'change' + n ].style.display = 'none';
	document.getElementById( 'btChange' + n ).disabled = false;
	return false;
};

changeImage = function( n ) {
	document.forms[ 'upload' + n ].style.display = 'block';
	document.getElementById( 'btUpload' + n ).disabled = true;
};

uploadReset = function( n ) {
	document.forms[ 'upload' + n ].style.display = 'none';
	document.getElementById( 'btUpload' + n ).disabled = false;
	return false;
};

uploadSubmit = function( n ) {
	var form = document.forms[ 'upload' + n ];
	var err = document.getElementById( 'uploadErr' + n );

	var error = function( e ) {
		err.innerHTML = e;
		err.style.display = '';
		return false;
	}
	
	if( form.image.value.trim() == '' )
		return error( 'Please provide an image' );
	
	return true;
};

changeSubmit = function( n ) {
	var form = document.forms[ 'change' + n ];
	var err = document.getElementById( 'changeErr' + n );

	var error = function( e ) {
		err.innerHTML = e;
		err.style.display = '';
		return false;
	}
	
	if( form.url.value.trim() == '' )
		return error( 'URL cannot be empty' );
	
	var rex = /\d{4}-\d{2}-\d{2}/;
	
	var checkDate = function ( dt ) {
		return dt != '' && ( ! rex.test( dt ) || isNaN( Date.parse( dt ) ) );
	}
	
	if( checkDate( form.start_date.value ) || checkDate( form.end_date.value ) )
		return error( 'Invalid date' );
	
	return true;
};

deleteSelected = function() {
	var text='';
	var n = 0;
	for( var i = 0; i < bannerList.length; ++ i )
		if( document.getElementById( 'checkBox' + i ).checked )
			text += '<input type="hidden" name="id[' + n ++ + ']" value="' + bannerList[ i ].id + '" />';
	if( text != '' ) {
		document.forms.deleter.innerHTML = text;
		document.forms.deleter.submit();
	}
};


