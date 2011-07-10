<?php
/**
*
* link_filter [English]
*
* @package language
* @version $Id$
* @copyright (c) 2005 phpBB Group
* @license http://opensource.org/licenses/gpl-license.php GNU Public License
*
*/

/**
* DO NOT CHANGE
*/
if (!defined('IN_PHPBB'))
{
 exit;
}

if (empty($lang) || !is_array($lang))
{
 $lang = array();
}

// DEVELOPERS PLEASE NOTE
//
// All language files should use UTF-8 as their encoding and the files must not contain a BOM.
//
// Placeholders can now contain order information, e.g. instead of
// 'Page %s of %s' you can (and should) write 'Page %1$s of %2$s', this allows
// translators to re-order the output of data while ensuring it remains correct
//
// You do not need this where single placeholders are used, e.g. 'Message %d' is fine
// equally where a string contains only two placeholders which are used to wrap text
// in a url you again do not need to specify an order e.g., 'Click %sHERE%s' is fine

// Dangerous Prototypes 

$lang = array_merge($lang, array(
    'NO_LINK_FOR_YOU'	=>'',
    'NO_LINK_FOR_YOU_SIG'	=>	'Antispam: You can\'t have off-site URLs in your sig until you post a few times. ',
	'NO_LINK_FOR_YOU_SPAMMY'	=>	'Your post looks too spamy for a new user, please remove off-site URLs.',
	'NO_PROFILE_FOR_YOU'	=> 'Antispam: You can\'t have a profile yet. You need to post a few times first.',
	'NO_WORD_FOR_YOU'	=>  '',
	'NO_WORD_FOR_YOU_SPAMMY'	=>  'Your post looks too spamy for a new user, please remove bad words or non-english text.',
	'NO_WORD_FOR_YOU_MOUTH'	=> 'Do you kiss your mom with that mouth? We don\'t want to read that! ',
	'NO_LINK_TOO_SHORT'	=>	'Antispam: Sorry, your first post needs to be just a little longer.',
	'NO_SLEEPER_SPAM_FOR_YOU'	=>	'Antispam: account disabled, please contact an admin.',
	'HELP_LINK'	=>	'Click for help',
	'SPAM_HAMMER_DELETE_ACCT'	=>	'Antispam: Sorry, this account was DELETED due to suspicious behavior.',
	'LOG_PRUNE_USER_DEL_DEL'	=>	'spam hammer zombie cleanup: ',
	'LOG_SPAM_HAMMER'	=>	'spam hammer: ',

));

?>
