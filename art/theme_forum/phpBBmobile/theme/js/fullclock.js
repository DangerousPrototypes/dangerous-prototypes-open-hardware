//<![CDATA[
setInterval('update_fullclock();', 1000);

function update_fullclock()
{
    document.getElementById('fullclock').innerHTML = Date(); // "Sat Feb 02 2008 11:31:05 GMT-0800 (PST)"
}

//]]>
