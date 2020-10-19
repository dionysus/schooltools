javascript: audios = document.querySelectorAll("audio, video");
el = document.createElement("div");
el.style.position = "absolute";
el.style.width = "100%";
el.style.zIndex = "9999";
el.style.padding = "10px";
el.style.backgroundColor = "magenta";
var i;
for (i = 0; i < audios.length; i++) {
  newLink = document.createElement("div");
  newLink.innerHTML =
    "<a download" +
    "Download Link #${i+1}".link(audios[i].getAttribute("src")).substring(2);
  el.appendChild(newLink);
}
document.body.prepend(el);
