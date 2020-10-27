// This script grabs and copies the current youtube time to your clipboard
// Copying code adapted from
// https://www.30secondsofcode.org/blog/s/copy-text-to-clipboard-with-javascript

javascript: ytplayer = document.getElementById("movie_player");
time = ytplayer.getCurrentTime();
el = document.getElementById("ytcopypaster");
if (el == null) var el = document.createElement("textarea");
el.id = "ytcopypaster";
el.value = new Date(time * 1000).toISOString().substr(11, 8);
document.body.appendChild(el);
el.select();
document.execCommand("copy");
document.body.removeChild(el);
