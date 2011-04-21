<?php
/**
*
* functions_link_filter.php version r753
* @license http://opensource.org/licenses/gpl-license.php GNU Public License
* Modified by Ian Lesnet (http://dangerousprototypes.com)
* Documentation and install info here: 
*  http://dangerousprototypes.com/docs/PhpBB3_MOD:_Disable_links_for_new_users
*
*/

/**
* @ignore
*/
if (!defined('IN_PHPBB'))
{
   exit;
}

class link_filter{

	//--settings variables--//
	// An array of no-nos. Add whatever you need...
	private $no_link_strings=array();//('http://', 'www.', '.com', '.net', '.org', '.uk', '.ly', '.me', '.ru', '.biz', '.info', 'dot com', 'dot net', 'dot org', 'dotcom', 'dotnet', 'dotorg', '_com', '_org', '_co_uk', '_ru', 'dot ru');

	//a secondary spam words filter
	private $no_word_strings=array();
   
	private $show_trigger_word=true; //show the user the word that triggered the error
	
	//URLS to ALLOW always. In additon to own-site urls
	private $whitelist_urls=array('http://code.google.com', 'http://sourceforge.net',);
	
	//a regex to filter a unicode character range. 
	//Will throw an error if any of these characters are included in a post. 
	//leave blank to disable this feature
	//for unicode blocks see: http://www.fileformat.info/info/unicode/block/index.htm
	//0400-04FF - Cyrillic (Russian)
	//0600-06FF - Arabic
	//3100-312F - Mandarin Bopomofo block
	//example of chaining together: '/([\x{0400}-\x{04FF}]|[\x{0600}-\x{06FF}])+/u';
	private $unicode_filter='/([\x{0400}-\x{04FF}]|[\x{0600}-\x{06FF}])+/u';
	
	//what percentage of the post must be non-unicode character (mosly useful for english language sites)
	//leave blank to disable this feature
	private $minimum_nonunicode_text=0.95; //percent of post that must be non-unicode
	
	//where can the user get more help about the filter? Could be a forum post or web page
	//if blank the link will NOT be added to the error messages
	//leave blank to no use this features
	private $help_url = 'http://dangerousprototypes.com/forum/viewtopic.php?f=2&t=1846&p=17886#p17886';
	
	private $load_values_from_db=true; //enable to use with DB, or use the values below
	private $minimum_days=1; //minimum days as member to post links
	private $minimum_posts=1; //minimum posts for member to post links
	
	private $sleeper_check=true; //users with 0 posts who try to post after minimum_days will be prohibited
	
	private $first_post_length=73;//a minimum characters for the first post. enter 0 to disable
	
	private $log_activity=false;//log entry for all activity (not recomended)
	
	private $extreme=false; //deletes accounts for profile abuse
	private $extreme_links_delete=9;
	private $kill=false;
	//-- Reporting variables--//
	public $filter_user=false; //we decided to filter this user (they met our criteria)
	
	public $found_stuff=false; //did we find anything? (any item below)
	public $found_sleeper=false;//did we determine this user to be a sleeper agent?
	public $found_links=false; //we found links
	public $found_words=false;//we found bad words
	public $found_minwords=false;//we found too few words
	public $found_unicode=false;//found unicode
	public $found_profile=false;//profiles not allow check positive (for log)
	public $error=array(); //holds text error array

	/*
	*	Log filter actions
	*
	*/
	function link_add_log($type,$no_link_message){
		global $user;

		$l='CHECKED '.$type.' of \''.$user->data['username'].'\'. ';
		if($this->found_stuff){
			$l.='DETECTED: ';
			if($this->found_sleeper)$l.='sleeper agent, ';
			if($this->found_links)$l.='links, ';
			if($this->found_words)$l.='bad words, ';
			if($this->found_minwords)$l.='too few words, ';
			if($this->found_unicode)$l.='unicode, ';
			if($this->found_profile)$l.='profile disabled, ';
			$l.='ERRORS: '.implode(', ', $this->error);
			if(!empty($no_link_message)) $l.=' CONTENTS: '.$no_link_message;  
		}else{
			$l.='OK';
		}
		add_log('user', 'LOG_SPAM_HAMMER', 'spam hammer: '.$l);
	}
	
/**
*  Test if user can have a profile yet
*  returns false if they do NOT need to be filtered
*/
function link_filter_test_profile($abuse=false){
	global $user;
	
	//do we need to check this user?
	if(!$this->link_filter_check()) return false; //don't check, no error
	
	if($this->load_values_from_db) $this->link_filter_load_list_from_db(); //load list values from DB if configured	
	
	if(!$this->link_filter_sleeper_check()){ //if it is a sleeper agent just return error, don;t do the check
		$this->found_stuff=$this->found_profile=true;			
		//If there isn't a phpbb3 no_link message add one
		if (empty($user->lang['NO_LINK_FOR_YOU'])){
			$user->lang['NO_PROFILE_FOR_YOU']='Antispam: You can\'t have a profile yet. You need to post a few times first.';
			//$user->lang['NO_PROFILE_FOR_YOU']='Antispam: DO NOT update the profile yet, you will be DELETED! You need to post a few times first.';
		}
		
		$this->error[]=$user->lang['NO_PROFILE_FOR_YOU'].' '.$this->link_filter_add_help_link();
	}
	if($abuse && $this->extreme && ($user->data['user_posts']==0)){
		add_log('admin', 'LOG_SPAM_HAMMER', 'spam hammer: DELETED '.$user->data['username'].' for profile abuse.');
		add_log('user', 'LOG_SPAM_HAMMER', 'spam hammer: DELETED '.$user->data['username'].' for profile abuse.');
		$this->link_filter_delete_account($user->data['user_id']);
		//$this->error[]='Antispam: Sorry, this account was DELETED due to suspicious behavior.'; 
		trigger_error('Antispam: Sorry, this account was DELETED due to suspicious behavior. New users are NOT allowed to post a profile.');
	}else{
		if($this->log_activity) $this->link_add_log('PROFILE','');
	}	
	return true;
}	

/**
*  Test a submitted signature for links and words
*  Returns true if bad things detected
*/
function link_filter_test_signature($signature){
	global $user;

	//do we need to check this user?
	if(!$this->link_filter_check()) return false; //don't check, no error
	
	if($this->load_values_from_db) $this->link_filter_load_list_from_db(); //load list values from DB if configured	
	
	if($this->link_filter_sleeper_check()){
		if($this->log_activity) $this->link_add_log('SIGNATURE',$signature);
		return true; //if it is a sleeper agent just return error, don;t do the check
	}
	
	//If there isn't a phpbb3 no_link message add one
	if (empty($user->lang['NO_LINK_FOR_YOU'])){
		$user->lang['NO_LINK_FOR_YOU']='Antispam: You can\'t have off-site URLs in your sig until you post a few times. ';
	}
	//If there isn't a phpbb3 no_word message add one
	if (empty($user->lang['NO_WORD_FOR_YOU'])){
		$user->lang['NO_WORD_FOR_YOU']='Do you kiss your mom with that mouth? We don\'t want to read that! ';
	}
	
	//make a version of the post and subject
	//need the trailing space or it can hang forever in the while loop if only using a local URL
	$res=$this->link_filter_test(' '.trim($signature).' ');

	if($res && $this->extreme && ($user->data['user_posts']==0)){
		add_log('admin', 'LOG_SPAM_HAMMER', 'spam hammer: DELETED '.$user->data['username'].' for signature abuse.');
		add_log('user', 'LOG_SPAM_HAMMER', 'spam hammer: DELETED '.$user->data['username'].' for signature abuse. CONTENTS:'.$signature);
		$this->link_filter_delete_account($user->data['user_id']);
		//$this->error[]='Antispam: Sorry, this account was DELETED due to suspicious behavior.'; 
		trigger_error('Antispam: Sorry, this account was DELETED due to suspicious behavior.');
	}else{
		if($this->log_activity) $this->link_add_log('SIGNATURE',$signature);
	}
	
	return $res;
	
}

/**
*  Test a submitted post for links and words
*  Returns true if bad things detected
*/
function link_filter_test_post($message, $subject){
	global $user;
	
	//do we need to check this user?
	if(!$this->link_filter_check()) return false; //don't check, no error
	
	//need to do this here or we don;t get the site's unique help URL
	//better to do it here and then again below that do it for every user before the check
	if($this->load_values_from_db) $this->link_filter_load_list_from_db(); //load list values from DB if configured	
	
	if( (($user->data['user_posts']==0)||($user->data['user_type']==USER_IGNORE)||($user->data['user_id']==ANONYMOUS))&& (strlen($message)<$this->first_post_length)){//first post, check length
		
		//If there isn't a phpbb3 message add one
		if (empty($user->lang['NO_LINK_TOO_SHORT'])){
			$user->lang['NO_LINK_TOO_SHORT']='Antispam: Sorry, your first post needs to be just a little longer.';
		}
		$this->error[]=$user->lang['NO_LINK_TOO_SHORT'].' '.$this->link_filter_add_help_link();
		$this->found_stuff=$this->found_minwords=true; //flag the error
		
		if($this->log_activity) $this->link_add_log('POST',$subject.''.$message);
		
		return true;
	}
	
	if($this->link_filter_sleeper_check()){
		if($this->log_activity) $this->link_add_log('POST',$subject.''.$message);
		return true; //if it is a sleeper agent just return error, don;t do the check
	}

	//If there isn't a phpbb3 no_link message add one
	if (empty($user->lang['NO_LINK_FOR_YOU'])){
		$user->lang['NO_LINK_FOR_YOU']='Your post looks too spamy for a new user, please remove off-site URLs.';
	}
	//If there isn't a phpbb3 no_word message add one
	if (empty($user->lang['NO_WORD_FOR_YOU'])){
		$user->lang['NO_WORD_FOR_YOU']='Your post looks too spamy for a new user, please remove bad words or non-english text.';
	}
	
	//make a version of the post and subject
	$res=$this->link_filter_test(' '.trim($message.' '.$subject).' ');
	
	//if($this->log_activity) $this->link_add_log('POST',$subject.''.$message);

	if( ($res && $this->extreme && ($user->data['user_posts']==0)) && ($this->kill || $this->found_unicode) ){//if extreme mode, delete the user
			global $phpbb_root_path,$phpEx;
			add_log('admin', 'LOG_SPAM_HAMMER', 'spam hammer: DELETED '.$user->data['username'].' for post abuse.');
			add_log('user', 'LOG_SPAM_HAMMER', 'spam hammer: DELETED '.$user->data['username'].' for post abuse. CONTENT: '.$subject.''.$message);
			include($phpbb_root_path . 'includes/functions_user.' . $phpEx);
			$this->link_filter_delete_account($user->data['user_id']);
			$this->error[]='Antispam: Sorry, this account was DELETED due to suspicious behavior.'; 
			//trigger_error('Antispam: Sorry, this account was DELETED due to suspicious behavior.');
	}else{
		if($this->log_activity) $this->link_add_log('POST',$subject.''.$message);
	}
	
	return $res;	
}

/**
*  Test a submitted PM for links and words
*  Returns true if bad things detected
*/
function link_filter_test_pm($message, $subject){
	global $user;
	
	//do we need to check this user?
	if(!$this->link_filter_check()) return false; //don't check, no error
	
	//if($this->found_sleeper) return true; //if it is a sleeper agent we still allow PMs to contact an admin, but we still filter them

	if($this->load_values_from_db) $this->link_filter_load_list_from_db(); //load list values from DB if configured	

	//If there isn't a phpbb3 no_link message add one
	if (empty($user->lang['NO_LINK_FOR_YOU'])){
		$user->lang['NO_LINK_FOR_YOU']='Your message looks too spamy for a new user, please remove off-site URLs.';
	}
	//If there isn't a phpbb3 no_word message add one
	if (empty($user->lang['NO_WORD_FOR_YOU'])){
		$user->lang['NO_WORD_FOR_YOU']='Your message looks too spamy for a new user, please remove bad words or non-english text.';
	}
	
	//make a version of the post and subject
	$res=$this->link_filter_test(' '.trim($message.' '.$subject).' ');
	
	if($this->log_activity) $this->link_add_log('PM',$subject.''.$message);
	
	return $res;	
	
}

/**
* 	Do we need to check this user?
* 
*/
function link_filter_check()
{
	global $user, $config;

	if($this->load_values_from_db){ //use MOD setting from database
		$this->minimum_days=$config['links_after_num_days'];
		$this->minimum_posts=$config['links_after_num_posts'];
		if($config['links_disable_sleepers']=='1'){
			$this->sleeper_check=true;
		}else{
			$this->sleeper_check=false;
		}
	}

	//check if the user meets filter criteria
	$this->filter_user=((!$user->data['session_admin']) && (($user->data['user_type']==USER_IGNORE) || ($user->data['user_id']==ANONYMOUS) || ($user->data['user_posts']<=($this->minimum_posts-1)) || ($user->data['user_regdate']>((time())-(86400*$this->minimum_days)))));

	//this MIGHT be used in a bigger filter to only apply to new users.
	//$this->filter_user=((!$user->data['session_admin']) && (($user->data['user_type']==USER_IGNORE) || ($user->data['user_id']==ANONYMOUS) || ($user->data['user_new']==1 &&(($user->data['user_posts']<=($this->minimum_posts-1)) || ($user->data['user_regdate']>((time())-(86400*$this->minimum_days)))))));
	
	//If you're not special, we filter you
	return $this->filter_user;
}

/**
* 	check for spammers who come back later and  try to post (sleeper agents, or aged accounts)
* 
*/
function link_filter_sleeper_check(){
	global $user;
	
	//check for spammers who come back later and  try to post (sleeper agents, or aged accounts)
	if(($this->sleeper_check) && ($user->data['user_id']!=ANONYMOUS) && ($user->data['user_posts']==0) && ($user->data['user_regdate']<=((time())-(86400*$this->minimum_days)))){
		$this->found_sleeper=$this->found_stuff=true;
		
		//If there isn't a phpbb3 sleeper agent message add one
		if (empty($user->lang['NO_SLEEPER_SPAM_FOR_YOU'])){
			$user->lang['NO_SLEEPER_SPAM_FOR_YOU']='Antispam: account disabled, please contact an admin.';
			//could delete the user automatically here
		}
		$this->error[]=$user->lang['NO_SLEEPER_SPAM_FOR_YOU'].' '.$this->link_filter_add_help_link();
		return true;
	}
	return false;
}

/**
* 	Add a help link if it exists
*  
*/
function link_filter_add_help_link(){
	if(!empty($this->help_url)){
	
		//If there isn't a phpbb3 message add one
		if (empty($user->lang['HELP_LINK'])){
			$user->lang['HELP_LINK']='Click for help';
		}
		
		return '<a href="'.$this->help_url.'">'.$user->lang['HELP_LINK'].'</a>.';
	}
}

/**
* 	if database is enabled this will explore the filter lists into the arrays
*  We move it here so this only happen when we need to filter the user
*/
function link_filter_load_list_from_db(){
	global $config;
	//use MOD setting from database
	$this->whitelist_urls=explode(",", $config['links_allow_always']);
	$this->no_link_strings=explode(",", $config['links_link_strings']);
	$this->no_word_strings=explode(",", $config['links_word_strings']);		
	$this->whitelist_urls=explode(",", $config['links_allow_always']);		
	$this->unicode_filter=$config['links_unicode_filter'];
	$this->minimum_nonunicode_text=(float)$config['links_nonunicode_percent'];
	$this->help_url = $config['links_help_url'];
	$this->first_post_length=$config['links_first_post_words'];
	if($config['links_log_activity']=='1'){
		$this->log_activity=true;
	}else{
		$this->log_activity=false;		
	}
}

/**
* 	Search the text for forbidden URLs and text. 
*	Add an error to the local error array if found
*	returns true for bad stuff, false for no flags found
* 
*/
function link_filter_test($no_link_message){
	global $user, $config;

	//filter the looozers
	//remove line feeds and stuff
	$no_link_message=str_replace('\n', ' ',$no_link_message);
	$no_link_message=str_replace('\r', ' ', $no_link_message);
	//replace double spaces with single spaces (not sure why, white space?)
	while (strpos($no_link_message, '  ')){
		$no_link_message=str_replace('  ', ' ', $no_link_message);
	}

	//whitelist other common domains
	//we do this by relacing them with our own domain so we only have to run the search once below
	for ($x=0;$x<sizeof($this->whitelist_urls);$x++){
		if(stripos($no_link_message, $this->whitelist_urls[$x])){
			$no_link_message=str_ireplace($this->whitelist_urls[$x], $config['server_name'], $no_link_message);	
		}
	}	

	//remove any own-site references, these are ok
	//first change http://mysite.com to mysite.com so we only have to look once below
	$no_link_message=str_replace($config['server_protocol'].$config['server_name'], $config['server_name'], $no_link_message);
	
	//look at all instances of mysite.com
	while ($ok_start=stripos($no_link_message, $config['server_name'])){ //start of mysite.com
		$ok_end=strpos($no_link_message, '[', $ok_start); //find next [ (bbcode?)
		if (!$ok_end){ //if not bbcode
			$ok_end=strpos($no_link_message, ' ', $ok_start); //end is position of next space
		}
		if ($ok_end){
			$no_link_message=substr($no_link_message, 0, $ok_start).substr($no_link_message, $ok_end);//remove own URL
		}
	}
		

	//search for each link element, throw an error when found
	for ($x=0;$x<sizeof($this->no_link_strings);$x++){
		if (stripos($no_link_message, $this->no_link_strings[$x])){
			
			$this->found_links=$this->found_stuff=true;
			
			if($this->extreme && ($user->data['user_posts']==0) && (substr_count($no_link_message, 'http://')>$this->extreme_links_delete)){
				$this->kill=true;
			}
						
			$this->error[]=$user->lang['NO_LINK_FOR_YOU'].' '.$this->link_filter_add_help_link();
			
			//$x=sizeof($no_link_strings);
			//break;//no reason to go further
			return true;
		}
	}
	
	//search each word, throw an error when found
	for ($x=0;$x<sizeof($this->no_word_strings);$x++){
		if (stripos($no_link_message, $this->no_word_strings[$x])){
		
			$this->found_words=$this->found_stuff=true;
		
			if($this->show_trigger_word){//show the cause so the user isn't stumped 
				$this->error[]=$user->lang['NO_WORD_FOR_YOU'].' ('.$this->no_word_strings[$x].') '.$this->link_filter_add_help_link();
			}else{//don't show the cause
				$this->error[]=$user->lang['NO_WORD_FOR_YOU'].' '.$this->link_filter_add_help_link();
			}
			
			//$x=sizeof($no_link_strings);
			//break;//no reason to search further
			return true;
		}
	}
	
	//if($this->found_stuff==true) return true; //don't continue checking below
	
	//make a smaller subset for preg_match to save time and cycles
	if(strlen($no_link_message) > 512){
		$no_link_message = substr($no_link_message, 0, 512);
	}
	
	//Check for unicode characters that don't belong in the language of this forum	
	if(!empty($this->unicode_filter)){
		if(preg_match($this->unicode_filter, $no_link_message, $m)==1){ //test for unicode character ranged defined by user
		
			$this->found_unicode=$this->found_stuff=true;

			$this->error[]=$user->lang['NO_WORD_FOR_YOU'].' '.$this->link_filter_add_help_link();
			
			return true; //don't continue checking below
		}
	}
	
	//check the percentage of the text that is NOT unicode
	//see http://www.mawhorter.net/web-development/easily-detecting-if-a-block-of-text-is-written-in-english-non-unicode-languages
	if((!empty($this->minimum_nonunicode_text))){

		//found the length in unicode mode
		$ulen = preg_match_all("#.#u", $no_link_message, $m);
		//find length without unicode
		$len  = preg_match_all('#.#', $no_link_message, $m);
		
		//determine if % of non-unicode is enough
		if(($ulen/$len)<(float)$this->minimum_nonunicode_text){
			$this->found_unicode=$this->found_stuff=true;
			$this->error[]=$user->lang['NO_WORD_FOR_YOU'].' ('.$ulen.'/'.$len.') '.$this->link_filter_add_help_link();
		}	
	}

	return $this->found_stuff;

}

//deletes a single account based on user id
function link_filter_delete_account($id){
		global $db, $user;
		
		if(($user->data['user_type']==USER_IGNORE)||($user->data['user_id']==ANONYMOUS)) return; //don't delete anon user
		
		// Get bot ids
		$sql = 'SELECT user_id
			FROM ' . BOTS_TABLE;
		$result = $db->sql_query($sql);

		$bot_ids = array();
		while ($row = $db->sql_fetchrow($result))
		{
			$bot_ids[] = $row['user_id'];
		}
		$db->sql_freeresult($result);

		// Do not prune bots and the user currently pruning.
		if (!in_array($id, $bot_ids))
		{
			user_delete('remove', $id);//delete the user and all posts (there should be none though)
		}
}

//purges all accounts with 0 posts older than $config['links_delete_zombies_days']
function link_filter_purge_zombies(){
	global $db, $config;
	
	if($this->load_values_from_db){ //use MOD setting from database
		if($config['links_delete_zombies']!='1'){
			if($config['links_log_activity']=='1'){
				add_log('admin', 'LOG_PRUNE_USER_DEL_DEL', 'spam hammer zombie cleanup: Disabled!');
			}
			return; //honor ACP setting
		}
		
		$this->minimum_days=$config['links_delete_zombies_days']; //$config['links_after_num_days'];
	}
	
	if($this->minimum_days<1){
		add_log('admin', 'LOG_PRUNE_USER_DEL_DEL', 'spam hammer zombie cleanup: ERROR - days set to 0!');
		return; //don't delete if there is no days setting
	}

	// Get bot ids
	$sql = 'SELECT user_id
		FROM ' . BOTS_TABLE;
	$result = $db->sql_query($sql);

	$bot_ids = array();
	while ($row = $db->sql_fetchrow($result))
	{
		$bot_ids[] = $row['user_id'];
	}
	$db->sql_freeresult($result);

	// Select the group of users to delete
	$sql = 'SELECT user_id, username
		FROM ' . USERS_TABLE . '
		WHERE user_id <> ' . ANONYMOUS . '
			AND user_type <> ' . USER_FOUNDER .'
			AND user_regdate < ' . gmmktime(0, 0, 0, date("m"), (date("d")-$this->minimum_days), date("Y")).'
			AND user_posts = 0'; 
	$result = $db->sql_query($sql);

	$usernames = array();

	//this would be simpler with a SQL statment, but recycling the ppBB prune functon makes it more robust
	while ($row = $db->sql_fetchrow($result))
	{

		// Do not prune bots and the user currently pruning.
		if (!in_array($row['user_id'], $bot_ids))
		{
			user_delete('remove', $row['user_id']);//delete the user and all posts (there should be none though)
			//user_delete('retain', $row['user_id'],$row['username']); //delete users but not posts, safer just in case
			$usernames[]=$row['username'];//keep the list for the log
		}
	}
	$db->sql_freeresult($result);
	
	//add log message
	add_log('admin', 'LOG_PRUNE_USER_DEL_DEL', 'spam hammer zombie cleanup:'.implode(', ', $usernames));

}

}//class

?>