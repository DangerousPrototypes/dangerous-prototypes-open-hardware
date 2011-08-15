//<![CDATA[
setInterval('update_clock();', 1000);

function update_clock()
{
   $date = new Date();
   $hours = $date.getHours();
   $minutes = $date.getMinutes();
   $seconds = $date.getSeconds();
   
   if ($minutes < 10)
   {
      $minutes = '0' + $minutes;
   }
   if ($seconds < 10)
   {
      $seconds = '0' + $seconds;
   }
   
   document.getElementById('clock').innerHTML = $hours + ':' + $minutes + ':' + $seconds;
}

//]]>
