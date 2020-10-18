// This script grabs and copies the current youtube time to your clipboard
// Copying code adapted from
// https://www.30secondsofcode.org/blog/s/copy-text-to-clipboard-with-javascript

javascript: ytplayer = document.getElementById("movie_player");
time = ytplayer.getCurrentTime();
if (typeof el !== "undefined") {
  const el = document.createElement("textarea");
}
el.value = new Date(time * 1000).toISOString().substr(11, 8);
el.setAttribute("readonly", "");
el.style.position = "absolute";
el.style.left = "-9999px";
document.body.appendChild(el);
el.select();
document.execCommand("copy");
document.body.removeChild(el);
