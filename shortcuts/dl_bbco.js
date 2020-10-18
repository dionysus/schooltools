// This script provides a link to download video files from myMedia.

javascript: const el = document.createElement("div");
el.innerHTML =
  "<a download" +
  "Download Video"
    .link(document.querySelector("video").getAttribute("src"))
    .substring(2);
el.style.position = "absolute";
el.style.width = "100%";
el.style.zIndex = "9999";
el.style.padding = "10px";
el.style.backgroundColor = "magenta";
document.body.prepend(el);
