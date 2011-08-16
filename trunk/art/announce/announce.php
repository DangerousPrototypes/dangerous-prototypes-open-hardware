<?php
$bannerAd[1] = array("image"=>"OHS2011.jpg","url"=>"http://dangerousprototypes.com/2011/08/16/fast-forward-from-alpha-agile-open-hardware-manufacturing/");
$bannerAd[2] = array("image"=>"MFNY2011.png","url"=>"http://dangerousprototypes.com/2011/08/08/maker-faire-new-york-2011/");

$base='http://dangerousprototypes.com/announce/';

// pick a random one
$pick = $bannerAd[array_rand($bannerAd)];
$banner='<a href="'.$pick["url"].'"><img src="'.$base.$pick["image"].'"/></a>';

if(!isset($_GET['ajax'])){
	echo $banner;
}else{
	// send XML headers
	header('Content-type: text/xml');
	echo '<?xml version="1.0" ?>';
	// print the XML response
?>
<banner>
    <content><?php echo htmlentities($banner); ?></content>
</banner>
<?php
}
?>