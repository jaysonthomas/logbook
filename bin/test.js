function hideSidebar() {
  document.getElementById('openSideMenu').checked = false;
}

var sideIconToggle = document.getElementById('sidebarContainer');

document.addEventListener('click', function(event) {
  if (!sidebarContainer.contains(event.target))
    hideSidebar();
});

