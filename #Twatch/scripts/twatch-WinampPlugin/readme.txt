http://dangerousprototypes.com/forum/index.php?topic=421

For me, the main reason for getting a #twatch in the first place was to display the currently playing song info from WinAmp (couldn't care less about twitter:).  Since I received it, I've been working on a native plug-in for WinAmp (did not want to glue a bunch of stuff together).  So here it is, the first release.  Still fairly in beta state, but I think it might use some testing from others.  Just copy the dll in your plugin directory and it should show up in General Plugins in Winamp.  First time you lunch WinAmp, you'll get an error because the IP address in registry is not set.  Go configure the plugin with the correct IP and it should work...

In it's current state, it displays the artist name in the first row, the song title in the second, the album name and year in the third and finally, the playing status, progress bar and time (played or left) in the fourth.  It also display the shuffle state using a custom char.  If you use the modern skin, it can show the state of "Stop after current".

There are ton of stuff to be done still, like custom chars for playing status (just can't get it to work), maybe scrolling (not sure yet if it's worth the trouble on a LCD), etc...

If you don't like beta stuff, don't bother, otherwise, give it a try and let me know.